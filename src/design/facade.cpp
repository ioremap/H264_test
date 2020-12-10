#include <iostream>
using namespace std;


/*外观模式---------结构型模式*/

/*
//
//提供一个外观类，负责对外打交道的门户，它屏蔽了子系统内部特定的调用关系，简化接口的使用
//
*/

class subsystem1
{
public:
	subsystem1()
	{

	}

	~subsystem1()
	{

	}

	void operation()
	{
		cout << "subsystem1::operation" << endl;
	}

};

class subsystem2
{
public:
	subsystem2()
	{

	}

	~subsystem2()
	{

	}

	void operation()
	{
		cout << "subsystem2::operation" << endl;
	}

};

class facade
{
public:
	facade()
	{
		psys1 = new subsystem1();
		psys2 = new subsystem2();
	}

	~facade()
	{
		delete psys1;
		delete psys2;
	}

	void operation()
	{
		psys1->operation();
		psys2->operation();
	}
private:
	subsystem1* psys1;
	subsystem2* psys2;
};

#if 0
int main()
{
	facade f1;
	f1.operation();

}

#endif

