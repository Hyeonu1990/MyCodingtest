#include "MyVector.h"

void MyVector::Grow()
{
	_capacity++;
	MyObject* new_data = new MyObject[_capacity];
	for (int i = 0; i < _size; i++)
	{
		new_data[i] = data[i];
	}

	delete[] data;
	data = new_data;
}

MyVector::MyVector(int capacity)
{
	data = new MyObject[capacity];
	_capacity = capacity;
	_size = 0;
}

MyVector::MyVector(const MyVector& other)
{
	*this = other;
}

MyVector& MyVector::operator=(const MyVector& other)
{
	_capacity = other._capacity;
	_size = other._size;
	data = new MyObject[_capacity];
	for (int i = 0; i < _size; i++)
	{
		data[i] = other.data[i];
	}

	return *this;
}

MyVector::~MyVector()
{
	if (data != nullptr)
		delete[] data;
}

int MyVector::GetCapacity() const
{
	return _capacity;
}

int MyVector::GetSize() const
{
	return _size;
}

void MyVector::Add(int id)
{
	MyObject* myobj = new MyObject();
	myobj->_id = id;

	if (_size == _capacity)
	{
		Grow();
	}

	data[_size] = *myobj;
	_size++;
}

MyObject* MyVector::FindById(int MyObjectId) const
{
	for (int i = 0; i < _size; i++)
	{
		if (data[i]._id == MyObjectId)
			return &data[i];
	}

	return nullptr;
}

void MyVector::TrimToSize()
{
	_capacity = _size;
	MyObject* new_data = new MyObject[_capacity];
	if (data != nullptr)
	{
		for (int i = 0; i < _size; i++)
		{
			new_data[i] = data[i];
		}
		delete[] data;
	}
	data = new_data;
}

MyObject& MyVector::operator[](const size_t index)
{
	return data[index];
}

std::string MyVector::ToString() const
{
	std::string value;
	value += "Size : " + std::to_string(_size) + ", Capacity : " + std::to_string(_capacity) + "\n Data : ";
	for (int i = 0; i < _size; i++)
	{
		value += std::to_string(data[i]._id);

		if (i != _size - 1)
		{
			value += ", ";
		}
	}
	return value;
}

void MyVector::RemoveAll(int MyObjectId)
{
	MyObject* new_data = new MyObject[_capacity];
	
	for (int i = 0; i < _size; i++)
	{
		bool IsEmpty = true;
		for (int j = i; j < _size; j++)
		{
			if (data[j]._id != MyObjectId)
			{
				new_data[i] = data[j];
				data[j]._id = MyObjectId;
				IsEmpty = false;
				break;
			}
		}

		if (IsEmpty)
		{
			_size = i;
			break;
		}
	}

	delete[] data;
	data = new_data;
		
}

MyVector * MyVector::GroupById(int * numGroups)
{
	MyVector* group = new MyVector(_size);

	for (int i = 0; i < _size; i++)
	{
		if (group->FindById(data[i]._id) == nullptr)
		{
			group->Add(data[i]._id);
		}
	}

	group->TrimToSize();
	*numGroups = group->GetSize();

	return group;
}
