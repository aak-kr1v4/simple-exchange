#ifndef REQUEST_TYPES_HPP
#define REQUEST_TYPE_HPP

#include "commonTypes.hpp"

enum class REQUEST_TYPE: ushort
{
    NONE = 0,
    HELLO,
    REGISTRATION,
    ORDER_CREATE,
    GET_BALANCE
};

using req_t = REQUEST_TYPE;

#endif