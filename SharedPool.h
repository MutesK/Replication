#pragma once

#include <cassert>
#include <vector>
#include <memory>

template <class Type>
class SharedPool final
{
	std::vector<std::shared_ptr<Type>> _Pool;
public:
	SharedPool() = default;
	~SharedPool() = default;

	void Add(std::shared_ptr<Type> Ptr)
	{
		_Pool.emplace_back(Ptr);
	}

	std::shared_ptr<Type> Acquire()
	{
		assert(~Empty());
		return *std::find_if(_Pool.begin(), _Pool.end(), [](const std::shared_ptr<Type>& Ptr)
			{
				return Ptr.use_count() == 1;
			});
	}

	bool Empty() const
	{
		return std::none_of(_Pool.begin(), _Pool.end(), [](const std::shared_ptr<Type>& Ptr)
			{
				return Ptr.use_count() == 1;
			});
	}
};