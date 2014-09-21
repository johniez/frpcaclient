/* Async FRPC client.
 * The MIT License (MIT)
 * Copyright (c) 2014 Jan Cermak
 */


#include "frpcaclient.h"
#include "httpcurl.h"
#include "frpcdata.h"


namespace frpc {
namespace aclient {


class Request::PrivateImpl {
    httpcurl::Req request;
    bool useBinary;
    unsigned char protMajor;
    unsigned char protMinor;
  public:
    explicit PrivateImpl(const char *url)
      : request(url), useBinary(false),
        protMajor(2), protMinor(0)
    {}

    httpcurl::Req &data() {
        return request;
    }

    void setOpts(const FRPC::ServerProxy_t::Config_t &);

    void prepare(const std::string &method) {
        frpcdata::Converter cnvt(useBinary, protMajor, protMinor);
        request.dataToPost(cnvt.dumps(method.c_str(), 0x0));
    }

    void prepare(const std::string &method,
                 const FRPC::Value_t &param1) {
        frpcdata::Converter cnvt(useBinary, protMajor, protMinor);
        request.dataToPost(cnvt.dumps(method.c_str(), &param1, 0x0));
    }

    void prepare(const std::string &method,
                 const FRPC::Value_t &param1,
                 const FRPC::Value_t &param2) {
        frpcdata::Converter cnvt(useBinary, protMajor, protMinor);
        request.dataToPost(cnvt.dumps(method.c_str(), &param1, &param2,
                    0x0));
    }

    void prepare(const std::string &method,
                 const FRPC::Value_t &param1,
                 const FRPC::Value_t &param2,
                 const FRPC::Value_t &param3) {
        frpcdata::Converter cnvt(useBinary, protMajor, protMinor);
        request.dataToPost(cnvt.dumps(method.c_str(), &param1, &param2,
                    &param3, 0x0));
    }

    void prepare(const std::string &method,
                 const FRPC::Value_t &param1,
                 const FRPC::Value_t &param2,
                 const FRPC::Value_t &param3,
                 const FRPC::Value_t &param4) {
        frpcdata::Converter cnvt(useBinary, protMajor, protMinor);
        request.dataToPost(cnvt.dumps(method.c_str(), &param1, &param2,
                    &param3, &param4, 0x0));
    }

    void prepare(const std::string &method,
                 const FRPC::Value_t &param1,
                 const FRPC::Value_t &param2,
                 const FRPC::Value_t &param3,
                 const FRPC::Value_t &param4,
                 const FRPC::Value_t &param5) {
        frpcdata::Converter cnvt(useBinary, protMajor, protMinor);
        request.dataToPost(cnvt.dumps(method.c_str(), &param1, &param2,
                    &param3, &param4, &param5, 0x0));
    }

    void prepare(const std::string &method,
                 const FRPC::Value_t &param1,
                 const FRPC::Value_t &param2,
                 const FRPC::Value_t &param3,
                 const FRPC::Value_t &param4,
                 const FRPC::Value_t &param5,
                 const FRPC::Value_t &param6) {
        frpcdata::Converter cnvt(useBinary, protMajor, protMinor);
        request.dataToPost(cnvt.dumps(method.c_str(), &param1, &param2,
                    &param3, &param4, &param5, &param6, 0x0));
    }

    void prepare(const std::string &method,
                 const FRPC::Value_t &param1,
                 const FRPC::Value_t &param2,
                 const FRPC::Value_t &param3,
                 const FRPC::Value_t &param4,
                 const FRPC::Value_t &param5,
                 const FRPC::Value_t &param6,
                 const FRPC::Value_t &param7) {
        frpcdata::Converter cnvt(useBinary, protMajor, protMinor);
        request.dataToPost(cnvt.dumps(method.c_str(), &param1, &param2,
                    &param3, &param4, &param5, &param6, &param7, 0x0));
    }

