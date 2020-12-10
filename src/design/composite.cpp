#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*组合模式-----结构型模式*/
/*
//
//组合模式是为解决组件之间的递归组合提供了解决的办法，它主要分为两个派生类：Leaf是叶子结点,也就是不含有子组件的结点
//Composite是含有子组件的类.
//
//举例来说在UI设计中,最基本的控件是诸如Button、Edit这样的控件，相当于是这里的Leaf组件，而比较复杂的控件比如Panel
//则可也看做是由这些基本的组件组合起来的控件，相当于这里的Composite，它们之间有一些行为含义是相同的，比如在控件上作一个点击,
//移动操作等等的，这些都可以定义为抽象基类中的接口虚函数，由各个派生类去实现之，这些都会有的行为就是这里的Operation函数，
//而添加、删除等进行组件组合的操作只有非叶子结点才可能有
//
//
*/

class component
{
public:
	
	virtual ~component()
	{

	}

	virtual void add(component* p)
	{

	}
	
	virtual void remove(component* p)
	{

	}
	
	virtual component* get_child(unsigned int index)
	{
		return NULL;
	}
	
	virtual void operation() = 0;


protected:
	component()
	{

	}
};


class leaf: public component
{
public:
	leaf(string name)
	{
		m_name = name;
	}

	~leaf()
	{

	}


	void operation()
	{
		cout<< "leaf::operation()  name:" << m_name << endl;
	}


	string m_name;

};


class composite: public component
{
public:
	composite(string name)
	{
		m_name = name;
	}

	~composite()
	{

	}



	void add(component* p)
	{
		m_vector.push_back(p);
	}

	void remove(component* p)
	{
		//m_vector.erase(&p);

		for(vector<component*>::iterator it = m_vector.begin(); it != m_vector.end(); it++)
		{
			if(*it == p)
			{
				m_vector.erase(it);
			}
		}
	}

	component* get_child(unsigned int index)
	{
		if(index > m_vector.size())
		{
			cout<< "composite::get_child error m_vector::size:" << m_vector.size() << endl;
		}

		return m_vector[index];
	}

	void operation()
	{
		cout<< "component::operation name:" << m_name << endl;
		for(vector<component*>::iterator it = m_vector.begin();
			it != m_vector.end(); it++)
		{
			(*it)->operation();
		}

		cout<< "-----------------------------" <<endl;
	}

	
private:
	vector<component*> m_vector;
	string m_name;
};


#if 0
int main()
{
	
	component* proot = new composite(string("root"));
	
	component* pson1 = new composite(string("son1"));
	component* pson2 = new composite(string("son2"));

	component* pnode1 = new leaf(string("son1_node1"));
	component* pnode2 = new leaf(string("son1_node2"));
	component* pnode3 = new leaf(string("son1_node3"));
	component* pnode4 = new leaf(string("son2_node1"));
	component* pnode5 = new leaf(string("son2_node2"));
	component* pnode6 = new leaf(string("son2_node3"));

	pson1->add(pnode1);
	pson1->add(pnode2);
	pson1->add(pnode3);

	pson2->add(pnode4);
	pson2->add(pnode5);
	pson2->add(pnode6);

	proot->add(pson1);
	proot->add(pson2);

	proot->operation();

	delete pnode1;
	delete pnode2;
	delete pnode3;
	delete pnode4;
	delete pnode5;
	delete pnode6;

	delete pson1;
	delete pson2;
	delete proot;

}

#endif


