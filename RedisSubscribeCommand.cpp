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
                RedisError::Throw(Context, __FILE__, __FUNCTION__, __LINE__);
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
            auto Context = std::static_pointer_cast<RedisConnection>(_ConnectionPtr)->GetRedisContext();
            std::for_each(_ParameterMap.begin(), _ParameterMap.end(), [&Context](const auto& Iter)
            {
                redisAppendCommand(Context, "SUBSCRIBE %s", Iter.second.Channel);
            });

            std::for_each(_ParameterMap.begin(), _ParameterMap.end(), [&Context](const auto& Iter)
            {
                ScopedRedisReply Reply = nullptr;
                redisGetReply(Context, (void **)(&Reply));

                if(nullptr == Reply.get())
                {
                    RedisError::Throw("redisGetReply returns nullptr", __FILE__, __FUNCTION__, __LINE__);
                }

                if(Reply->type != REDIS_REPLY_ARRAY)
                    return;

#if defined(REPLICATION_DEBUG)
                for(int index = 0; index < Reply->elements; ++index)
                {
                    std::cout << Util::StringHelper::Format("[%d]: %s", index, Reply->element[index]->str) << '\n';
                }
#endif
                Iter.second.UpdateValue(Reply->element[1]->str, Reply->element[2]->str);
            });


            return true;
        }

        std::size_t RedisSubscribeCommand::ParameterSize() const
        {
            return _ParameterMap.size();
        }
    }
}

#endif
