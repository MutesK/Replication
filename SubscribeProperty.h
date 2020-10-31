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
        SubscribeProperty(const ReplicationImplPtr& Replicator, const ReplicationParameters& Parameters)
			:_Parameters(Parameters), _ReplicatorPtr(Replicator)
		{
            this->_type = Type();
			_Parameters.UpdateCallback = [&](const std::string& Value)
			{
				OnUpdateValue(Value);
			};
			_ReplicatorPtr->UnRegisterSubscribe(_Parameters);
		}
		~SubscribeProperty()
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
			if constexpr (is_string<Type>::requires)
			{
				this->_type = Value;
			}
			else if (is_integer<Type>::requires)
			{
				this->_type = std::atoi(Value.c_str());
			}
			else if (is_float<Type>::requires)
			{
				this->_type = std::stof(Value.c_str());
			}
			else if (is_double<Type>::requires)
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