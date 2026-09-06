#include <iostream>
#include <memory>
#include <string>
#include <initializer_list>
#include <memory>
#include <utility>
#include <vector>
using namespace std;
#pragma warning(disable:4996)

template<typename T>
class Vec
{
public:
	Vec() :elements(nullptr), first_free(nullptr), cap(nullptr) {}
	Vec(initializer_list<T> i1) :Vec()
	{
		range_initializer(i1.begin(), i1.end());
	}
	Vec(const T* s):Vec()
	{
		T *s1 = const_cast<T*>(s);
		while (*s1)
		{
			++s1;
		}
		range_initializer(s, ++s1);
	}
	Vec(const Vec& rhs) :Vec()
	{
		range_initializer(rhs.begin(), rhs.end());
	}
	Vec(Vec&& rhs) noexcept
		:elements(rhs.elements), first_free(rhs.first_free), cap(rhs.cap)
	{
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	Vec& operator=(const Vec&);
	Vec& operator=(Vec&&)noexcept;
	Vec& operator = (initializer_list<T>);
	~Vec() { free(); }

	void push_back(const T&);
	void push_back(T&&);


	size_t size()const { return first_free - elements; }
	size_t capacity()const { return cap - elements; }
	T* begin()const { return elements; }
	T* end()const { return first_free; }

	Vec& operator[](int index)
	{
		return elements[index];
	}
	friend Vec<T> operator+(const Vec<T> &lhs, const Vec<T> &rhs)
	{
		Vec v(lhs);
		v += rhs;
		return v;
	}
	Vec<T>& operator+=( const Vec<T> &rhs)
	{
		auto newlen = (end() - begin() + (rhs.end() - rhs.begin()));
		allocator<T> newalloc;
		T *newdata = newalloc.allocate(newlen);
		T *dest = newdata, *elem = elements;
		for (size_t i= 0; 
			(sizeof(*elem)!=1)? 
			i < size():
			i<size()-1;
			++i)
			newalloc.construct(dest++, std::move(*elem++));
		free();//ÊÍ·Å¾ÉÖµ
		elem = rhs.elements;
		for (size_t i= 0; i < rhs.size(); ++i)
			newalloc.construct(dest++, *elem++);
		alloc = newalloc;
		elements = newdata;
		first_free = dest;
		cap = elements + newlen;
		return *this;
	}

	void reserve(size_t);
	void resize(size_t);
	void resize(size_t, const T&);
	friend ostream& operator<< <T>(ostream&,const Vec<T>&);
private:
	void chk_n_alloc()
	{
		if (size() == capacity())
		{
			reallocate();
		}
	}
	void free();
	pair<T*, T*> alloc_n_copy(const T*, const T*);
	void range_initializer(const T*, const T*);
	void reallocate();
	void alloc_n_mvoe(size_t);
	static allocator<T> alloc;
	T *elements, *first_free, *cap;
};
template<typename T>
allocator<T> Vec<T>::alloc;
template<typename T>
ostream& operator<<(ostream& os, const Vec<T> &rhs)
{
	T *beg = rhs.elements;
	if (sizeof(*beg) != 1)
	{
		while (beg != rhs.end())
		{
			os << *beg++ << "\t";
		}
	}
	else
		os << rhs.begin();
	return os <<"\n";
}
template<typename T>
Vec<T>& Vec<T>::operator=(const Vec<T> &rhs)
{
	if (this != &rhs)
	{
		range_initializer(rhs.begin(), rhs.end());
	}
	return *this;
}
template<typename T>
Vec<T>& Vec<T>::operator=(Vec<T> &&rhs)noexcept
{
	if (this != &rhs)
	{
		free();
		elements = rhs.elements;
		first_free = rhs.first_free;
		cap = rhs.cap;
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}
template<typename T>
Vec<T>& Vec<T>::operator=(initializer_list<T> i1)
{
	range_initializer(i1.begin(), i1.end());
	return *this;
}
template<typename T>
void Vec<T>::push_back(const T &t)
{
	chk_n_alloc();
	alloc.construct(first_free++, t);
}
template<typename T>
void Vec<T>::push_back(T &&t)
{
	chk_n_alloc();
	alloc.construct(first_free++, std::move(t));
}
template<typename T>
void Vec<T>::reserve(size_t new_cap)
{
	if (new_cap > size())
		alloc_n_mvoe(new_cap);
}

template<typename T>
void Vec<T>::resize(size_t count)
{
	resize(count, T());
}
template<typename T>
void Vec<T>::resize(size_t count, const T& t)
{
	if (count > size())
	{
		if (count > capacity())
			reserve(count * 2);
		for (size_t i = size(); i < count; ++i)
			alloc.construct(first_free++, t);
	}
	else if (count < size())
	{
		while (first_free != elements + count)
		{
			--first_free;
			alloc.destroy(first_free);
		}
	}
}
template<typename T>
void Vec<T>::free()
{
	if (elements)
	{
		for (T *p = first_free; p != elements;)
		{
			--p;
			alloc.destroy(p);
		}
		alloc.deallocate(elements, cap - elements);
	}
}
template<typename T>
pair<T*, T*> Vec<T>::alloc_n_copy(const T* b, const T *e)
{
	T *data = alloc.allocate(e - b);
	return make_pair(data, uninitialized_copy(b, e, data));
}
template<typename T>
void Vec<T>::range_initializer(const T *b, const T *e)
{
	pair<T*, T*> newdata = alloc_n_copy(b, e);
	free();
	elements = newdata.first;
	first_free = cap = newdata.second;
}
template<typename T>
void Vec<T>::reallocate()
{
	auto newcapacity = size() ? size() * 2 : 1;
	alloc_n_move(newcapacity);
}
template<typename T>
void Vec<T>::alloc_n_mvoe(size_t newcapacity)
{
	T *newdata = alloc.allocate(newcapacity);
	T *dest = newdata, *elem = elements;
	for (size_t i = 0; i < size(); ++i)
		alloc.construct(dest++, std::move(*elem++));
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}
int main()
{
	Vec<int> vi{ 45,78,99,23,1,44,3,89,7 }, vi1;
	cout << vi;
	vi = { 55,66,77,0 };
	cout << vi;
	vi1 = { 77,88 };
	cout << vi1;
	vi += vi1;
	cout << vi;

	Vec<char> vc = { "abcde" }, vc1{ "fghijk" };
	vc += vc1;
	cout << vc;
	char ch[30];
	memset(ch, 0, 30);
	strcpy(ch, vc.begin());
	cout << ch << endl;

	Vec<double> vd{ 5.678,7.9,6.30 }, vd1{ 97,7.7,9,9 };
	Vec<double> vd2 = vd + vd1;
	cout << vd2;
	system("pause");
	return 0;
}
