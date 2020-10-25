#pragma once

#include "Common.h"
#include "Property.h"
#include "TypeDefine.h"
#include "ReplicationImpl.h"
#include "TypeTraits.h"

namespace Replication
{
	using ReplicationImplPtr = std::shared_ptr<IReplicationImpl>;

	template <typename Type>
	class SubscribeProperty final : public Property<Type>
	{
		SubscribeParameters			_Parameters;
		ReplicationImplPtr			_ReplicatorPtr;
	public:
		PublishProperty(const ReplicationImplPtr& Replicator, const ReplicationParameters& Parameters)
			:_Parameters(Parameters), _type(), _ReplicatorPtr(Replicator)
		{
			_Parameters.UpdateCallback = [&](const std::string& Value)
			{
				OnUpdateValue(Value);
			}
			_Parameters.Value = "";

			_ReplicatorPtr->UnRegisterSubscribe(_Parameters);
		}
		~PublishProperty()
		{
			_ReplicatorPtr->UnRegisterSubscribe(_Parameters);
		}
	protected:
		virtual void Set(const Type& value) override
		{
		}

		virtual void OnChangedProperty() override
		{
		}

		void OnUpdateValue(const std::string& Value)
		{
			if constexpr (is_string<Type>)
			{
				this->_type = Value;
			}
			else if (is_integer<Type>)
			{
				this->_type = std::atoi(Value.c_str());
			}
			else if (is_float<Type>)
			{
				this->_type = std::stof(Value.c_str());
			}
			else if (is_double<Type>)
			{
				this->_type = std::stod(Value.c_str());
			}
			else
			{
				std::logic_error("");
			}
		}
	};



}