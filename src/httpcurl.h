/* Async FRPC client.
 * The MIT License (MIT)
 * Copyright (c) 2014 Jan Cermak
 */


#ifndef __HTTP_CURL_TRANS_H__
#define __HTTP_CURL_TRANS_H__

#include <curl/curl.h>
#include <curl/multi.h>
#include <stdexcept>
#include <string>

namespace httpcurl {


/// Init underlaying libraries
void init();


class MultiReq;

class Req {
    CURL *handle;       ///< CURL easy handler for single connection.
    curl_slist *headers;///< Headers assigned to request.
    CURLcode lastCode;  ///< Last curl status code, valid for state = DONE || FAILED.
    enum {
        INIT = -1,      ///< Did not performed yet.
        DONE = 0,       ///< OK completed.
        PERFORMING,     ///< Performing and not finished yet.
        FAILED,         ///< Something went wrong. lastCode for details.
        UNKNOWN         ///< Unknown incorrect state.
    } state;
    std::string response;       ///< Response data.
    std::string requestData;    ///< Request data copy.

    inline CURL *getHandler() {
        return handle;
    }

    Req(const Req &);
    Req &operator=(const Req &);
  public:
    explicit Req(const char *url);

    ~Req();

    /// Prepare data to post. Does not initiate data transfer.
    /// Request must be added using MultiReq::add() method
    /// and after successful call of MultiReq::run() should be response
    /// available. Or use Req::perform() method to transfer data
    /// synchronously.
    void dataToPost(const std::string &data);

    /// Return true if (asynchronously) performed request succeeded.
    inline bool succeeded() const {
        return state == DONE;
    }

    /// Return human readable error message, if (asynchronously) performed
    /// request failed.
    const char *getErrorMsg() const;

    /// Return http status code of last successful request.
    int httpStatus() const;

    /// Run request in synchronous way. Blocks until response is completed.
    /// Return true if request succeeded.
    bool perform();

    /// Get data received from remote server.
    const std::string &getResponse() const;

    /// Set timeouts in msec.
    void setConnectTimeout(int msec);
    void setReadTimeout(int msec);

    friend class MultiReq;
};


class MultiReq {
    /// Curl multi handler.
    CURLM *m_handler;

    MultiReq(const MultiReq &);
    MultiReq &operator=(const MultiReq &);
  public:
    MultiReq();
    ~MultiReq();

    /// Add request to run it asynchronously. To initiate data transfer, use
    /// method run().
    void add(Req &req);

    /// Run all previously added request asynchronously.
    /// Return number of failed requests. Zero on success.
    int run();
  private:
    /// Collect all requests state. Release it from MultiReq instance.
    /// Return number of failed requests.
    int collect();
};


}  // namespace httpcurl

#endif
