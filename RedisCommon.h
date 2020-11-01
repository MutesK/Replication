//
// Created by JunMin Kim on 2020/10/31.
//

#ifndef REPLICATION_REDISCOMMON_H
#define REPLICATION_REDISCOMMON_H

#include "Common.h"

#if defined(REPLICATION_REDIS)


#include <hiredis/hiredis.h>
#include <hiredis/async.h>
#include <hiredis/adapters/libevent.h>

namespace Replication
{
    namespace Redis
    {
        struct RedisError
        {
            static void Throw(redisContext *pContext, std::string function, size_t Line)
            {

            }

            static void Throw(redisAsyncContext *pContext, std::string function, size_t Line)
            {

            }

            static void Throw(std::string ThrowMessage, std::string Function, std::size_t line)
            {

            }
        };

        class ScopedRedisReply
        {
            redisReply *_pRawReply;

        public:
            ScopedRedisReply(redisReply* Reply)
            :_pRawReply(Reply)
            {
            }

            ~ScopedRedisReply()
            {
                freeReplyObject(_pRawReply);
            }

            redisReply *operator->()
            {
                return _pRawReply;
            }

            redisReply *get()
            {
                return _pRawReply;
            }
        };
    }
}

#endif

#endif //REPLICATION_REDISCOMMON_H
