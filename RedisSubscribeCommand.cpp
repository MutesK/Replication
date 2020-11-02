//
// Created by JunMin Kim on 2020/11/01.
//


#include "RedisCommon.h"
#include "RedisConnection.hpp"
#include "RedisSubscribeCommand.hpp"

#ifdef REPLICATION_REDIS

namespace Replication
{
    namespace Redis
    {
        RedisSubscribeCommand::RedisSubscribeCommand(const ConnectionPtr &ptr, const timeval& Timeout)
        : Command(ptr)
        {
            auto Context = std::static_pointer_cast<RedisConnection>(_ConnectionPtr)->GetRedisContext();
            if(redisSetTimeout(Context, Timeout) == REDIS_OK)
            {
                RedisError::Throw(Context, __FUNCTION__, __LINE__);
            }
        }

        void RedisSubscribeCommand::PushParameter(const SubscribeParameters &Parameter)
        {
            _ParameterMap.insert({Parameter.Channel, Parameter});
        }

        void RedisSubscribeCommand::EraseParameter(const std::string &ChannelName)
        {
            const auto& Iter = _ParameterMap.find(ChannelName);

            if(Iter == _ParameterMap.end())
            {
                return;
            }

            _ParameterMap.erase(Iter);
        }

        bool RedisSubscribeCommand::Do(ErrorCode &Code)
        {
            static auto CreateSubscribeCommand = [](const ChannelPerSubscribeParameterMap& ParameterMap) -> std::string
            {
                std::string Command;

                std::for_each(ParameterMap.begin(), ParameterMap.end(), [&Command](const auto& Iter)
                {
                    Command.append(Util::StringHelper::Format(" %s ", Iter.second.Channel.c_str()));
                });

                return Command;
            };

            static auto CallbackProcess = [&](const std::string& Channel, const std::string& Value)
            {
                const auto& Iter = _ParameterMap.find(Channel);
                if(Iter == _ParameterMap.end())
                {
                    return;
                }

                const auto& Parameter = Iter->second;
                Parameter.UpdateCallback(Value);
            };

            auto Context = std::static_pointer_cast<RedisConnection>(_ConnectionPtr)->GetRedisContext();
            std::string SubscribeCommand = CreateSubscribeCommand(_ParameterMap);

            {
                ScopedRedisReply Reply = (redisReply *) redisCommand(Context, "SUBSCRIBE %s", SubscribeCommand.c_str());
                if (nullptr == Reply.get())
                {
                    return false;
                }

                if (REDIS_REPLY_ERROR == Reply->type)
                {
                    return false;
                }
            }

            redisReply* pRawReply = nullptr;
            while(redisGetReply(Context, (void **)(&pRawReply)) == REDIS_OK)
            {
                if(pRawReply->type != REDIS_REPLY_ARRAY)
                    continue;

#if defined(REPLICATION_DEBUG)
                for(int index = 0; index < pRawReply->elements; ++index)
                {
                    std::cout << Util::StringHelper::Format("[%d]: %s", index, reply->element[i]->str) << '\n';
                }
#endif
                const std::string ChannelName = pRawReply->element[1]->str;
                const std::string Value = pRawReply->element[2]->str;

                CallbackProcess(ChannelName, Value);

                freeReplyObject(pRawReply);
            }
            return true;
        }

        std::size_t RedisSubscribeCommand::ParameterSize() const
        {
            return _ParameterMap.size();
        }
    }
}

#endif
