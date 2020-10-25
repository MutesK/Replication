#include "Common.h"
#include "TypeDefine.h"
#include "ConnectEnviorment.h"
#include "ReplicationManager.h"
#include "ReplicationImpl.h"


namespace Replication
{
	class ReplicationMethodSelector
	{
	public:
		static std::shared_ptr<IReplicationImpl> CreateReplicationMethod(ReplicationMode ModeType,
			const ConnectEnviorment& Env)
		{

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
}