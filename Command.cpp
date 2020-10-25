#include "TypeDefine.h"
#include "Common.h"
#include "Connection.h"
#include "Command.h"

namespace Replication
{
	Command::Command(const ConnectionPtr& Ptr)
		:_ConnectionPtr(Ptr)
	{
	}
}
