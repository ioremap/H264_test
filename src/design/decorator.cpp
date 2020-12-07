#include <iostream>
#include <string>
using namespace std;

/*装饰模式---结构型模式*/

/*
//有时候我们需要为一个已经定义好的类添加新的操作，通常的情况我们会给定义一个新类继承自定义好的类，
//这样会带来一个问题，通过继承的方式解决这样的情况还带来了系统的复杂性，因为继承的深度会变得很深
//
//有时我们希望给某个对象而不是整个类添加一些功能。一种灵活的设计方式是，将对象嵌入到另一对象中，由这个对象完成特性的添加，
//我们称这个嵌入的对象为装饰。这个装饰与它所装饰的组件接口一致，因此它对使用该组件的客户透明。
*/


class phone
{
public:
	virtual ~phone()
	{
		cout << "~phone" << endl;
	}

	virtual void show() = 0;
	
protected:
	phone()
	{
		cout << "phone" << endl;
	}
};

class xiaomi_phone : public phone
{
public:
	xiaomi_phone()
	{
		cout << "xiaomi_phone" << endl;
	}

	~xiaomi_phone()
	{
		cout << "~xiaomi_phone" << endl;
	}

	void show()
	{
		cout << "xiaomi_phone show" << endl;
	}
};

class phone_decorator : public phone
{
public:
	phone_decorator(phone* p)
	{
		cout << "phone_decorator" << endl;
		mphone = p;
	}

	virtual ~phone_decorator()
	{
		cout << "~phone_decorator" << endl;
	}

	virtual void show()
	{
		cout << "phone_decorator::show" << endl;
		
		mphone->show();
	}


	phone* mphone;

};


class phone_decorator_a : public phone_decorator
{
public:
	phone_decorator_a(phone* p):phone_decorator(p)
	{
		cout << "phone_decorator_a" << endl;
	}

	~phone_decorator_a()
	{
		cout << "~phone_decorator_a" << endl;
	}

	void show()
	{
		cout << "phone_decorator_a show" << endl;
		
		mphone->show();

		fun1();
	}

	void fun1()
	{
		cout << "phone_decorator_a::fun1()" << endl;
	}

};


class phone_decorator_b : public phone_decorator
{
public:
	phone_decorator_b(phone* p):phone_decorator(p)
	{
		cout << "phone_decorator_b" << endl;
	}

	~phone_decorator_b()
	{
		cout << "~phone_decorator_b" << endl;
	}

	void show()
	{
		cout << "phone_decorator_b show" << endl;
		
		mphone->show();

		fun2();
	}

	void fun2()
	{
		cout << "phone_decorator_b::fun2()" << endl;
	}

};

int main()
{
	xiaomi_phone mi_phone;

	cout << "---------------------------------" << endl;

	phone_decorator_a* phone_a = new phone_decorator_a(&mi_phone);
	phone_a->show();

	cout << "---------------------------------" << endl;

	phone_decorator_b* phone_b = new phone_decorator_b(phone_a);
	phone_b->show();

	delete phone_a;
	delete phone_b;
}


