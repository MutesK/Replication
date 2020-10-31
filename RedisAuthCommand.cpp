//
// Created by JunMin Kim on 2020/10/31.
//

#include "RedisCommon.h"
#include "RedisConnection.hpp"
#include "RedisAuthCommand.hpp"


namespace Replication
{
    namespace Redis
    {

        RedisAuthCommand::RedisAuthCommand(const ConnectionPtr &Ptr, const std::string& Pass)
            :Command(Ptr), _Pass(Pass)
        {
        }

        ErrorCode RedisAuthCommand::Do()
        {
            const auto& Ptr = std::static_pointer_cast<RedisConnection>(_ConnectionPtr);
            const auto Context = Ptr->GetRedisContext();

            auto Reply = redisCommand(Context, "AUTH %s", _Pass.c_str());

        }
    }
}