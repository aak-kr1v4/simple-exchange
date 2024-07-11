#ifndef REQUEST_TYPES_HPP
#define REQUEST_TYPE_HPP

#include "commonTypes.hpp"

enum class REQUEST_TYPE: ushort
{
    NONE = 0,
    HELLO,
    REGISTRATION,
    ORDER_CREATE,
    GET_BALANCE,
    END_OF_ENUM
};

using REQ_T = REQUEST_TYPE;

#endif