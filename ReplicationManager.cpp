#include "Common.h"
#include "TypeDefine.h"
#include "ConnectEnviorment.h"
#include "ReplicationManager.h"
#include "ConnectionPool.h"
#include "RedisConnection.hpp"
#include "RedisReplicationImpl.hpp"

namespace Replication
{
	class ReplicationMethodSelector
	{
	public:
		static std::shared_ptr<IReplicationImpl> CreateReplicationMethod(ReplicationMode ModeType,
			const ConnectEnviorment& Env)
		{
#if defined(REPLICATION_REDIS)
            static auto Ptr = std::shared_ptr<ConnectionPool<::Replication::Redis::RedisConnection>>
            (new ConnectionPool<::Replication::Redis::RedisConnection>(Env));

            switch(ModeType)
            {
                case ReplicationMode::EMaster:
                    return std::make_shared<Redis::RedisPublishReplicationImpl>(Ptr);
                case ReplicationMode::ESlave:
                    return std::make_shared<Redis::RedisSubscribeReplicationImpl>(Ptr);
#endif
            }

		    std::logic_error("");
            return nullptr;
		}
	};

	bool ReplicationManager::Initialize(const ReplicationMode ModeType, const ConnectEnviorment& Env)
	{
		if (nullptr != _ReplicationImplPtr)
			return false;

		_Mode = ModeType;
		_ConnectEnviorment = Env;

		_ReplicationImplPtr = ReplicationMethodSelector::CreateReplicationMethod(ModeType, Env);
		if (nullptr == _ReplicationImplPtr)
			return false;

		return true;
	}

    void ReplicationManager::Comsume()
    {
        if(nullptr == _ReplicationImplPtr)
            return;

        _ReplicationImplPtr->Comsume();
    }
}