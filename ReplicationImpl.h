#pragma once

#include "TypeDefine.h"

namespace Replication
{
	class IReplicationImpl
	{
	public:
	    // 휘발성
		virtual void RequestPublishOnce(const PublishParameters& Parameters) = 0;
        virtual void UnRequestPublishOnce(const PublishParameters& Parameters) = 0;

		// 지속성
		virtual void RegisterSubscribe(const SubscribeParameters& Parameters) = 0;
		virtual void UnRegisterSubscribe(const SubscribeParameters& Parameters) = 0;

		virtual void Comsume() = 0;
	};
}