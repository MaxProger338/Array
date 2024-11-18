#define COF_CAPACITY 1.2

#include <iostream>
#include <initializer_list>
using namespace std;

typedef unsigned int uint;

template<typename T>
class Array
{
	private:
		T* _arr;
		uint _size;
		uint _capacity;

	public:
		Array(): Array(0) {}

		Array(uint capacity)
		{
			_arr      = new T[capacity];
			_size     = 0;
			_capacity = capacity;
		}

		Array(const initializer_list<T>& list) : Array(list.size() * COF_CAPACITY)
		{
			uint index = 0;
			for (auto i : list)
			{
				_arr[index++] = i;
			}

			_size = list.size();
		}

		Array(const Array& arr): Array(arr._capacity)
		{
			for (size_t i = 0; i < arr._size; i++)
			{
				_arr[i] = arr._arr[i];
			}

			_size = arr._size;
		}

		Array(Array&& arr)
		{
			_arr      = arr._arr;
			_size     = arr._size;
			_capacity = arr._capacity;

			arr._arr = nullptr;
		}

		~Array()
		{
			delete _arr;
			_arr	  = nullptr;
			_size     = 0;
			_capacity = 0;
		}

		bool isEmpty() const
		{
			return _size == 0;
		}

		uint getSize() const
		{
			return _capacity;
		}

		uint getCurrentSize() const
		{
			return _size;
		}

		Array& setSize(uint size, uint capacity = 1)
		{
			if (capacity < size)
				capacity = size * COF_CAPACITY;

			T* newArr = new T[capacity];

			for (size_t i = 0; i < min(_size, size); i++)
			{
				newArr[i] = _arr[i];
			}

			_capacity = capacity;
			_size     = size;

			delete[] _arr;
			_arr = newArr;

			return *this;
		}

		uint getUpperBound() const
		{
			return _size - 1;
		}

		Array& freeExtra()
		{
			_capacity = _size;

			T* newArr = new T[_size];
			for (size_t i = 0; i < _size; i++)
			{
				newArr[i] = _arr[i];
			}

			delete[] _arr;
			_arr = newArr;

			return *this;
		}

		Array& removeAll()
		{
			~Array();

			return *this;
		}

		T getAt(uint index)
		{
			if (index >= _size)
				throw "Out of range";

			return _arr[index];
		}

		Array& setAt(uint index, T value)
		{
			if (index >= _size)
				throw "Out of range";

			_arr[index] = value;

			return *this;
		}

		Array& add(T value)
		{
			if (_size == _capacity)
			{
				setSize(_size + 1);
			} 
			else
			{
				_size++;
			}

			_arr[_size - 1] = value;

			return *this;
		}

		Array& getData() const
		{
			return *this;
		}

		Array& append(const Array& arr)
		{
			T* newArr = new T[_capacity + arr._capacity];
			for (size_t i = 0; i < _size; i++)
			{
				newArr[i] = _arr[i];
			}

			for (size_t i = 0; i < arr._size; i++)
			{
				newArr[i + _size] = arr._arr[i];
			}

			_capacity += arr._capacity;
			_size     += arr._size;

			delete _arr;
			_arr = newArr;

			return *this;
		}

		Array& insertAt(uint index, T value)
		{
			if (index >= _size)
				throw "Out of range";

			if (_size == _capacity)
			{
				setSize(_size + 1);
			}
			else
			{
				_size++;
			}

			for (size_t i = _size; i > index; i--)
			{
				_arr[i] = _arr[i - 1];
			}
			_arr[index] = value;

			return *this;
		}

		Array& removeAt(uint index)
		{
			if (index >= _size)
				throw "Out of range";

			for (size_t i = index; i < _size; i++)
			{
				_arr[i] = _arr[i + 1];
			}
			
			_size--;

			return *this;
		}

		T& operator[](uint index)
		{
			return getAt(index);
		}

		Array& operator()(uint index, T value)
		{
			return setAt(index, value);
		}

		friend ostream& operator<<(ostream& out, const Array& arr)
		{
			for (size_t i = 0; i < arr._size; i++)
			{
				out << arr._arr[i] << '\t';
			}
			out << endl;

			return out;
		}
};

int main()
{
	Array<int> arr(5);

	arr.add(1);
	arr.add(2);
	arr.add(3);

	cout << arr << endl;

	return 0;
}
