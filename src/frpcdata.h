/* Async FRPC client.
 * The MIT License (MIT)
 * Copyright (c) 2014 Jan Cermak
 */


#ifndef __FRPC_DATA_CONV_H__
#define __FRPC_DATA_CONV_H__

#include <frpc.h>
#include <string>

namespace frpcdata {


/**
 * Return string representation of frpc request of method \c methodname.
 * Arguments are passed in var_args, last must be null ptr. Thus means
 * for no parameters you must call dumps(methodname, NULL).
 * Valid parameter must be FRPC::Value_t*.
 */
std::string dumps(const char *methodname, ...);


/// Read string data (xml) and return it as FRPC Value.
FRPC::Value_t &loads(FRPC::Pool_t &pool, const std::string &data);


}  // namespace frpcdata

#endif
