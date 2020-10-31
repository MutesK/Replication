#pragma once

#include "Common.h"

namespace Replication
{
	using ErrorCode = uint64_t;
	struct ReplicationParameters
	{
		std::string  Channel;
	};

	struct PublishParameters : public ReplicationParameters
	{
		std::string  Value;

        PublishParameters() = default;
		PublishParameters(const ReplicationParameters& paranters)
        {
		    Channel = paranters.Channel;
        }
	};

	struct SubscribeParameters : public ReplicationParameters
	{
		std::function<void(const std::string& value)> UpdateCallback;

        SubscribeParameters() = default;
        SubscribeParameters(const ReplicationParameters& paranters)
        {
            Channel = paranters.Channel;
        }
	};

	enum class ReplicationMode
	{
		EMaster = 0,
		ESlave,
	};
}