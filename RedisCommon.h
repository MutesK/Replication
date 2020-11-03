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
        const std::string BlankCommand = " ";

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
        struct RedisError
        {
            static void Throw(redisContext *pContext, std::string file, std::string function, size_t Line)
            {
#if defined(REPLICATION_DEBUG)

#endif
                throw std::logic_error(Util::StringHelper::Format("RedisError: %s Function %s/ Line %d  Because (%d:%s)",
                                                            file.c_str(),
                                                            function.c_str(),
                                                            Line,
                                                            pContext->err,
                                                            pContext->errstr));
            }

            static void Throw(ScopedRedisReply& Reply, std::string file, std::string function, size_t Line)
            {
#if defined(REPLICATION_DEBUG)

#endif
                throw std::logic_error(Util::StringHelper::Format("RedisError: %s Function %s/ Line %d  Because (%s)",
                                                                  file.c_str(),
                                                                  function.c_str(),
                                                                  Line,
                                                                  Reply->str));
            }

            static void Throw(std::string ThrowMessage, std::string file, std::string Function, std::size_t line)
            {
#if defined(REPLICATION_DEBUG)

#endif
                throw std::logic_error(Util::StringHelper::Format("RedisError: %s Function %s/ Line %d Because (%s)",
                                                                  file.c_str(),
                                                                  Function.c_str(),
                                                            line,
                                                            ThrowMessage.c_str()));
            }
        };


    }
}

#endif

#endif //REPLICATION_REDISCOMMON_H
