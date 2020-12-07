#include <iostream>
#include <string>
using namespace std;

/*桥接模式---结构型模式*/

/*
//将抽象(Abstraction)与实现(Implementation)分离，使得二者可以独立地变化。
//举例：
//手机品牌和软件是两个概念，不同的软件可以在不同的手机上，不同的手机可以有相同的软件，两者都具有很大的变动性。
//如果我们单独以手机品牌或手机软件为基类来进行继承扩展的话，无疑会使类的数目剧增并且耦合性很高
//如果将两者抽象出来两个基类分别是PhoneBrand和PhoneSoft，那么在品牌类中聚合一个软件对象的基类将解决软件和手机扩展
//混乱的问题，这样两者的扩展就相对灵活，剪短了两者的必要联系
//
//Bridge用于将表示和实现解耦,两者可以独立的变化.在Abstraction类中维护一个AbstractionImplement类指针,需要采用不同的
//实现方式的时候只需要传入不同的AbstractionImplement派生类就可以了
*/

class phone_software
{
public:
	virtual ~phone_software()
	{

	}

	virtual void operation() = 0;
protected:
	phone_software()
	{

	}
};

class app1 : public phone_software
{
public:
	app1()
	{

	}

	~app1()
	{

	}

	void operation()
	{
		cout << "app1 run!" << endl;
	}

};

class app2 : public phone_software
{
public:
	app2()
	{

	}

	~app2()
	{

	}

	void operation()
	{
		cout << "app2 run!" << endl;
	}

};


class phone
{
public:
	virtual ~phone()
	{

	}

	virtual void operation() = 0;

	phone_software* my_software;
	
protected:
	phone()
	{

	}		
};


class huawei_phone : public phone
{
public:
	huawei_phone(phone_software* pware)
	{
		my_software = pware;
	}

	~huawei_phone()
	{
		delete my_software;
	}

	void operation()
	{
		my_software->operation();
	}
};

class xiaomi_phone : public phone
{
public:
	xiaomi_phone(phone_software* pware)
	{
		my_software = pware;
	}

	~xiaomi_phone()
	{
		delete my_software;
	}

	void operation()
	{
		my_software->operation();
	}
};


#if 0
int main()
{
	phone_software* papp1 = new app1();
	phone_software* papp2 = new app2();

	huawei_phone hp(papp1);
	hp.operation();

	xiaomi_phone mp(papp2);
	mp.operation();

}
#endif

