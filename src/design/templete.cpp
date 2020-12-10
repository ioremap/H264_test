#include <iostream>
using namespace std;

/*模板模式-----------行为模式*/
/*
//模板模式是一种行为型模式，它用来定义一个算法的框架，而将一些步骤延迟到子类中。模板方法模式
//使得子类可以不改变一个算法的结构即可重定义该算法的某些特定步骤
*/

class abstract_class
{
public:
	virtual ~abstract_class()
	{

	}

	void templete_method()
	{
		method1();
		method2();
	}

	virtual void method1() = 0;
	virtual void method2() = 0;

protected:
	abstract_class()
	{

	}
};

class class1:public abstract_class
{
public:
	class1()
	{

	}

	~class1()
	{

	}

	void method1()
	{
		cout << "class1::method1" << endl;
	}

	void method2()
	{
		cout << "class1::method2" << endl;
	}
};

class class2:public abstract_class
{
public:
	class2()
	{

	}

	~class2()
	{

	}

	void method1()
	{
		cout << "class2::method1" << endl;
	}

	void method2()
	{
		cout << "class2::method2" << endl;
	}
};

#if 0
int main()
{

	class1 a1;
	a1.templete_method();

	class2 b1;
	b1.templete_method();
}
#endif
