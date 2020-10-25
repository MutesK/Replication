#pragma once

#include "PublishProperty.h"
#include "SubscribeProperty.h"

namespace Replication
{
	struct ConnectEnviorment;
	struct PublishParameters;
	struct SubscribeParameters;

	class IReplicationImpl;
	using ReplicationImplPtr = std::shared_ptr<IReplicationImpl>;

	class ReplicationManager final
	{
		ReplicationImplPtr								_ReplicationImplPtr = nullptr;

		ReplicationMode									_Mode;
		ConnectEnviorment								_ConnectEnviorment;
	public:
		ReplicationManager() = default;
		~ReplicationManager() = default;

		bool Initialize(const ReplicationMode ModeType, const ConnectEnviorment& Env);

		template <typename Type>
		PublishProperty<Type> IssuedPublish(const ReplicationParameters& Parameters);

		template <typename Type>
		SubscribeProperty<Type> IssuedSubscribe(const ReplicationParameters& Parameters);
	};
	template<typename Type>
	inline PublishProperty<Type> ReplicationManager::IssuedPublish(const ReplicationParameters& Parameters)
	{
		if (_Mode != ReplicationMode::EMaster)
			std::logic_error("");

		return PublishProperty<Type>(_ReplicationImplPtr, Parameters);
	}
	template<typename Type>
	inline SubscribeProperty<Type> ReplicationManager::IssuedSubscribe(const ReplicationParameters& Parameters)
	{
		if (_Mode == ReplicationMode::EMaster)
			std::logic_error("");

		return SubscribeProperty<Type>(_ReplicationImplPtr, Parameters);
	}
}