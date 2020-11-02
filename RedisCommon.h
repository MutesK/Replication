//
// Created by JunMin Kim on 2020/10/31.
//

#ifndef REPLICATION_REDISCOMMON_H
#define REPLICATION_REDISCOMMON_H

#include "Common.h"

#if defined(REPLICATION_REDIS)

#include <hiredis/hiredis.h>

namespace Replication
{
    namespace Redis
    {
        struct RedisError
        {
            static void Throw(redisContext *pContext, std::string function, size_t Line)
            {
#if defined(REPLICATION_DEBUG)

#endif
                throw std::logic_error(Util::StringHelper::Format("RedisError: Function %s/ Line %d  Because (%d:%s)",
                                                            function.c_str(),
                                                            Line,
                                                            pContext->err,
                                                            pContext->errstr));
            }

            static void Throw(std::string ThrowMessage, std::string Function, std::size_t line)
            {
#if defined(REPLICATION_DEBUG)

#endif
                throw std::logic_error(Util::StringHelper::Format("RedisError: Function %s/ Line %d Because (%s)",
                                                            Function.c_str(),
                                                            line,
                                                            ThrowMessage.c_str()));
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
