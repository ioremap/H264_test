#include <iostream>
#include <vector>
using namespace std;


/*备忘录模式---------结构型模式*/

/*
//在不破坏封装性的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态。这样以后就可将该对象恢复到原先保存的状态。
//
//Memento: 类定义了内部的状态
//Originator：原发器创建一个备忘录，用以记录当前时刻它的内部状态；我们使用备忘录恢复内部状态
//Caretaker：负责保存好备忘录
//
//管理器向原发器请求一个备忘录，保留一段时间后，将其送回给原发器；而有的时候管理者不会将备忘录返回给原发器，
//因为原发器可能根本不需要退到先前的状态。
*/


class state
{
public:
	state(int a, int b)
	{
		x = a;
		y = b;
	}

	state& operator=(const state& s)
	{
		x = s.x;
		y = s.y;

		return *this;
	}

	
	int x;
	int y;
};



class memento
{
public:
	memento(state s):m_state(s.x, s.y)
	{

	}

	~memento()
	{

	}

	state& get_state()
	{
		return m_state;
	}
	
private:
	state m_state;
};




class originator
{
public:
	originator():m_state(0, 0)
	{

	}

	~originator()
	{

	}

	void set_state(state s)
	{
		m_state = s;
	}

	void show_state()
	{
		cout <<"m_state.x:" << m_state.x << "  m_state.y:" <<m_state.y << endl;
	}

	memento* get_memento()
	{
		return new memento(m_state);
	}

	void recover_from_memento(memento* p)
	{
		if(p)
		{
			set_state(p->get_state());
		}
		
	}

private:
	state m_state;

};


class caretker
{
public:
	caretker()
	{

	}

	~caretker()
	{
		for(vector<memento*>::iterator it = m_list.begin(); it != m_list.end();)
		{
			it = m_list.erase(it);
		}

		m_list.clear();
	}

	void add_memento(memento* p)
	{
		if(p)
		{
			m_list.push_back(p);
		}
	}

	memento* get_memento(unsigned int index)
	{
		if(index >= m_list.size())
		{
			return NULL;
		}
		else
		{
			return m_list[index];
		}
	}

private:
	vector<memento*> m_list;

};


#if 0

int main()
{
	originator org;
	caretker ct;


	org.set_state(state(3,3));

	ct.add_memento(org.get_memento());


	org.set_state(state(5,5));

	ct.add_memento(org.get_memento());


	org.set_state(state(8,8));

	org.show_state();

	org.recover_from_memento(ct.get_memento(1));

	org.show_state();

}

#endif

