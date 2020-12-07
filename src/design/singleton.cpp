#include <iostream>
#include <memory>
#include <mutex>

using namespace std;


/*单例模式---创建型模式*/
/*保证一个类仅有一个实例，并提供一个访问它的全局访问点，该实例被所有程序模块共享*/
/*需要系统中只有唯一一个实例存在的类的全局变量的时候才使用单例*/


/*懒汉式*/
/*
//单例实例在第一次被使用时才进行初始化，这叫做延迟初始化。
//这种模式存在内存泄露的问题  ，有两种解决方法：1.使用智能指针 2.使用静态的嵌套类对象
*/

/*饿汉式*/
/*
//在main函数之前初始化Singleton Singleton::instance，没有安全问题;
//但是static Singleton instance 和 static Singleton& getInstance()二者的初始化顺序不确定，如果在初始化完成之前
//调用 getInstance() 方法会返回一个未定义的实例。
*/

/*最好使用C++11支持的局部变量法，即版本六*/




/*版本一   ：存在线程安全问题、内存泄漏问题*/
class singleton_v1
{
public:
	~singleton_v1()
	{
		cout<< "singleton_v1 destory!!" << endl;
	}

	static singleton_v1* get_instance()
	{
		if(NULL == m_pinstance)
		{
			m_pinstance = new singleton_v1();
		}

		return m_pinstance;
	}

protected:
	singleton_v1()
	{
		cout<< "singleton_v1 create!" << endl;
	}
	
private:
	static singleton_v1* m_pinstance;
};





/*版本二，使用静态的嵌套类对象解决内存泄漏问题*/
class singleton_v2
{
private:
	class singleton_v2_deleter
	{
	public:
		singleton_v2_deleter()
		{
		}
		~singleton_v2_deleter()
		{
			if(NULL != singleton_v2::m_pinstance)
			{
				delete singleton_v2::m_pinstance;
			}
		}
	};

	static singleton_v2_deleter my_deleter;
	
public:
	~singleton_v2()
	{
		cout<< "singleton_v2 destory!!" << endl;
	}

	static singleton_v2* get_instance()
	{
		if(NULL == m_pinstance)
		{
			m_pinstance = new singleton_v2();
		}

		return m_pinstance;
	}

protected:
	singleton_v2()
	{
		cout<< "singleton_v2 create!" << endl;
	}

private:
	static singleton_v2* m_pinstance;
};
//singleton_v2* singleton_v2::m_pinstance = NULL;
//singleton_v2::singleton_v2_deleter singleton_v2::my_deleter;





/*版本三：使用智能指针解决内存泄漏问题(C++11)*/
class singleton_v3
{	
public:
	~singleton_v3()
	{
		cout<< "singleton_v3 destory!!" << endl;
	}

	static shared_ptr<singleton_v3> get_instance()
	{
		if(NULL == m_pinstance)
		{
			m_pinstance = (shared_ptr<singleton_v3>)(new singleton_v3());
		}

		return m_pinstance;
	}

protected:
	singleton_v3()
	{
		cout<< "singleton_v3 create!" << endl;
	}

private:
	static shared_ptr<singleton_v3> m_pinstance;
};
//shared_ptr<singleton_v3> singleton_v3::m_pinstance = NULL;





/*版本四, 使用智能指针解决内存泄漏问题(C++11),使用锁解决线程安全问题*/
class singleton_v4
{	
public:
	~singleton_v4()
	{
		cout<< "singleton_v4 destory!!" << endl;
	}

	static shared_ptr<singleton_v4> get_instance()
	{
		/*使用两重判断称为双检锁，是为了不用每次进入该函数都加锁，减小开销*/
		if(NULL == m_pinstance)
		{
			lock_guard<mutex> lock(m_mutex); /*lock对象在此创建时对m_mutex自动加锁，当离开该函数lock对象析构时自动对m_mutex解锁*/

			if(NULL == m_pinstance)
			{
				m_pinstance = (shared_ptr<singleton_v4>)(new singleton_v4());
			}		
		}

		return m_pinstance;
	}

protected:
	singleton_v4()
	{
		cout<< "singleton_v4 create!" << endl;
	}

private:
	static shared_ptr<singleton_v4> m_pinstance;
	static mutex m_mutex;
};
//shared_ptr<singleton_v4> singleton_v4::m_pinstance = NULL;
//mutex singleton_v4::m_mutex;





/*版本五 C++11*/
/*
//版本四中的双检锁可能会失效。m_pinstance = new singleton_v4()这条语句实际上做了三件事，第一件事申请一块内存，
//第二件事调用构造函数，第三件是将该内存地址赋给m_pinstance。
//不同的编译器表现是不一样的,可能先将该内存地址赋给m_pinstance，然后再调用构造函数。如果线程A恰好申请完成内存，并且将内存地址赋给m_pinstance，
//但是还没调用构造函数的时候。线程B执行到语句1，判断instance_此时不为空，则返回该变量，然后调用该对象的函数，但是该对象还没有进行构造。
//
//这种情况下需要使用内存屏障来保证线程安全，此处使用C++11中的call_once
*/
class singleton_v5
{	
public:
	~singleton_v5()
	{
		cout<< "singleton_v5 destory!!" << endl;
	}

	static shared_ptr<singleton_v5> get_instance()
	{
		if(NULL == m_pinstance)
		{
			call_once(m_flag, create_instance); /*call_once将会翻转m_flag,使得只执行一次*/
		}

		return m_pinstance;
	}

	static void create_instance()
	{
		m_pinstance = (shared_ptr<singleton_v5>)(new singleton_v5());
	}

protected:
	singleton_v5()
	{
		cout<< "singleton_v5 create!" << endl;
	}

private:
	static shared_ptr<singleton_v5> m_pinstance;
	static once_flag m_flag;
};
//shared_ptr<singleton_v5> singleton_v5::m_pinstance = NULL;
//once_flag singleton_v5::m_flag;





/*版本六 C++11*/
/*
//C++11规定了local static在多线程条件下的初始化行为，要求编译器保证内部静态变量的线程安全性。
*/
class singleton_v6
{	
public:
	~singleton_v6()
	{
		cout<< "singleton_v6 destory!!" << endl;
	}

	static singleton_v6& get_instance()
	{
		static singleton_v6 m_pinstance;

		return m_pinstance;
	}

protected:
	singleton_v6()
	{
		cout<< "singleton_v6 create!" << endl;
	}
};


#if 0
int main()
{
	singleton_v6& p1 = singleton_v6::get_instance();
	singleton_v6& p2 = singleton_v6::get_instance();
	singleton_v6& p3 = singleton_v6::get_instance();

	cout<< "----------------------------" << endl;

}
#endif