    void prepare(const std::string &method,
                 const FRPC::Value_t &param1,
                 const FRPC::Value_t &param2,
                 const FRPC::Value_t &param3,
                 const FRPC::Value_t &param4,
                 const FRPC::Value_t &param5,
                 const FRPC::Value_t &param6,
                 const FRPC::Value_t &param7,
                 const FRPC::Value_t &param8) {
        frpcdata::Converter cnvt(useBinary, protMajor, protMinor);
        request.dataToPost(cnvt.dumps(method.c_str(), &param1, &param2,
                    &param3, &param4, &param5, &param6, &param7, &param8,
                    0x0));
    }

    void prepare(const std::string &method,
                 const FRPC::Value_t &param1,
                 const FRPC::Value_t &param2,
                 const FRPC::Value_t &param3,
                 const FRPC::Value_t &param4,
                 const FRPC::Value_t &param5,
                 const FRPC::Value_t &param6,
                 const FRPC::Value_t &param7,
                 const FRPC::Value_t &param8,
                 const FRPC::Value_t &param9) {
        frpcdata::Converter cnvt(useBinary, protMajor, protMinor);
        request.dataToPost(cnvt.dumps(method.c_str(), &param1, &param2,
                    &param3, &param4, &param5, &param6, &param7, &param8,
                    &param9, 0x0));
    }

    void prepare(const std::string &method,
                 const FRPC::Value_t &param1,
                 const FRPC::Value_t &param2,
                 const FRPC::Value_t &param3,
                 const FRPC::Value_t &param4,
                 const FRPC::Value_t &param5,
                 const FRPC::Value_t &param6,
                 const FRPC::Value_t &param7,
                 const FRPC::Value_t &param8,
                 const FRPC::Value_t &param9,
                 const FRPC::Value_t &param10) {
        frpcdata::Converter cnvt(useBinary, protMajor, protMinor);
        request.dataToPost(cnvt.dumps(method.c_str(), &param1, &param2,
                    &param3, &param4, &param5, &param6, &param7, &param8,
                    &param9, &param10, 0x0));
    }

    bool success() const {
        return request.succeeded();
    }

    const char *getError() const {
        return request.getErrorMsg();
    }

    int statusCode() const {
        return request.httpStatus();
    }

    FRPC::Value_t &response(FRPC::Pool_t &pool) {
        frpcdata::Converter cnvt(useBinary, protMajor, protMinor);
        return cnvt.loads(pool, request.getResponse());
    }
    const FRPC::Value_t &response(FRPC::Pool_t &pool) const {
        frpcdata::Converter cnvt(useBinary, protMajor, protMinor);
        return cnvt.loads(pool, request.getResponse());
    }
};

void Request::PrivateImpl::setOpts(const FRPC::ServerProxy_t::Config_t &cfg) {
    useBinary = false; // TODO cfg.useBinary;
    // FIXME this settings is too late. prepare() methods are done using defaults! (versions and binary)...
    protMajor = cfg.protocolVersion.versionMajor;
    protMinor = cfg.protocolVersion.versionMinor;
    request.setConnectTimeout(cfg.connectTimeout);
    request.setReadTimeout(cfg.readTimeout);
}


class ServerProxy::PrivateImpl {
    FRPC::ServerProxy_t::Config_t config;
    httpcurl::MultiReq proxy;
  public:
    PrivateImpl(): config(), proxy() {}
    PrivateImpl(const FRPC::ServerProxy_t::Config_t &cfg)
        : config(cfg), proxy()
    {}

    void add(Request::PrivateImpl *req) {
        req->setOpts(config);
        proxy.add(req->data());
    }

