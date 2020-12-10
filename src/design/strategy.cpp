#include <iostream>
using namespace std;

/*策略模式--------行为模式*/

/*
//
//trategy模式和Template模式的根本区别是Strategy通过组合方式实现算法（实现）的异构， 而Template模式则采取的是继承的方式，
//这两个模式的区别也是继承和组合两种实现接口重用的方式的区别
//
*/

class strategy
{
public:
	virtual ~strategy()
	{

	}

	virtual void method() = 0;

protected:
	strategy()
	{

	}
};

class strategy_a : public strategy
{
public:
	strategy_a()
	{

	}

	~strategy_a()
	{

	}

	void method()
	{
		cout << "strategy_a::method" << endl;
	}
};

class strategy_b : public strategy
{
public:
	strategy_b()
	{

	}

	~strategy_b()
	{

	}

	void method()
	{
		cout << "strategy_b::method" << endl;
	}
};


class context
{
public:
	context(strategy* p)
	{
		m_strategy = p;
	}

	~context()
	{

	}

	void method()
	{
		m_strategy->method();
	}
	
private:
	strategy* m_strategy;
};

#if 0
int main()
{
	strategy_b b;

	context c(&b);
	c.method();
}

#endif

