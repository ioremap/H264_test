#include <iostream>
using namespace std;

/*状态模式--------行为模式*/

/*
//
//状态模式主要解决的是当控制一个对象状态转换的条件表达式过于复杂时的情况。把状态的判断逻辑转移到表示不同状态的一系列类当中，
//可以把复杂的判断逻辑简化。
//
*/


class context;


class state
{
public:
	virtual ~state()
	{

	}

	virtual void handle(context* p) = 0;

protected:
	state()
	{

	}
};


class state_a : public state
{
public:
	state_a()
	{
		cout << "state_a::state_a" << endl;
	}

	~state_a()
	{
		cout << "state_a::~state_a" << endl;
	}

	void handle(context* p);

};


class state_b : public state
{
public:
	state_b()
	{
		cout << "state_b::state_b" << endl;
	}

	~state_b()
	{
		cout << "state_b::~state_b" << endl;
	}

	void handle(context* p);

};

class state_c : public state
{
public:
	state_c()
	{
		cout << "state_c::state_c" << endl;
	}

	~state_c()
	{
		cout << "state_c::~state_c" << endl;
	}

	void handle(context* p);

};

class context
{
public:
	context(state* p)
	{
		m_state = p;
	}

	~context()
	{
		if(NULL != m_state)
		{
			delete m_state;
			m_state = NULL;
		}
	}

	void request()
	{
		m_state->handle(this);
	}

	void change_state(state* p)
	{
		if(NULL != m_state)
		{
			delete m_state;
			m_state = NULL;
		}
		
		m_state = p;
	}

private:
	state* m_state;
};


void state_a::handle(context* p)
{
	cout << "handle1" << endl;

	p->change_state(new state_b());
}

void state_b::handle(context* p)
{
	cout << "handle2" << endl;

	p->change_state(new state_c());
}

void state_c::handle(context* p)
{
	cout << "handle3" << endl;

	p->change_state(new state_a());
}


#if 0
int main()
{
	context c(new state_a());

	c.request();
	c.request();
	c.request();
}
#endif

