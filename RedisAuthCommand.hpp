//
// Created by JunMin Kim on 2020/10/31.
//

#ifndef REPLICATION_REDISAUTHCOMMAND_HPP
#define REPLICATION_REDISAUTHCOMMAND_HPP

#include "Command.h"

namespace Replication
{
    namespace Redis
    {
        class RedisAuthCommand : public Command
        {
            std::string _Pass;
        public:
            RedisAuthCommand(const ConnectionPtr& Ptr, const std::string& Pass);

            virtual ErrorCode Do() override;
        };
    }
}


#endif //REPLICATION_REDISAUTHCOMMAND_HPP
