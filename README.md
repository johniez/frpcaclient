frpcaclient
===========

FastRPC async client.

TODO

## Deps

libcurl, libfastrpc

## Desired usage:
```c++ 
#include <frpcaclient.h>

int main() {
    FRPC::Pool_t pool;

    frpc::aclient::ServerProxy proxy;
    frpc::aclient::Request req("http://host:port/RPC2");
    // prepare call someRemoteMethod(1)
    req.prepare("someRemoteMethod", pool.Int(1));

    proxy.add(req);
    // prepare and add more requests... and then launch it.
    proxy.wait();

    if (req.success()) {
        // process result ... FRPC::Struct(req.getResponse(pool));
    }
    return 0;
}
```
