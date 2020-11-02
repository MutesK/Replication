#pragma once

#include "Common.h"

namespace Replication
{
	using ErrorCode = uint64_t;
	struct ReplicationParameters
	{
		std::string  Channel;

        ReplicationParameters() = default;
        ReplicationParameters(const std::string& ChannelName)
        :Channel(ChannelName)
        {
        }
        ReplicationParameters(const ReplicationParameters& paramters)
        {
		    Channel = paramters.Channel;
        }
	};

	struct PublishParameters : public ReplicationParameters
	{
		std::string  Value;

        PublishParameters() = default;
		PublishParameters(const ReplicationParameters& parameters)
		:ReplicationParameters(parameters)
        {
        }
	};
	using ChannelPerPublishParameterMap = std::unordered_map<std::string, PublishParameters>;


	struct SubscribeParameters : public ReplicationParameters
	{
		std::function<void(const std::string& value)> UpdateCallback;

        SubscribeParameters() = default;
        SubscribeParameters(const ReplicationParameters& parameters)
        :ReplicationParameters(parameters)
        {
        }
	};
    using ChannelPerSubscribeParameterMap = std::unordered_map<std::string, SubscribeParameters>;



    enum class ReplicationMode
	{
		EMaster = 0,
		ESlave,
	};
}