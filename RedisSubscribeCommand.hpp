//
// Created by JunMin Kim on 2020/11/01.
//

#ifndef REPLICATION_REDISSUBSCRIBECOMMAND_HPP
#define REPLICATION_REDISSUBSCRIBECOMMAND_HPP

#include "Command.h"

#ifdef REPLICATION_REDIS

namespace Replication
{
    namespace Redis
    {
        class RedisSubscribeCommand : public Command
        {
            ChannelPerSubscribeParameterMap _ParameterMap;

        public:
            RedisSubscribeCommand(const ConnectionPtr &ptr, const timeval& Timeout);

            void PushParameter(const SubscribeParameters& Parameter);
            void EraseParameter(const std::string& ChannelName);
            std::size_t ParameterSize() const;

            // As-like Consume
            virtual bool Do(ErrorCode &Code) override;
        };
    }
}

#endif
#endif //REPLICATION_REDISSUBSCRIBECOMMAND_HPP
