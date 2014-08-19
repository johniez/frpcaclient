/* Async FRPC client.
 * The MIT License (MIT)
 * Copyright (c) 2014 Jan Cermak
 */


#include "frpcdata.h"
#include <frpcmarshaller.h>
#include <frpcwriter.h>
#include <frpcunmarshaller.h>
#include <frpctreefeeder.h>
#include <frpctreebuilder.h>
#include <string.h>
#include <cstdarg>

namespace {


class StringWriter: public FRPC::Writer_t {
    std::string data;
  public:
    StringWriter() {}
    virtual void write(const char *data, unsigned size) {
        this->data.append(data, size);
    }
    virtual void flush() {}

    const std::string &getData() const {
        return data;
    }
};


/// va_list RAII.
struct VaListHolder {
    va_list &args;

    VaListHolder(va_list &args)
        : args(args)
    {}
    ~VaListHolder() {
        va_end(args);
    }
};


}  // anon namespace 

namespace frpcdata {


std::string dumps(const char *methodname, va_list args) {
    // TODO configurable from outside
    int useBinary = false;
    unsigned char protocolVersionMajor = 2;
    unsigned char protocolVersionMinor = 1;

    // create writer
    StringWriter writer;
    // create marshaller
    FRPC::Marshaller_t *marshaller = FRPC::Marshaller_t::create((useBinary
        ? FRPC::Marshaller_t::BINARY_RPC
        : FRPC::Marshaller_t::XML_RPC),
        writer, FRPC::ProtocolVersion_t(protocolVersionMajor,
                                        protocolVersionMinor));
    try {
        FRPC::TreeFeeder_t feeder(*marshaller);
        if (methodname) {
            marshaller->packMethodCall(methodname, strlen(methodname));
            // process value pointers varargs until nullptr.
            while (const FRPC::Value_t *value = va_arg(args, FRPC::Value_t*)) {
                feeder.feedValue(*value);
            }
        }

        marshaller->flush();
    } catch (const std::exception &e) {
        throw;
    }

    return writer.getData();
}


std::string dumps(const char *methodname, ...) {
    va_list args;
    va_start(args, methodname);
    VaListHolder _args(args);
    return std::string();
}


/// Read string data (xml) and return it as FRPC Value.
FRPC::Value_t &loads(FRPC::Pool_t &pool, const std::string &data) {
    FRPC::TreeBuilder_t tree(pool);
    FRPC::UnMarshaller_t *xml = FRPC::UnMarshaller_t::create(
            FRPC::UnMarshaller_t::XML_RPC, tree);
    xml->unMarshall(data.c_str(), data.size(), FRPC::UnMarshaller_t::TYPE_METHOD_RESPONSE);
    return tree.getUnMarshaledData();
}


}  // namespace frpcdata

