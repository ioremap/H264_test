#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*访问者模式----------结构型模式*/

/*
//可以在不改变各元素的类的前提下定义作用于这些元素的新操作。访问者模式把数据结构和作用于结构上的操作之间的耦合解脱开，
//使得操作集合可以相对自由地演化。该模式的目的是要把处理从数据结构分离出来。访问者模式让增加新的操作很容易，因为增加新的操作就意味着增加一个新的访问者。
//
//使用场景： 1、对象结构中对象对应的类很少改变，但经常需要在此对象结构上定义新的操作。 
//2、需要对一个对象结构中的对象进行很多不同的并且不相关的操作，而需要避免让这些操作"污染"这些对象的类，也不希望在增加新操作时修改这些类。
//
*/

class visitor;

class element
{
public:
	~element()
	{

	}

	virtual void accept(visitor* pvisitor) = 0;
	virtual int get_value() = 0;

protected:
	element()
	{

	}
};

class element_a : public element
{
public:
	element_a()
	{

	}

	~element_a()
	{

	}

	void accept(visitor* pvisitor);

	int get_value()
	{
		return 100;
	}
};

class element_b : public element
{
public:
	element_b()
	{

	}

	~element_b()
	{

	}

	void accept(visitor* pvisitor);

	int get_value()
	{
		return 200;
	}
};


class visitor
{
public:
	~visitor()
	{

	}

	virtual void visit_element_a(element_a* pa) = 0;
	virtual void visit_element_b(element_b* pb) = 0;

protected:
	visitor()
	{

	}
};


class visitor_x : public visitor
{
public:
	visitor_x()
	{

	}

	~visitor_x()
	{

	}

	void visit_element_a(element_a* pa)
	{
		int n = 100 + pa->get_value();
		cout << "element_a + 100 = " << n << endl;
	}

	void visit_element_b(element_b* pb)
	{
		int n = 100 + pb->get_value();
		cout << "element_b + 100 = " << n << endl;
	}
};

class visitor_y : public visitor
{
public:
	visitor_y()
	{

	}

	~visitor_y()
	{

	}

	void visit_element_a(element_a* pa)
	{
		int n = 100 * pa->get_value();
		
		cout << "element_a * 100 = " << n << endl;
	}

	void visit_element_b(element_b* pb)
	{
		int n = 100 * pb->get_value();
		cout << "element_b * 100 = " << n << endl;
	}
};



void element_a::accept(visitor* pvisitor)
{
	pvisitor->visit_element_a(this);
}

void element_b::accept(visitor* pvisitor)
{
	pvisitor->visit_element_b(this);
}



class object
{
public:
	object()
	{

	}

	~object()
	{

	}

	void add_element(element* pe)
	{
		m_list.push_back(pe);
	}

	void visit(visitor* pvisitor)
	{
		for(vector<element*>::iterator it = m_list.begin(); it != m_list.end(); it++)
		{
			(*it)->accept(pvisitor);
		}
	}

private:
	vector<element*> m_list;

};

#if 0
int main()
{
	element_a ea;
	element_b eb;

	object obj;
	obj.add_element(&ea);
	obj.add_element(&eb);

	visitor_y y;
	obj.visit(&y);
}
#endif


