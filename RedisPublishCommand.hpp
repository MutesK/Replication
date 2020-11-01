//
// Created by JunMin Kim on 2020/11/01.
//

#ifndef REPLICATION_REDISPUBLISHCOMMAND_HPP
#define REPLICATION_REDISPUBLISHCOMMAND_HPP

#include "Command.h"

#ifdef REPLICATION_REDIS

namespace Replication
{
    namespace Redis
    {
        class RedisPublishCommand : public Command
        {
            ChannelPerPublishParameterMap _ParameterMap;
        public:
            RedisPublishCommand(const ConnectionPtr& Ptr);

            std::size_t ParameterSize() const;
            void PushParameter(const PublishParameters& Parameter);
            void EraseParameter(const std::string& ChannelName);
            void ResetParameter();

            virtual bool Do(ErrorCode &Code) override;
        };
    }
}

#endif


#endif //REPLICATION_REDISPUBLISHCOMMAND_HPP
