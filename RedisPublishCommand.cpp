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
            static auto CreatePublishCommand = [](const ChannelPerPublishParameterMap& ParameterMap) -> std::string
            {
                std::string Command;

                std::for_each(ParameterMap.begin(), ParameterMap.end(), [&Command](const auto& Iter)
                {
                    Command.append(Util::StringHelper::Format(" %s %s ", Iter.second.Channel.c_str(), Iter.second.Value.c_str()));
                });

                return Command;
            };

            auto Context = std::static_pointer_cast<RedisConnection>(_ConnectionPtr)->GetRedisContext();
            std::string PublishCommand = CreatePublishCommand(_ParameterMap);

            ScopedRedisReply Reply = (redisReply *)redisCommand(Context, "PUBLISH %s", PublishCommand.c_str());
            if(nullptr == Reply.get())
            {
                return false;
            }

            if(Reply->type == REDIS_REPLY_ERROR)
            {
                RedisError::Throw(Context, __FUNCTION__, __LINE__);
                return false;
            }

#if defined(REPLICATION_DEBUG)
            std::cout << Util::StringHelper::Format("PUBLISH: %s", PublishCommand) << '\n';
#endif
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
