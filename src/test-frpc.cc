#include <frpcaclient.h>

int main() {
    FRPC::Pool_t pool;

    frpc::aclient::ServerProxy proxy;
    frpc::aclient::Request req("http://localhost:4040/RPC2");
    req.prepare("testMethod", pool.Int(1));

    proxy.add(req);
    proxy.wait();

    if (req.success()) {
        // process result ... FRPC::Struct(req.response(pool));
        FRPC::Value_t &res = req.response(pool);
        // TODO
    }
    return 0;
}
