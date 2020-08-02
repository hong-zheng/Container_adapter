容器适配器的实现Stack:

```cpp
// stack的实现
				// 底层实现容器默认为双端队列
template<class T,class Container = deque<T>>
class Stack
{
public:
	void push(const T& val)
	{
		_c.push_back(val);
	}

	void pop()
	{
		_c.pop_back();
	}

	const T& top()
	{
		return _c.back();
	}
	
	size_t size() const
	{
		return _c.size();
	}

	bool empty() const
	{
		return _c.empty();
	}
private:
	Container _c;
};
void testST()
{
	//Stack<int> st;
	//Stack<int, vector<int>> st;
	Stack<int, list<int>> st;
	st.push(12);
	st.push(42);
	st.push(22);
	st.push(92);

	while (!st.empty())
	{
		cout << st.top() << " ";
		st.pop();
	}
	cout << endl;
}
```

容器适配器实现队列queue

```cpp
// 利用容器适配器实现queue
template<class T,class Container=deque<T>>
class Queue
{
public:
	void push(const T& val)
	{
		_c.push_back(val);
	}

	void pop()
	{
		_c.pop_front();
	}

	T& front()
	{
		return _c.front();
	}

	T& back()
	{
		return _c.back();
	}

	size_t size() const
	{
		return _c.size();
	}

	bool empty() const
	{
		return _c.empty();
	}
private:
	Container _c;
};

void testQ()
{
	//Queue<int> q;
	// vector:不能实现，因为不能pop_front
	Queue<int, vector<int>> q;
	q.push(1);
	q.push(51);
	q.push(31);
	q.push(12);
	q.push(11);
	while (!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;
}

```

容器适配器实现优先级队列：

