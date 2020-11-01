//
// Created by JunMin Kim on 2020/10/31.
//

#ifndef REPLICATION_REDISCONNECTION_HPP
#define REPLICATION_REDISCONNECTION_HPP

#include "Connection.h"

#ifdef REPLICATION_REDIS


namespace Replication
{
    namespace Redis
    {
        class RedisConnection  : public Connection, public std::enable_shared_from_this<RedisConnection>
        {
            redisContext* _pRawContext;
        public:
            RedisConnection(const ConnectEnviorment& Env);
            virtual ~RedisConnection() override;

            virtual bool Connect(ErrorCode& Code) override;
            virtual bool Disconnect() override;

            redisContext* GetRedisContext();
        };
    }
}

#endif
#endif //REPLICATION_REDISCONNECTION_HPP
