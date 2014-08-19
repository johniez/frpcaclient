/* Async FRPC client.
 * The MIT License (MIT)
 * Copyright (c) 2014 Jan Cermak
 */


#include "frpcaclient.h"
#include "httpcurl.h"
#include "frpcdata.h"


class Request::PrivateImpl {
    httpcurl::Req request;
  public:
    PrivateImpl(const char *url, bool binary)
      : request(url)
    {}

    httpcurl::Req &data() {
        return request;
    }

    void prepare(const std::string &method) {
        request.dataToPost(frpcdata::dumps(method.c_str(), 0x0));
    }

    void prepare(const std::string &method,
                 const FRPC::Value_t &param1) {
        request.dataToPost(frpcdata::dumps(method.c_str(), &param1, 0x0));
    }

    bool success() const {
        return request.succeeded();
    }

    int statusCode() const {
        return request.httpStatus();
    }

    FRPC::Value_t &response(FRPC::Pool_t &pool) {
        return frpcdata::loads(pool, request.getResponse());
    }
    const FRPC::Value_t &response(FRPC::Pool_t &pool) const {
        return frpcdata::loads(pool, request.getResponse());
    }
};


class ServerProxy::PrivateImpl {
    httpcurl::MultiReq proxy;
  public:
    PrivateImpl(): proxy() {}

    void add(Request::PrivateImpl *req) {
        proxy.add(req->data());
    }

    int wait() {
        return proxy.run();
    }
};


// Request pimpl calls

Request::Request(const char *url, bool binary)
    : impl(new PrivateImpl(url, binary))
{}

void Request::prepare(const std::string &method) {
    impl->prepare(method);
}

void Request::prepare(const std::string &method,
                      const FRPC::Value_t &param1) {
    impl->prepare(method, param1);
}

bool Request::success() const {
    return impl->success();
}

int Request::statusCode() const {
    return impl->statusCode();
}

FRPC::Value_t &Request::response(FRPC::Pool_t &pool) {
    return impl->response(pool);
}

const FRPC::Value_t &Request::response(FRPC::Pool_t &pool) const {
    return impl->response(pool);
}

// ServerProxy pimpl calls

ServerProxy::ServerProxy()
    : impl(new PrivateImpl())
{}

void ServerProxy::add(Request &req) {
    impl->add(req.impl.get());
}

int ServerProxy::wait() {
    return impl->wait();
}

