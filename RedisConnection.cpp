//
// Created by JunMin Kim on 2020/10/31.
//


#include "RedisCommon.h"
#include "RedisConnection.hpp"

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

        ErrorCode RedisConnection::Connect()
        {
            _pRawContext = redisConnect(_Enviorment._Ip.c_str(), _Enviorment._Port);
            if(_pRawContext == nullptr)
            {
                return -1;
            }
            else if(_pRawContext->err)
            {
                redisFree(_pRawContext);
                return _pRawContext->err;
            }

            if(_Enviorment._Password.length() > 0)
            {
                // AUTH
            }

            return 0;
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
    }
}