    int wait() {
        return proxy.run();
    }
};


// Request pimpl calls

Request::Request(const char *url)
    : impl(new PrivateImpl(url))
{}

void Request::prepare(const std::string &method) {
    impl->prepare(method);
}

void Request::prepare(const std::string &method,
                      const FRPC::Value_t &param1) {
    impl->prepare(method, param1);
}

void Request::prepare(const std::string &method,
                      const FRPC::Value_t &param1,
                      const FRPC::Value_t &param2) {
    impl->prepare(method, param1, param2);
}

void Request::prepare(const std::string &method,
                      const FRPC::Value_t &param1,
                      const FRPC::Value_t &param2,
                      const FRPC::Value_t &param3) {
    impl->prepare(method, param1, param2, param3);
}

void Request::prepare(const std::string &method,
                      const FRPC::Value_t &param1,
                      const FRPC::Value_t &param2,
                      const FRPC::Value_t &param3,
                      const FRPC::Value_t &param4) {
    impl->prepare(method, param1, param2, param3, param4);
}

void Request::prepare(const std::string &method,
                      const FRPC::Value_t &param1,
                      const FRPC::Value_t &param2,
                      const FRPC::Value_t &param3,
                      const FRPC::Value_t &param4,
                      const FRPC::Value_t &param5) {
    impl->prepare(method, param1, param2, param3, param4, param5);
}

void Request::prepare(const std::string &method,
                      const FRPC::Value_t &param1,
                      const FRPC::Value_t &param2,
                      const FRPC::Value_t &param3,
                      const FRPC::Value_t &param4,
                      const FRPC::Value_t &param5,
                      const FRPC::Value_t &param6) {
    impl->prepare(method, param1, param2, param3, param4, param5, param6);
}

void Request::prepare(const std::string &method,
                      const FRPC::Value_t &param1,
                      const FRPC::Value_t &param2,
                      const FRPC::Value_t &param3,
                      const FRPC::Value_t &param4,
                      const FRPC::Value_t &param5,
                      const FRPC::Value_t &param6,
                      const FRPC::Value_t &param7) {
    impl->prepare(method, param1, param2, param3, param4, param5, param6,
                  param7);
}

void Request::prepare(const std::string &method,
                      const FRPC::Value_t &param1,
                      const FRPC::Value_t &param2,
                      const FRPC::Value_t &param3,
                      const FRPC::Value_t &param4,
                      const FRPC::Value_t &param5,
                      const FRPC::Value_t &param6,
                      const FRPC::Value_t &param7,
                      const FRPC::Value_t &param8) {
    impl->prepare(method, param1, param2, param3, param4, param5, param6,
                  param7, param8);
}

void Request::prepare(const std::string &method,
                      const FRPC::Value_t &param1,
                      const FRPC::Value_t &param2,
                      const FRPC::Value_t &param3,
                      const FRPC::Value_t &param4,
                      const FRPC::Value_t &param5,
                      const FRPC::Value_t &param6,
                      const FRPC::Value_t &param7,
                      const FRPC::Value_t &param8,
                      const FRPC::Value_t &param9) {
    impl->prepare(method, param1, param2, param3, param4, param5, param6,
                  param7, param8, param9);
}

void Request::prepare(const std::string &method,
                      const FRPC::Value_t &param1,
                      const FRPC::Value_t &param2,
                      const FRPC::Value_t &param3,
                      const FRPC::Value_t &param4,
                      const FRPC::Value_t &param5,
                      const FRPC::Value_t &param6,
                      const FRPC::Value_t &param7,
                      const FRPC::Value_t &param8,
                      const FRPC::Value_t &param9,
                      const FRPC::Value_t &param10) {
    impl->prepare(method, param1, param2, param3, param4, param5, param6,
                  param7, param8, param9, param10);
}

bool Request::success() const {
    return impl->success();
}

const char *Request::getError() const {
    return impl->getError();
}

int Request::statusCode() const {
    return impl->statusCode();
}

FRPC::Value_t &Request::response(FRPC::Pool_t &pool) const {
    return impl->response(pool);
}

// ServerProxy pimpl calls

ServerProxy::ServerProxy()
    : impl(new PrivateImpl())
{}

ServerProxy::ServerProxy(const FRPC::ServerProxy_t::Config_t &cfg)
    : impl(new PrivateImpl(cfg))
{}

void ServerProxy::add(Request &req) {
    impl->add(req.impl.get());
}

int ServerProxy::wait() {
    return impl->wait();
}


}  // namespace aclient
}  // namespace frpc

