#include <iostream>
#include <string>

using namespace std;


/*中介者模式---------结构型模式*/

/*
//用一个中介对象来封装一系列的对象交互。中介者使各对象不需要显式地相互引用，从而使其耦合松散，而且可以独立地改变它们之间的交互。
//
//Mediator：中介者，它定义了一个接口用于与各个Colleage对象通信
//
*/

class person;


class mediator
{
public:
	virtual ~mediator()
	{

	}
	virtual void send_msg(string& msg, person* p) = 0;

protected:
	mediator()
	{

	}
};

class person
{
public:
	virtual ~person()
	{

	}

	virtual void send(string& msg) = 0;
	virtual void recv(string& msg) = 0;

protected:
	person()
	{

	}
};

class person_a : public person
{
public:
	person_a(mediator* p)
	{
		m_pmed = p;
	}

	~person_a()
	{

	}

	void send(string& msg)
	{
		m_pmed->send_msg(msg, this);
	}

	void recv(string& msg)
	{
		cout << "person_a recv msg:" << msg << endl;
	}

private:
	mediator* m_pmed;	

};

class person_b : public person
{
public:
	person_b(mediator* p)
	{
		m_pmed = p;
	}

	~person_b()
	{

	}

	void send(string& msg)
	{
		m_pmed->send_msg(msg, this);
	}

	void recv(string& msg)
	{
		cout << "person_b recv msg:" << msg << endl;
	}

private:
	mediator* m_pmed;	

};


class mediator_x : public mediator
{
public:
	mediator_x()
	{
		p1 = NULL;
		p2 = NULL;
	}

	~mediator_x()
	{

	}

	void set_person(person* pa, person* pb)
	{
		p1 = pa;
		p2 = pb;
	}

	void send_msg(string& msg, person* p)
	{
		if(!p1 || !p2)
		{
			return;
		}
		
		if(p == p1)
		{
			p2->recv(msg);
		}
		else
		{
			p1->recv(msg);
		}
	}

private:
	person* p1;
	person* p2;
};

#if 0
int main()
{
	mediator_x mx;
	
	person_a pa(&mx);
	person_b pb(&mx);

	
	mx.set_person(&pa, &pb);

	string m1 = "1111111111111";

	pa.send(m1);
}

#endif


