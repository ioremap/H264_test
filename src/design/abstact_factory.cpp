#include <iostream>
using namespace std;

/*Factory 模式对于对象的创建给予开发人员提供了很好的实现策略，但是
Factory 模式仅仅局限于一类类（就是说 Product 是一类，有一个共同的基类），如果我们要
为不同类的类提供一个对象创建的接口，那就要用 AbstractFactory */


/*抽象工厂模式---创建型模式*/
/*
//抽象工厂模式和工厂方法模式的区别就在于需要创建对象的复杂程度上。
//AbstractFactory 模式是为创建一组（ 有多类） 相关或依赖的对象提
//供创建接口， 而 Factory 模式正如我在相应的文档中分析的是为一类对象提供创建接口或延
//迟对象的创建到子类中实现。
*/

class prodtct_type_car
{
public:
	virtual ~prodtct_type_car()
	{

	}

	virtual void show_type() = 0;
protected:
	prodtct_type_car()
	{

	}
};

class prodtct_type_phone
{
public:
	virtual ~prodtct_type_phone()
	{

	}

	virtual void show_type() = 0;
protected:
	prodtct_type_phone()
	{

	}
};


class bmw_car : public prodtct_type_car
{
public:
	bmw_car()
	{

	}

	~bmw_car()
	{

	}

	void show_type()
	{
		cout << "bmw_car" << endl;
	}
};

class benz_car : public prodtct_type_car
{
public:
	benz_car()
	{

	}

	~benz_car()
	{

	}

	void show_type()
	{
		cout << "benz_car" << endl;
	}
};


class iphone: public prodtct_type_phone
{
public:
	iphone()
	{

	}

	~iphone()
	{

	}

	void show_type()
	{
		cout<< "iphone" << endl;
	}
};

class mi_phone: public prodtct_type_phone
{
public:
	mi_phone()
	{

	}

	~mi_phone()
	{

	}

	void show_type()
	{
		cout<< "mi_phone" << endl;
	}
};





class factory
{
public:
	factory()
	{

	}

	virtual ~factory()
	{

	}

	virtual prodtct_type_car* create_car() = 0;
	virtual prodtct_type_phone* create_phone() = 0;
};

class factory_a : public factory
{
public:
	factory_a()
	{

	}

	~factory_a()
	{

	}

	prodtct_type_car* create_car()
	{
		return new bmw_car();
	}

	prodtct_type_phone* create_phone()
	{
		return new mi_phone();
	}
};

class factory_b : public factory
{
public:
	factory_b()
	{

	}

	~factory_b()
	{

	}

	prodtct_type_car* create_car()
	{
		return new benz_car();
	}

	prodtct_type_phone* create_phone()
	{
		return new iphone();
	}
};

#if 0
int main()
{
	factory_a fa;
	prodtct_type_car* pcar_a = fa.create_car();
	pcar_a->show_type();
	prodtct_type_phone* pphone_a = fa.create_phone();
	pphone_a->show_type();

	factory_b fb;
	prodtct_type_car* pcar_b = fb.create_car();
	pcar_b->show_type();
	prodtct_type_phone* pphone_b = fb.create_phone();
	pphone_b->show_type();

}
#endif

