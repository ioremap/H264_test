#include <iostream>
#include <list>
using namespace std;


/*观察者模式------结构型模式*/

/*
//定义对象间的一种一对多的依赖关系，当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并被自动更新。
//当一个对象发生了变化，关注它的对象就会得到通知；这种交互也称为发布-订阅(publish-subscribe)。
//目标是通知的发布者，它发出通知时并不需要知道谁是它的观察者。
//
//
//举例：对同一组数据进行统计分析时候， 我们希望能够提供多种形式的表示 （例如以表格进行统计显示、
//柱状图统计显示、百分比统计显示等）。这些表示都依赖于同一组数据， 我们当然需要当数据改变的时候， 所有的统计的显示都能够同时改变。
//
//
//Subject: 抽象的目标，提供注册和删除观察者对象的接口  。一对多中的一
//ConcreteSubject： 具体的目标
//Observer: 抽象的观察者，那些在目标发生改变时需获得通知的对象定义一个更新接口
//ConcreteObserver：具体的观察者
*/

class observer;

class subject
{
public:
	virtual ~subject()
	{

	}

	virtual void add_observer(observer* p) = 0;
	virtual void remove_observer(observer* p) = 0;
	virtual void notify() = 0;

	virtual int get_state() = 0;
	virtual void set_sate(int state) = 0;

protected:
	subject()
	{

	}	
};

class observer
{
public:
	virtual ~observer()
	{

	}

	virtual void on_change() = 0;

protected:
	observer()
	{

	}
};

class observer_a : public observer
{
public:
	observer_a(subject* p)
	{
		m_psubject = p;
	}

	~observer_a()
	{

	}

	void fun1()
	{
		cout << "observer_a::fun1()" << endl;
	}

	void on_change();

private:
	subject* m_psubject;
};

class observer_b : public observer
{
public:
	observer_b(subject* p)
	{
		m_psubject = p;
	}

	~observer_b()
	{

	}

	void fun2()
	{
		cout << "observer_b::fun2()" << endl;
	}

	void on_change();


private:
	subject* m_psubject;
};



class subject_a : public subject
{
public:
	subject_a(int state)
	{
		m_state = state;
	}

	~subject_a()
	{

	}

	void add_observer(observer* p)
	{
		m_pobserver_list.push_back(p);
	}

	void remove_observer(observer* p)
	{
		m_pobserver_list.remove(p);
	}

	void notify()
	{
		for(list<observer*>::iterator it = m_pobserver_list.begin(); it != m_pobserver_list.end(); it++)
		{
			(*it)->on_change();
		}
	}

	int get_state()
	{
		return m_state;
	}

	void set_sate(int state)
	{
		m_state = state;

		notify();
	}

private:
	int m_state;
	list<observer*> m_pobserver_list;
};




void observer_a::on_change()
{
	fun1();

	cout<< "new_state:" << m_psubject->get_state() << endl;
}

void observer_b::on_change()
{
	fun2();

	cout<< "new_state:" << m_psubject->get_state() << endl;
}


#if 0
int main()
{

	subject_a s1(1);

	observer_a oa(&s1);

	observer_b ob(&s1);

	s1.add_observer(&oa);
	s1.add_observer(&ob);

	s1.set_sate(3);

	s1.set_sate(9);

}
#endif



