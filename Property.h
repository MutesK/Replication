#pragma once


template <typename Type>
class Property
{
protected:
	Type _type;
public:
	Property() = default;
	~Property() = default;

	virtual void Set(const Type& value)
	{
		_type = value;
		OnChangedProperty();
	}

	virtual Type Get()
	{
		return _type;
	}

	virtual void OnChangedProperty() = 0;
};