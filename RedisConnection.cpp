//
// Created by JunMin Kim on 2020/10/31.
//


#include "RedisCommon.h"
#include "RedisConnection.hpp"
#include "RedisAuthCommand.hpp"

#ifdef REPLICATION_REDIS


namespace Replication
{
    namespace Redis
    {
        RedisConnection::RedisConnection(const ConnectEnviorment &Env)
                : Connection(Env)
        {
        }

        RedisConnection::~RedisConnection()
        {
            Disconnect();
        }

        bool RedisConnection::Connect(ErrorCode& Code)
        {
            _pRawContext = redisConnect(_Enviorment._Ip.c_str(), _Enviorment._Port);
            if(_pRawContext == nullptr)
            {
                return false;
            }
            else if(_pRawContext->err)
            {
                RedisError::Throw(_pRawContext, __FILE__, __FUNCTION__, __LINE__);
                redisFree(_pRawContext);
                return false;
            }

            if(_Enviorment._Password.length() > 0)
            {
                RedisAuthCommand Command(shared_from_this(), _Enviorment._Password);
                if(!Command.Do(Code))
                {
                    return false;
                }
            }

            return true;
        }

        bool RedisConnection::Disconnect()
        {
            if(nullptr == _pRawContext)
            {
                return false;
            }

            redisFree(_pRawContext);
            return true;
        }

        redisContext *RedisConnection::GetRedisContext()
        {
            return _pRawContext;
        }
    }
}

#endif
