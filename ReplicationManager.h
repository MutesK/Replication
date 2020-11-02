#pragma once

#include "ConnectEnviorment.h"
#include "PublishProperty.h"
#include "SubscribeProperty.h"
#include "ReplicationImpl.h"

namespace Replication
{
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

		void Comsume();
	};
	template<typename Type>
	inline PublishProperty<Type> ReplicationManager::IssuedPublish(const ReplicationParameters& Parameters)
	{
		if (_Mode != ReplicationMode::EMaster)
			std::logic_error("Slave Mode can't called IssuedPublish");

		const auto Property = PublishProperty<Type>(_ReplicationImplPtr, Parameters);
        return Property;
	}
	template<typename Type>
	inline SubscribeProperty<Type> ReplicationManager::IssuedSubscribe(const ReplicationParameters& Parameters)
	{
		if (_Mode == ReplicationMode::EMaster)
            std::logic_error("Master Mode can't called IssuedSubscribe");

        const auto Property =  SubscribeProperty<Type>(_ReplicationImplPtr, Parameters);
        _ReplicationImplPtr->RegisterSubscribe(Property);

        return Property;
	}
}