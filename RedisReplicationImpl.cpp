//
// Created by JunMin Kim on 2020/11/01.
//

#include "RedisCommon.h"
#include "RedisReplicationImpl.hpp"
#include "RedisConnection.hpp"


#ifdef REPLICATION_REDIS

namespace Replication
{
    namespace Redis
    {
        RedisPublishReplicationImpl::RedisPublishReplicationImpl(
                const std::shared_ptr<ConnectionPool<Redis::RedisConnection>> &ConnectionPoolPtr)
                :RedisReplicationInfo(ConnectionPoolPtr)
        {
            _CommandPtr = std::unique_ptr<RedisPublishCommand>(new RedisPublishCommand(ConnectionPoolPtr->Acquire()));
        }

        void RedisPublishReplicationImpl::RequestPublishOnce(const PublishParameters &Parameters)
        {
            _CommandPtr->PushParameter(Parameters);
        }

        void RedisPublishReplicationImpl::UnRequestPublishOnce(const PublishParameters &Parameters)
        {
            _CommandPtr->EraseParameter(Parameters.Channel);
        }

        void RedisPublishReplicationImpl::RegisterSubscribe(const SubscribeParameters &Parameters)
        {
            // Not to Run
        }

        void RedisPublishReplicationImpl::UnRegisterSubscribe(const SubscribeParameters &Parameters)
        {
            // Not to Run
        }

        void RedisPublishReplicationImpl::Resume()
        {
            if(_CommandPtr->ParameterSize() <= 0)
            {
                return;
            }

            ErrorCode Code;
            if(!_CommandPtr->Do(Code))
            {
                //
            }

            _CommandPtr->ResetParameter();
        }

        RedisSubscribeReplicationImpl::RedisSubscribeReplicationImpl(
                const std::shared_ptr<ConnectionPool<Redis::RedisConnection>> &ConnectionPoolPtr)
                : RedisReplicationInfo(ConnectionPoolPtr)
        {
            struct timeval time;
            time.tv_sec = 1;

            _CommandPtr = std::unique_ptr<RedisSubscribeCommand>(new RedisSubscribeCommand(ConnectionPoolPtr->Acquire(), time));
        }

        void RedisSubscribeReplicationImpl::RequestPublishOnce(const PublishParameters &Parameters)
        {
            // Not to Run
        }

        void RedisSubscribeReplicationImpl::UnRequestPublishOnce(const PublishParameters &Parameters)
        {
            // Not to Run
        }

        void RedisSubscribeReplicationImpl::RegisterSubscribe(const SubscribeParameters &Parameters)
        {
            _CommandPtr->PushParameter(Parameters);
        }

        void RedisSubscribeReplicationImpl::UnRegisterSubscribe(const SubscribeParameters &Parameters)
        {
            _CommandPtr->EraseParameter(Parameters.Channel);
        }

        void RedisSubscribeReplicationImpl::Resume()
        {
            if(_CommandPtr->ParameterSize() <= 0)
            {
                return;
            }

            ErrorCode Code;
            if(!_CommandPtr->Do(Code))
            {

            }
        }

    }
}

#endif