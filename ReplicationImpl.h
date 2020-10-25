#pragma once

#include "TypeDefine.h"

namespace Replication
{
	class IReplicationImpl
	{
	public:
		virtual void NotifyPublish(const PublishParameters& Parameters) = 0;
		virtual void RegisterSubscribe(const SubscribeParameters& Parameters) = 0;
		virtual void UnRegisterSubscribe(const SubscribeParameters& Parameters) = 0;
	};
}