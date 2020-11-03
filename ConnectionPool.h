#pragma once

#include "TypeDefine.h"
#include "Common.h"
#include "SharedPool.h"
#include "Connection.h"
#include "ConnectEnviorment.h"
#include "ConnectionPool.h"

namespace Replication
{
	template <class DerivedConnectionType>
	class ConnectionPool
	{
		static_assert(std::is_base_of_v<Connection, DerivedConnectionType>, "Connection Pool class Type Only Dervied by Connection Class");

		ConnectEnviorment						_Enviorment;
		SharedPool<DerivedConnectionType>		_SharedPool;
	public:
		ConnectionPool(const ConnectEnviorment& Env);

		std::shared_ptr<DerivedConnectionType> Acquire();
	};
	template<class DerivedConnectionType>
	inline ConnectionPool<DerivedConnectionType>::ConnectionPool(const ConnectEnviorment& Env)
	{
		for (size_t Count = 0; Count < Env._ConnectionSize; ++Count)
		{
		    ErrorCode Code;
			auto Connection = std::make_shared<DerivedConnectionType>(Env);

			if (false == Connection->Connect(Code))
			{
				--Count;
				continue;
			}

			_SharedPool.Add(std::move(Connection));
		}
	}
	template<class DerivedConnectionType>
	inline std::shared_ptr<DerivedConnectionType> ConnectionPool<DerivedConnectionType>::Acquire()
	{
		return _SharedPool.Acquire();
	}
}