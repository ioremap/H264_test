#include <iostream>
#include <string>
using namespace std;

/*适配器模式---结构型模式*/

/*
//将一个类的接口转换成客户希望的另外一个接口。Adapter模式使得原本由于接口不兼容而不能一起工作的那些类可以一起工作。
//比如购买的第三方开发组件，该组件接口与我们自己系统的接口不相同，或者由于某种原因无法直接调用该组件，可以考虑适配器。
//
//Target:目标接口类，客户需要的接口
//Adaptee:需要适配的类
//Adapter:适配器
//
//分为类模式/  对象模式 两种适配器
*/


/*对象模式*/
class target
{
public:
	target()
	{

	}

	virtual ~target()
	{

	}

	virtual void request()
	{

	}
};

class Adaptee
{
public:
	Adaptee()
	{

	}

	virtual ~Adaptee()
	{

	}

	void method()
	{
		cout << "Adaptee::method" << endl;
	}
};

class Adapter : public target, private Adaptee
{
public:
	Adapter()
	{

	}

	~Adapter()
	{

	}

	void request()
	{
		this->method();
	}
};

/*对象模式*/
class Adapter2
{
public:
	Adapter2(Adaptee* p)
	{
		pclass = p;
	}

	~Adapter2()
	{
	
	}

	void request()
	{
		pclass->method();
	}
private:
	Adaptee* pclass;
};


#if 0
int main()
{
	/*类模式*/
	Adapter a1;
	a1.request();

	/*对象模式*/
	Adaptee t1;
	Adapter2(&t1).request();

}
#endif

