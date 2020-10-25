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
	};

	struct SubscribeParameters : public ReplicationParameters
	{
		std::function<void(const std::string& value)> UpdateCallback;
	};

	enum class ReplicationMode
	{
		EMaster = 0,
		ESlave,
	};
}