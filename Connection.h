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

		virtual bool Connect(ErrorCode& Code) = 0;
		virtual bool Disconnect() = 0;
	};

}