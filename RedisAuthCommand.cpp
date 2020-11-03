//
// Created by JunMin Kim on 2020/10/31.
//


#include "RedisCommon.h"
#include "RedisConnection.hpp"
#include "RedisAuthCommand.hpp"


#ifdef REPLICATION_REDIS

namespace Replication
{
    namespace Redis
    {

        RedisAuthCommand::RedisAuthCommand(const ConnectionPtr &Ptr, const std::string& Pass)
            :Command(Ptr), _Pass(Pass)
        {
        }

        bool RedisAuthCommand::Do(ErrorCode& Code)
        {
            const auto& Ptr = std::static_pointer_cast<RedisConnection>(_ConnectionPtr);
            if(nullptr == Ptr)
            {
                RedisError::Throw("Connection Pointer is Null", __FILE__, __FUNCTION__, __LINE__);
                return false;
            }

            auto Context = Ptr->GetRedisContext();
            if(nullptr == Context)
            {
                RedisError::Throw("RedisContext Pointer is Null Get From Connection", __FILE__,  __FUNCTION__, __LINE__);
                return false;
            }

            ScopedRedisReply Reply = (redisReply *)redisCommand(Context, "AUTH %s", _Pass.c_str());
            if(nullptr == Reply.get())
            {
                RedisError::Throw("RedisReply is Null From redisCommand",  __FILE__, __FUNCTION__, __LINE__);
                return false;
            }

#if defined(REPLICATION_DEBUG)
            std::cout << Util::StringHelper::Format("AUTH %s", Reply->str) << '\n';
#endif

            if(Reply->type == REDIS_REPLY_ERROR)
            {
                RedisError::Throw("Redis Auth Failed",  __FILE__, __FUNCTION__, __LINE__);
                return false;
            }
            return true;
        }
    }
}

#endif