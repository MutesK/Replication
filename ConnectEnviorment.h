#pragma once

#include <string>

namespace Replication
{
	struct ConnectEnviorment
	{
		std::string _Ip;
		uint16_t    _Port;
		
		std::string	_Password;
		std::size_t _ConnectionSize;
	};
}