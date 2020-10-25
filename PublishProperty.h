#pragma once

#include "Common.h"
#include "Property.h"
#include "TypeDefine.h"
#include "ReplicationImpl.h"

#include <sstream>

namespace Replication
{
	using ReplicationImplPtr = std::shared_ptr<IReplicationImpl>;

	template <typename Type>
	class PublishProperty : public Property<Type>
	{
		PublishParameters			_Parameters;
		ReplicationImplPtr			_ReplicatorPtr;
	public:
		PublishProperty(const ReplicationImplPtr& Replicator, const ReplicationParameters& Parameters)
			:_Parameters(Parameters), _type(), _ReplicatorPtr(Replicator)
		{
			_Parameters.Value = "";
		}
	protected:
		virtual void OnChangedProperty() override
		{
			_Parameters.Value = std::to_string(_type);

			_ReplicatorPtr->NotifyPublish(_Parameters);
		}
	};



}