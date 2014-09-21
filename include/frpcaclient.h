/* Async FRPC client.
 * The MIT License (MIT)
 * Copyright (c) 2014 Jan Cermak
 */


#ifndef __FRPC_A_CLIENT_H__
#define __FRPC_A_CLIENT_H__

#include <memory>
#include <string>
#include <frpc.h>
#include <frpcserverproxy.h>

namespace frpc {
namespace aclient {

class ServerProxy;


/// Single request to call remote procedure. Request should be passed
/// to ServerProxy object instance to be processed asynchronously.
class Request {
    class PrivateImpl;
    std::shared_ptr<PrivateImpl> impl;
  public:
    /// Create request to \c url frpc server ("http://host:port/RPC2").
    explicit Request(const char *url);

    /// Prepare a remote method call without parameters.
    void prepare(const std::string &method);
    /// Prepare a remote method call with one parameter.
    void prepare(const std::string &method,
                 const FRPC::Value_t &param1);
    /// Prepare a remote method call with two parameters.
    void prepare(const std::string &method,
                 const FRPC::Value_t &param1,
                 const FRPC::Value_t &param2);
    /// Prepare a remote method call with three parameters.
    void prepare(const std::string &method,
                 const FRPC::Value_t &param1,
                 const FRPC::Value_t &param2,
                 const FRPC::Value_t &param3);
    /// Prepare a remote method call with four parameters.
    void prepare(const std::string &method,
                 const FRPC::Value_t &param1,
                 const FRPC::Value_t &param2,
                 const FRPC::Value_t &param3,
                 const FRPC::Value_t &param4);
    /// Prepare a remote method call with five parameters.
    void prepare(const std::string &method,
                 const FRPC::Value_t &param1,
                 const FRPC::Value_t &param2,
                 const FRPC::Value_t &param3,
                 const FRPC::Value_t &param4,
                 const FRPC::Value_t &param5);
    /// Prepare a remote method call with six parameters.
    void prepare(const std::string &method,
                 const FRPC::Value_t &param1,
                 const FRPC::Value_t &param2,
                 const FRPC::Value_t &param3,
                 const FRPC::Value_t &param4,
                 const FRPC::Value_t &param5,
                 const FRPC::Value_t &param6);
    /// Prepare a remote method call with seven parameters.
    void prepare(const std::string &method,
                 const FRPC::Value_t &param1,
                 const FRPC::Value_t &param2,
                 const FRPC::Value_t &param3,
                 const FRPC::Value_t &param4,
                 const FRPC::Value_t &param5,
                 const FRPC::Value_t &param6,
                 const FRPC::Value_t &param7);
    /// Prepare a remote method call with eight parameters.
    void prepare(const std::string &method,
                 const FRPC::Value_t &param1,
                 const FRPC::Value_t &param2,
                 const FRPC::Value_t &param3,
                 const FRPC::Value_t &param4,
                 const FRPC::Value_t &param5,
                 const FRPC::Value_t &param6,
                 const FRPC::Value_t &param7,
                 const FRPC::Value_t &param8);
    /// Prepare a remote method call with nine parameters.
    void prepare(const std::string &method,
                 const FRPC::Value_t &param1,
                 const FRPC::Value_t &param2,
                 const FRPC::Value_t &param3,
                 const FRPC::Value_t &param4,
                 const FRPC::Value_t &param5,
                 const FRPC::Value_t &param6,
                 const FRPC::Value_t &param7,
                 const FRPC::Value_t &param8,
                 const FRPC::Value_t &param9);
    /// Prepare a remote method call with ten parameters.
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
                 const FRPC::Value_t &param10);

    /// Return true if last call was successful.
    bool success() const;

    /// Get error message (valid if last call failed).
    /// \retval 0x0 If request was successful.
    /// \throw std::runtime_error when request did not failed or succeeded.
    const char *getError() const;

    /// Get last call http status code.
    int statusCode() const;

    /// Get last call frpc data received from remote server.
    FRPC::Value_t &response(FRPC::Pool_t &pool) const;

    friend class ServerProxy;
};


/// Multiple Request processor.
class ServerProxy {
    class PrivateImpl;
    std::shared_ptr<PrivateImpl> impl;
  public:
    ServerProxy();
    ServerProxy(const FRPC::ServerProxy_t::Config_t &);

    /// Add request to process. Remote method is not called immediately,
    /// All added requests are processed on wait() method call.
    void add(Request &);

    /**
     * Wait for any client to finish or till timeout.
     * \return Number of successful connections.
     */
    int wait();
};


}  // namespace aclient
}  // namespace frpc

#endif

