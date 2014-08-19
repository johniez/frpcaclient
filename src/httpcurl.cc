/* Async FRPC client.
 * The MIT License (MIT)
 * Copyright (c) 2014 Jan Cermak
 */


#include "httpcurl.h"


namespace {


/// Receive callback storing data to supplied string pointed to by userdata.
size_t receiveString(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    std::string *data = static_cast<std::string *>(userdata);
    data->append(ptr, size * nmemb);
    return size * nmemb;
}


/// Add header to supplied list, throw exception on error.
curl_slist *addHeader(curl_slist *headers, const char *header) {
    curl_slist *added = curl_slist_append(headers, header);
    if (added) {
        return added;
    }
    throw std::runtime_error("curl_slist_append() failed.");
}


/// xml headers required to acomplish xmlrpc request correctly.
static const char *xheaders[] = {
    "Content-Type: text/xml",
    "Accept: text/xml"
};


}  // anon namespace

namespace httpcurl {


void init() {
    curl_global_init(CURL_GLOBAL_ALL);
}


Req::Req(const char *url)
    : handle(0x0), headers(0x0), lastCode(CURLE_OK), state(INIT)
{
    handle = curl_easy_init();
    if (handle == 0x0) {
        throw std::runtime_error("curl_easy_init() failed.");
    }
    for (size_t i = 0; i < sizeof(xheaders) / sizeof(const char *); ++i) {
        headers = addHeader(headers, xheaders[i]);
    }
    curl_easy_setopt(handle, CURLOPT_URL, url);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, receiveString);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(handle, CURLOPT_PRIVATE, this);
}

Req::~Req() {
    if (headers) curl_slist_free_all(headers);
    curl_easy_cleanup(handle);
}

void Req::dataToPost(const std::string &data) {
    if (state == PERFORMING) {
        throw std::runtime_error("This request still did not finished.");
    }
    state = INIT;
    response.clear();
    requestData = data;
    curl_easy_setopt(handle, CURLOPT_POST, 1);
    curl_easy_setopt(handle, CURLOPT_POSTFIELDSIZE, requestData.size());
    curl_easy_setopt(handle, CURLOPT_POSTFIELDS, requestData.data());
    curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers);
}

const char *Req::getErrorMsg() const {
    switch (state) {
        case INIT:
            throw std::runtime_error("Request not used.");
        case DONE:
            return 0x0;
        case PERFORMING:
            throw std::runtime_error("Request did not finished yet.");
        case FAILED:
            return curl_easy_strerror(lastCode);
        case UNKNOWN:
            throw std::runtime_error("Request state is unknown.");
    }
    return 0x0;
}

int Req::httpStatus() const {
    if (state != DONE) {
        throw std::runtime_error("Request was not completed correctly.");
    }
    long code = 0;
    curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &code);
    return static_cast<int>(code);
}

bool Req::perform() {
    if (state == PERFORMING) {
        throw std::runtime_error("Request is already running.");
    }
    state = PERFORMING;
    lastCode = curl_easy_perform(handle);
    if (lastCode == CURLE_OK) {
        state = DONE;
    } else {
        state = FAILED;
        return false;
    }
    return true;
}

const std::string &Req::getResponse() const {
    if (state != DONE) {
        throw std::runtime_error("Request did not finished.");
    }
    return response;
}


#define MAX_WAIT_MSECS 30*1000

MultiReq::MultiReq()
    : m_handler(0x0)
{
    m_handler = curl_multi_init();
    if (!m_handler) {
        throw std::runtime_error("curl_multi_init() failed.");
    }
}

MultiReq::~MultiReq() {
    curl_multi_cleanup(m_handler);
}

void MultiReq::add(Req &req) {
    if (req.state == Req::PERFORMING) {
        throw std::runtime_error("Request is already performing.");
    }
    req.state = Req::PERFORMING;
    curl_multi_add_handle(m_handler, req.getHandler());
}

int MultiReq::run() {
    int running = 0;
    curl_multi_perform(m_handler, &running);

    do {
        int numfds = 0;
        int res = curl_multi_wait(m_handler, NULL, 0, MAX_WAIT_MSECS, &numfds);
        if (res != CURLM_OK) {
            throw std::runtime_error("curl_multi_wait() error.");
        }
        curl_multi_perform(m_handler, &running);
    } while (running);

    return collect();
}

int MultiReq::collect() {
    int errCount = 0;
    CURLMsg *msg = 0x0;
    int msgs_left = 0;
    while ((msg = curl_multi_info_read(m_handler, &msgs_left))) {
        Req *req = 0x0;
        curl_easy_getinfo(msg->easy_handle, CURLINFO_PRIVATE, &req);
        if (msg->msg == CURLMSG_DONE) {
            req->state = Req::DONE;
            CURLcode returnCode = msg->data.result;
            req->lastCode = returnCode;
            if (returnCode != CURLE_OK) {
                req->state = Req::FAILED;
                errCount++;
            }
        } else {
            req->state = Req::UNKNOWN;
            errCount++;
        }

        curl_multi_remove_handle(m_handler, msg->easy_handle);
    }
    return errCount;
}


}  // namespace httpcurl

