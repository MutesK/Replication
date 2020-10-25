#pragma once

namespace Replication
{
	class Connection;
	using ConnectionPtr = std::shared_ptr<Connection>;
	class Command abstract
	{
	protected:
		ConnectionPtr _ConnectionPtr;
	public:
		Command(const ConnectionPtr& Ptr);

		virtual void Do() = 0;
	};
}