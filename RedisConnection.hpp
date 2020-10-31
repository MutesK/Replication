//
// Created by JunMin Kim on 2020/10/31.
//

#ifndef REPLICATION_REDISCONNECTION_HPP
#define REPLICATION_REDISCONNECTION_HPP

#include "Connection.h"

namespace Replication
{
    namespace Redis
    {
        class RedisConnection  : public Connection
        {
            redisContext* _pRawContext;
        public:
            RedisConnection(const ConnectEnviorment& Env);
            virtual ~RedisConnection() override;

            virtual ErrorCode Connect() override;
            virtual bool Disconnect() override;

            redisContext* GetRedisContext();
        };
    }
}

#endif //REPLICATION_REDISCONNECTION_HPP
