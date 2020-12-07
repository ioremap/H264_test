#include <iostream>
using namespace std;


#define FACTORY_METHOD


#ifdef SIMPLE_FACTORY

/*简单工厂模式---创建型模式*/
/*
//工厂类角色：这是本模式的核心，含有一定的商业逻辑和判断逻辑。
//抽象产品角色：它一般是具体产品继承的父类或者实现的接口。
//具体产品角色：工厂类所创建的对象就是此角色的实例。
//缺点：对修改不封闭，新增加产品需要修改工厂。违反了开闭法则（OCP）。
*/

class product
{
public:
	virtual ~product()
	{
	}

	virtual void show_type() = 0;
	
protected:
	product()
	{
	}
};


class product1 : public product
{
public:
	product1()
	{
	}
	
	~product1()
	{
	}

	void show_type()
	{
		cout<< "product1" << endl;
	}
};

class product2 : public product
{
public:
	product2()
	{
	}
	
	~product2()
	{
	}

	void show_type()
	{
		cout<< "product2" << endl;
	}
};

class factory
{
public:
	factory()
	{
	}
	
	~factory()
	{
	}

	product* create_product(int type)
	{
		switch(type)
		{
			case 1:
			{
				return new product1();
			}

			case 2:
			{
				return new product2();
			}

			default:
				return NULL;
		}

	}

};

#endif




#ifdef FACTORY_METHOD
/*工厂方法模式*/
/*
//抽象工厂角色： 这是工厂方法模式的核心，它与应用程序无关。是具体工厂角色必须实现的接口或者必须继承的父类。
//具体工厂角色：它含有和具体业务逻辑有关的代码。由应用程序调用以创建对应的具体产品的对象。
//抽象产品角色：它是具体产品继承的父类或者是实现的接口。
//具体产品角色：具体工厂角色所创建的对象就是此角色的实例。
//缺点：每增加一种产品，就需要增加一个对象的工厂
*/
class product
{
public:
	virtual ~product()
	{
	}

	virtual void show_type() = 0;
	
protected:
	product()
	{
	}
};


class product1 : public product
{
public:
	product1()
	{
	}
	
	~product1()
	{
	}

	void show_type()
	{
		cout<< "product1" << endl;
	}
};

class product2 : public product
{
public:
	product2()
	{
	}
	
	~product2()
	{
	}

	void show_type()
	{
		cout<< "product2" << endl;
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

	virtual product* create_product() = 0;
};

class factory1 : public factory
{
public:
	factory1()
	{

	}

	~factory1()
	{

	}

	product* create_product()
	{
		return new product1();
	}
};

class factory2 : public factory
{
public:
	factory2()
	{

	}

	~factory2()
	{

	}

	product* create_product()
	{
		return new product2();
	}
};
#endif

#if 0
int main()
{
	#ifdef SIMPLE_FACTORY
	factory my_factory;

	product* p1 = my_factory.create_product(1);
	p1->show_type();

	product* p2 = my_factory.create_product(2);
	p2->show_type();
	#endif


	#ifdef FACTORY_METHOD
	factory1 f1;
	product* p1 = f1.create_product();
	p1->show_type();

	factory2 f2;
	product* p2 = f2.create_product();
	p2->show_type();
	#endif

}

#endif

