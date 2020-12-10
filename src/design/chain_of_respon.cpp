#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*责任链模式------行为模式*/

/*
//责任链模式为请求创建了一个接收者对象的链。这种模式给予请求的类型，对请求的发送者和接收者进行解耦。
//通常每个接收者都包含对另一个接收者的引用。如果一个对象不能处理该请求，那么它会把相同的请求传给下一个接收者，依此类推。
*/

class event
{
public:
	event(string event, int type)
	{
		m_event = event;
		m_type = type;
	}
	
	~event()
	{
	
	}
	
	string get_event()
	{
		return m_event;
	}
	
	int get_type()
	{
		return m_type;
	}
private:
	string m_event;
	int m_type;

};

class handler
{
public:
	~handler()
	{
	
	}
	
	virtual void handle_request(event* pevent) = 0;
	
protected:
	handler()
	{
	
	}
};

class handlle_a : public handler
{
public:
	handlle_a(int level)
	{
		m_level = level;
		
		m_next = NULL;
	}
	
	~handlle_a()
	{
	
	}
	
	void set_next(handler* p)
	{
		m_next = p;
	}
	
	void handle_request(event* pevent)
	{
		if(m_level == pevent->get_type())
		{
			cout << "handlle_a::handle_request:" << pevent->get_event() << endl;
		}
		else if(m_next != NULL)
		{
			m_next->handle_request(pevent);
		}
		else
		{
			cout << "No handle!" << endl;
		}
	}
private:
	handler* m_next;
	int m_level;
};

class handlle_b : public handler
{
public:
	handlle_b(int level)
	{
		m_level = level;
		
		m_next = NULL;
	}
	
	~handlle_b()
	{
	
	}
	
	void set_next(handler* p)
	{
		m_next = p;
	}
	
	void handle_request(event* pevent)
	{
		if(m_level == pevent->get_type())
		{
			cout << "handlle_b::handle_request:" << pevent->get_event() << endl;
		}
		else if(m_next != NULL)
		{
			m_next->handle_request(pevent);
		}
		else
		{
			cout << "No handle!" << endl;
		}
	}
private:
	handler* m_next;
	int m_level;
};


class handlle_c : public handler
{
public:
	handlle_c(int level)
	{
		m_level = level;
		
		m_next = NULL;
	}
	
	~handlle_c()
	{
	
	}
	
	void set_next(handler* p)
	{
		m_next = p;
	}
	
	void handle_request(event* pevent)
	{
		if(m_level == pevent->get_type())
		{
			cout << "handlle_c::handle_request:" << pevent->get_event() << endl;
		}
		else if(m_next != NULL)
		{
			m_next->handle_request(pevent);
		}
		else
		{
			cout << "No handle!" << endl;
		}
	}
private:
	handler* m_next;
	int m_level;
};

#if 0
int main()
{
	string msg = "AAAAAA";
	event ev1(msg, 3);
	
	handlle_a ha(1);
	handlle_b hb(2);
	handlle_c hc(3);
	
	ha.set_next(&hb);
	hb.set_next(&hc);
	
	ha.handle_request(&ev1);

}
#endif

