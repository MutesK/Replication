#pragma once

#include "TypeDefine.h"
#include "ConnectEnviorment.h"

namespace Replication
{
	class Connection abstract
	{
	protected:
		ConnectEnviorment _Enviorment;
	public:
		Connection(const ConnectEnviorment& Env);
		virtual ~Connection();

		virtual ErrorCode Connect() = 0;
		virtual bool Disconnect() = 0;
	};

}