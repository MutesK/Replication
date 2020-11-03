//
// Created by JunMin Kim on 2020/11/01.
//

#include "RedisCommon.h"
#include "RedisConnection.hpp"
#include "RedisPublishCommand.hpp"

#ifdef REPLICATION_REDIS

namespace Replication
{
    namespace Redis
    {
        RedisPublishCommand::RedisPublishCommand(const ConnectionPtr& Ptr)
                : Command(Ptr)
        {
        }

        bool RedisPublishCommand::Do(ErrorCode &Code)
        {
            auto Context = std::static_pointer_cast<RedisConnection>(_ConnectionPtr)->GetRedisContext();
            std::for_each(_ParameterMap.begin(), _ParameterMap.end(), [&Context](const auto& Iter)
            {
                redisAppendCommand(Context, "PUBLISH %s %s", Iter.second.Channel.c_str(), Iter.second.Value.c_str());
            });

            std::for_each(_ParameterMap.begin(), _ParameterMap.end(), [&Context](const auto& Iter)
            {
                ScopedRedisReply Reply = nullptr;
                redisGetReply(Context, (void **)(&Reply));

                // Debug if type reply_integer then print recvied client num.
            });

            return true;
        }

        void RedisPublishCommand::PushParameter(const PublishParameters &Parameter)
        {
            _ParameterMap.insert({Parameter.Channel, Parameter});
        }

        void RedisPublishCommand::EraseParameter(const std::string &ChannelName)
        {
            const auto& Iter = _ParameterMap.find(ChannelName);

            if(Iter == _ParameterMap.end())
            {
                return;
            }

            _ParameterMap.erase(Iter);
        }

        void RedisPublishCommand::ResetParameter()
        {
            _ParameterMap.clear();
        }

        std::size_t RedisPublishCommand::ParameterSize() const
        {
            return _ParameterMap.size();
        }
    }

}

#endif
