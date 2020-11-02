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
			:_Parameters(Parameters), _ReplicatorPtr(Replicator)
		{
		    this->_type = Type();
			_Parameters.Value = "";
		}
		virtual ~PublishProperty()
        {
		    _ReplicatorPtr->UnRequestPublishOnce(_Parameters);
        }

        void operator=(Type value)
        {
            this->Set(value);
        }
	protected:
		virtual void OnChangedProperty() override
		{
			_Parameters.Value = std::to_string(this->_type);

			_ReplicatorPtr->RequestPublishOnce(_Parameters);
		}
	};



}