#include <iostream>
using namespace std;


/*代理模式------结构型模式*/

/*
//代理模式也称为委托模式,作用就是找一个对象来替我们访问某个对象
//
//虚拟代理:
//虚拟代理的主要目的是实现延迟。一个可以在文档中嵌入图形对象的文档编辑器。有些图形对象的创建开销很大。
//但是打开文档必须很迅速，因此我们在打开文档时应避免一次性创建所有开销很大的对象。这里就可以运用代理模式，
//在打开文档时，并不打开图形对象，而是打开图形对象的代理以替代真实的图形。待到真正需要打开图形时，仍由代理负责打开。
//
//
//远程代理:
//多见于通讯，如网络、IPC和RPC中
//
//智能引用代理:
//最典型的应用就是智能指针的运用，相对于指针，智能指针就是对指针的代理,增加了引用计数
//
//
//安全代理:
//用来控制真实对象访问时的权限
//
//Subject:抽象主体角色，是一个普通的业务类型定义
//RealSubject:具体主体角色，也叫作被代理角色。业务逻辑的具体执行者
//Proxy代理主体角色，委托类，代理类
*/

class subject
{
public:

	virtual ~subject()
	{

	}

	virtual void request() = 0;
	
protected:
	subject()
	{

	}
};

class real_subject: public subject
{
public:
	real_subject()
	{

	}
	
	~real_subject()
	{

	}

	void request()
	{
		cout << "real_subject::request" << endl;
	}
};

class proxy: public subject
{
public:
	proxy(subject* p)
	{
		m_subject = p;
	}

	~proxy()
	{

	}

	void check()
	{

	}

	void request()
	{
		check();

		m_subject->request();		
	}
private:
	subject* m_subject;
};

#if 0
int main()
{
	real_subject r1;

	proxy p1(&r1);
	p1.request();
}

#endif

