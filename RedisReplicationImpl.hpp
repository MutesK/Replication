//
// Created by JunMin Kim on 2020/11/01.
//

#ifndef REPLICATION_REDISREPLICATIONIMPL_HPP
#define REPLICATION_REDISREPLICATIONIMPL_HPP

#ifdef REPLICATION_REDIS

#include "ReplicationImpl.h"
#include "ConnectionPool.h"

#include "RedisPublishCommand.hpp"
#include "RedisSubscribeCommand.hpp"

namespace Replication
{
    namespace Redis
    {
        class RedisConnection;

        class RedisReplicationInfo
        {
        protected:
            std::shared_ptr<ConnectionPool<Redis::RedisConnection>> _ConnectionPoolPtr;
        public:
            RedisReplicationInfo(const std::shared_ptr<ConnectionPool<Redis::RedisConnection>>& ConnectionPoolPtr)
            :_ConnectionPoolPtr(ConnectionPoolPtr)
            {
            }
        };

        class RedisPublishReplicationImpl : public IReplicationImpl, public RedisReplicationInfo
        {
            std::unique_ptr<RedisPublishCommand> _CommandPtr;
        public:
            RedisPublishReplicationImpl(const std::shared_ptr<ConnectionPool<Redis::RedisConnection>>& ConnectionPoolPtr);

            virtual void RequestPublishOnce(const PublishParameters &Parameters) override;

            virtual void UnRequestPublishOnce(const PublishParameters &Parameters) override;

            virtual void RegisterSubscribe(const SubscribeParameters &Parameters) override;

            virtual void UnRegisterSubscribe(const SubscribeParameters &Parameters) override;

            virtual void Comsume() override;

        };

        class RedisSubscribeReplicationImpl : public IReplicationImpl, public RedisReplicationInfo
        {
            std::unique_ptr<RedisSubscribeCommand> _CommandPtr;
        public:
            RedisSubscribeReplicationImpl(const std::shared_ptr<ConnectionPool<Redis::RedisConnection>>& ConnectionPoolPtr);

            virtual void RequestPublishOnce(const PublishParameters &Parameters) override;

            virtual void UnRequestPublishOnce(const PublishParameters &Parameters) override;

            virtual void RegisterSubscribe(const SubscribeParameters &Parameters) override;

            virtual void UnRegisterSubscribe(const SubscribeParameters &Parameters) override;

            virtual void Comsume() override;

        };
    }
}

#endif
#endif //REPLICATION_REDISREPLICATIONIMPL_HPP
