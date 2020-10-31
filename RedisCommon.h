//
// Created by JunMin Kim on 2020/10/31.
//

#ifndef REPLICATION_REDISCOMMON_H
#define REPLICATION_REDISCOMMON_H

#include <hiredis/hiredis.h>
#include <hiredis/async.h>
#include <hiredis/adapters/libevent.h>

namespace Redis
{
    struct RedisError
    {
        static void Throw(redisContext* pContext, std::string function, size_t Line)
        {

        }

        static void Throw(redisAsyncContext* pContext, std::string function, size_t Line)
        {

        }
    };
}

#endif //REPLICATION_REDISCOMMON_H