```cpp
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <deque>
#include <vector>
using namespace std;

// 仿函数：用作 priority_queue 的第三个参数，用来做比较定义
template<class T>
struct Less
{
	bool operator()(const T& val1, const T& val2)
	{
		return val1 < val2;
	}
};

template<class T>
struct Greater
{
	bool operator()(const T& val1, const T& val2)
	{
		return val1 > val2;
	}
};
/*
 容器适配器实现优先级队列
 1、默认容器为 vector
	用 vector 作为默认容器的理由：
		1、优先级的实现是堆结构，因此需要随机访问，相对于双端队列而言，vector的随机访问效率更高，而deque的虽然支持随机访问，但是在不同的缓冲区需要进行换算；
		2、不用 list 实现，因为 list 不支持随机访问

2、第三个参数 Compare 仿函数
实现对堆的大小的控制，增加了代码的灵活性
*/
template<class T,class Container = vector<T>,class Compare = Less<T>>
class Priority_Queue
{
public:
	void push(const T& val)
	{
		_c.push_back(val);
		shiftUp(_c.size() - 1);
	}

	void pop()
	{
		swap(_c[0], _c[_c.size() - 1]);
		_c.pop_back();
		shiftDown(0);
	}

	T& front()
	{
		return _c.front();
	}

	T& back()
	{
		return _c.back();
	}

	size_t size() const
	{
		return _c.size();
	}

	bool empty() const
	{
		return _c.empty();
	}
private:
	// 向下调整：和两个孩子作比较
	void shiftDown(int parent)
	{
		int child = 2 * parent + 1;

		while (child < _c.size())
		{
			if (child + 1 < _c.size() && _cmp(_c[child],_c[child + 1]))
				child++;
			if (_cmp(_c[parent],_c[child]))
			{
				swap(_c[child], _c[parent]);
				parent = child;
				child = 2 * parent + 1;
			}
			else
			{
				break;
			}
		}
	}

	// 向上调整：和父结点作比较
	void shiftUp(int child)
	{
		int   parent = (child - 1) >> 1;

		// 当父节点为 0 的时候也是可以调整的，因为此时孩子结点依然存在
		while (parent >= 0)
		{
			if (_cmp(_c[parent],_c[child]))
			{
				swap(_c[parent], _c[child]);
				child = parent;
				parent = (child - 1) >> 1;
			}
			else
			{
				break;
			}
		}
	}
private:
	Container _c;
	Compare _cmp;
};
void testpriorityqueueu()
{
	Priority_Queue<int, vector<int>, Greater<int>> pq;
	//Priority_Queue<int, vector<int>, Less<int>> pq;
	pq.push(1);
	pq.push(10);
	pq.push(13);
	pq.push(61);
	pq.push(41);
	pq.push(421);
	pq.push(410);
	pq.push(141);
	pq.push(12);
	pq.push(11);
	 // 1 12 13 41 61 11 10
   	 // 1 13 12 41 11 61 10
	while(!pq.empty())
	{
		cout << pq.front() << " ";
		pq.pop();
	}
	cout << endl;
}

struct Date
{
	Date(int y = 2020,int m = 8,int d = 2)
		:_y(y)
		, _m(m)
		, _d(d)
	{}

	bool operator<(const Date& d) const
	{
		if (_y < d._y)
		{
			return true;
		}
		else if (_y == d._y)
		{
			if (_m < d._m)
			{
				return true;
			}
			else if (_m == d._m)
			{
				if (_d < d._d)
					return true;
			}
		}
		return false;
	}

	bool operator>(const Date& d) const
	{
		if (_y > d._y)
		{
			return true;
		}
		else if (_y == d._y)
		{
			if (_m > d._m)
			{
				return true;
			}
			else if (_m == d._m)
			{
				if (_d > d._d)
					return true;
			}
		}
		return false;
	}
	int _y;
	int _m;
	int _d;
};

ostream& operator<<(ostream& cout, const Date& d)
{
	cout << d._y << "-" << d._m << "-" << d._d << endl;
	return  cout;
}
void testDate()
{
	// 自定义类型使用优先级队列，类模板中必须重定义"<,>"的规则，否则仿函数在调用的时候并不知道调用什么规则去做比较
	//Priority_Queue<Date, vector<Date>, Less<Date>> pq;
	Priority_Queue<Date, vector<Date>, Greater<Date>> pq;

	pq.push(Date(2020, 3, 23));
	pq.push(Date(2000, 9, 13));
	pq.push(Date(1990, 10, 30));
	pq.push(Date(3020, 3, 23));
	pq.push(Date(1020, 5, 13));
	pq.push(Date(2020, 4, 3));

	while (!pq.empty())
	{
		cout << pq.front();
		pq.pop();
	}
	cout << endl;
}
int main()
{
	testDate();
	//testpriorityqueueu();
	system("pause");
	return 0;
}
```
/*
容器适配器实现stack,queue and priority_queue总结：
1、容器适配器实现stack，默认用双端队列deque（指针数组（T**)+缓冲区(buffer)）
	和其他容器对比：vector：在此处的随机访问的最大优势得不到充分的发挥，stack不用随机访问；
								 list : 申请内存次数过于频繁，而且内存碎片问题较为严重；
2、容器适配器实现queue，默认使用双端队列deque（指针数组+缓冲区）
	和其他容器比较：vector：不使用随机访问
								list：内存碎片问题

3、容器适配器实现优先级队列 priority_queue 
模板参数三个 : template<class T , class Container = vector<T> , class Compare = Less<T>> 
第一个：T，所存数据类型；
第二个：容器适配器，缺省为vector，在优先级队列中，其中的优先顺序是用堆来实现的，因此在插入和删除的时候需要大量的向上与向下调整，因此对随机访问的效率要求比较高，虽然双端队列deque也支持随机访问，但是相对于vector的随机访问，deque的随机访问在不同缓冲区中需要用数组指针中的指针换算，因此需要更大的开销，所以相对而言，vector 的随机访问更加高效；
第三个：仿函数，定义一个类
	重写 bool operator()(const T& val1,const T& val2)函数；
4、shiftUp：堆的向上调整
shiftUp(int child)
参数：孩子结点位置
获得父节点位置，然后作比较再实施；
5、shiftDown(int parent) : 堆的向下调整
参数：父节点位置
从子节点中选择满足仿函数要求的结点再与父节点作比较，最后实施
6、自定义类型：需要使用仿函数对两个对象做比较，则需要在类模板中重写比较函数"<,>"，
例如：bool operator<(const Date& d) ;
函数中有两个对象：当前对象参数以及d，用这个对象定义比较规则，得到返回值
当程序运行调用仿函数作比较的时候，根据仿函数的参数模板T，找到具体的类模板，根据类模板中定义的函数对两个对象进行比较
*/