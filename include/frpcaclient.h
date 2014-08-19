/* Async FRPC client.
 * The MIT License (MIT)
 * Copyright (c) 2014 Jan Cermak
 */


#ifndef __FRPC_A_CLIENT_H__
#define __FRPC_A_CLIENT_H__

#include <memory>
#include <string>
#include <frpc.h>

// TODO some namespace

class ServerProxy;

// TODO docs

class Request {
    class PrivateImpl;
    std::shared_ptr<PrivateImpl> impl;
  public:
    explicit Request(const char *url, bool binary = false);

    void prepare(const std::string &method);
    void prepare(const std::string &method,
                 const FRPC::Value_t &param1);
    // TODO ... more params

    /// Return true if last call was successful.
    bool success() const;

    /// Get last call http status code.
    int statusCode() const;

    /// Get last call frpc data received from remote server.
    FRPC::Value_t &response(FRPC::Pool_t &pool);
    const FRPC::Value_t &response(FRPC::Pool_t &pool) const;

    friend class ServerProxy;
};


class ServerProxy {
    class PrivateImpl;
    std::shared_ptr<PrivateImpl> impl;
  public:
    ServerProxy();

    void add(Request &);

    /// void add(Request &, const char *method); ...

    /**
     * Wait for any client to finish or till timeout.
     * \return Number of successful connections.
     */
    int wait();
};


#endif

