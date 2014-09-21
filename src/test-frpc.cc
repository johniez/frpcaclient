#include <frpcaclient.h>
#include <iostream>

int main() {
    FRPC::Pool_t pool;

    frpc::aclient::ServerProxy proxy;
    frpc::aclient::Request req("http://localhost:4040/RPC2");
    req.prepare("testMethod", pool.Int(1));

    proxy.add(req);
    proxy.wait();

    if (req.success()) {
        // process result ...
        const FRPC::Struct_t &res = FRPC::Struct(req.response(pool));
        std::cerr << FRPC::Int(res["status"]) << "\n";
        std::cerr << FRPC::String(res["statusMessage"]).c_str();
    } else {
        std::cerr << "Failed: " << req.getError() << "\n";
        return 1;
    }
    return 0;
}
