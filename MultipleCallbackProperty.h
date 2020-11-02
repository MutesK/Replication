#pragma once


#include "Property.h"
#include "Common.h"

template <typename Type>
class MultipleCallbackProperty : public Property<Type>
{
public:
	using OnChangedDelegate = std::function<void(Type)>;
private:
	Type						 _Type;
	std::list<OnChangedDelegate> _Delegates;

public:
	virtual void Set(const Type& value) override
	{
        _Type = value;
	
		std::for_each(_Delegates.begin(), _Delegates.end(), [&](const auto& Delegate)
			{
				Delegate(_Type);
			});
	}

	void AddCallback(const OnChangedDelegate&& RefDelegate)
	{
		_Delegates.emplace_back(RefDelegate);
	}

private:
	virtual void OnChangedProperty() override
	{
		// Not to Run
	}
};
