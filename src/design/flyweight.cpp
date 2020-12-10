#include <iostream>
#include <string>
#include <map>

using namespace std;

/*享元模式---------结构型模式*/
/*
//
//享元模式是为了应对大量细粒度对象重复的问题。程序中存在大量细粒度的对象，每次要使用时都必须创建一个新的对象，
//既影响了运行效率又增加了内存消耗。于是有了享元模式，享元模式提取出这些细粒度对象中间公共的状态，只生成一个实例对象，
//所有用到这些公共属性对象的地方，都指向这一个实例。
//
//典型的享元模式的例子为文书处理器中以图形结构来表示字符。一个做法是，每个字形有其字型外观，字模metrics，
//和其他格式资讯，但为每个字符都生成这些书写，就会额外消耗许多的内存空间。取而代之的是，每个字符参照一个共享字形物件，
//此物件会被其他有共同特质的字符所分享；只有每个字符的位置才需要另外存储。
*/


class flyweight
{
public:
	flyweight(string k)
	{
		m_key = k;

		cout << "flyweight::flyweight key:" << m_key << endl;
	}

	~flyweight()
	{
		cout << "flyweight::~flyweight key:" << m_key << endl;
	}

	void operation(const string& op)
	{
		cout<< "m_key op:" << op << endl;
	}

private:
	string m_key;
};

class flyweight_factory
{
public:
	flyweight_factory()
	{

	}

	~flyweight_factory()
	{
		for(map<string, flyweight*>::iterator it = m_map.begin();
			it != m_map.end(); )
		{
			delete it->second;

			it = m_map.erase(it);
		}
	}

	flyweight* get_instance(const string& key)
	{
		map<string, flyweight*>::iterator it = m_map.find(key);
		if(it != m_map.end())
		{
			return it->second;
		}
		else
		{
			flyweight* p = new flyweight(key);

			m_map.insert(make_pair(key, p));

			return p;
		}
	}

private:
	map<string, flyweight*> m_map;
};

#if 0
int main()
{
	flyweight_factory factory;

	flyweight*p1 = factory.get_instance("hello");
	p1->operation("red");

	flyweight*p2 = factory.get_instance("hello");
	p2->operation("yellow");

	flyweight*p3 = factory.get_instance("hello");
	p3->operation("green");

}

#endif
