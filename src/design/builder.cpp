#include <iostream>
#include <string>
using namespace std;

/*建造者模式---创建型模式*/
/*
//将一个复杂对象的构建与它的表示分离，使得同样的构建过程可以创建不同的表示。
//
//Product: 最终要生成的对象
//Builder：构建者的抽象基类,其定义了构建Product的抽象步骤，其实体类需要实现这些步骤。
//ConcreteBuilder: Builder的实现类
//Director: 决定如何构建最终产品的算法. 其会包含一个负责组装的方法
//
//优点：
//1.客户端不必知道产品内部组成的细节，将产品本身与产品的创建过程解耦，使得相同的创建过程可以创建不同的产品对象。
//2.每一个具体建造者都独立，因此可以方便地替换具体建造者或增加新的具体建造者， 用户使用不同的具体建造者即可得到不同的产品对象 。
//3.可以更加精细地控制产品的创建过程 。将复杂产品的创建步骤分解在不同的方法中，使得创建过程更加清晰，也更方便使用程序来控制创建过程。
//4.增加新的具体建造者无须修改原有类库的代码，指挥者类针对抽象建造者类编程，系统扩展方便，符合“开闭”。
//缺点：
//1.当建造者过多时，会产生很多类，难以维护。
//2.建造者模式所创建的产品一般具有较多的共同点，其组成部分相似，若产品之间的差异性很大，则不适合使用该模式，因此其使用范围受到一定限制。
//3.若产品的内部变化复杂，可能会导致需要定义很多具体建造者类来实现这种变化，导致系统变得很庞大。
//
//与工厂模式却区别：
//工厂模式用于处理如何获取实例对象问题，建造者模式用于处理如何建造实例对象问题
//与工厂模式相比，建造者模式一般用来创建更为复杂的对象，因为对象的创建过程更为复杂，因此将对象的创建过程独立出来组成一个新的类——指挥类。
//工厂模式是将对象的全部创建过程封装在工厂类中，由工厂类向客户端提供最终的产品
*/

class product_computer
{
public:
	product_computer()
	{
		cout<< "product_computer create!" << endl;
	}

	~product_computer()
	{
		cout<< "product_computer destory!" << endl;
	}

	void set_cpu(const string& cpu_str)
	{
		cpu = cpu_str;
	}

	void set_mem(const string& mem_str)
	{
		mem = mem_str;
	}

	void set_board(const string& board_str)
	{
		board = board_str;
	}

	void set_power(const string& power_str)
	{
		power = power_str;
	}

	void show_info()
	{
		cout<< "------------info------------------" << endl;
		cout<< "cpu:" << cpu << endl;
		cout<< "mem:" << mem << endl;
		cout<< "board:" << board << endl;
		cout<< "power:" << power << endl;
	}

private:
	string cpu;
	string mem;
	string board;
	string power;
};

class builder
{
public:
	builder()
	{

	}

	virtual ~builder()
	{

	}

	virtual void build_cpu() = 0;
	virtual void build_mem() = 0;
	virtual void build_board() = 0;
	virtual void build_power() = 0;

	virtual product_computer* get_computer() = 0;
};

class builder_a : public builder
{
public:
	builder_a()
	{
		m_pcomputer = new product_computer();
	}

	~builder_a()
	{
		if(m_pcomputer)
		{
			delete m_pcomputer;
		}
	}

	void build_cpu()
	{
		m_pcomputer->set_cpu("i9-10900K");
	}

	void build_mem()
	{
		m_pcomputer->set_mem("8GB*2");
	}

	void build_board()
	{
		m_pcomputer->set_board("ASUS ROG");
	}

	void build_power()
	{
		m_pcomputer->set_power("corsair");
	}

	product_computer* get_computer()
	{
		return m_pcomputer;
	}
private:
	product_computer* m_pcomputer;
};

class builder_b : public builder
{
public:
	builder_b()
	{
		m_pcomputer = new product_computer();
	}

	~builder_b()
	{
		if(m_pcomputer)
		{
			delete m_pcomputer;
		}
	}

	void build_cpu()
	{
		m_pcomputer->set_cpu("R5-3600X");
	}

	void build_mem()
	{
		m_pcomputer->set_mem("16GB");
	}

	void build_board()
	{
		m_pcomputer->set_board("msi");
	}

	void build_power()
	{
		m_pcomputer->set_power("seasonic");
	}

	product_computer* get_computer()
	{
		return m_pcomputer;
	}
private:
	product_computer* m_pcomputer;
};

class director
{
public:
	director()
	{

	}

	~director()
	{

	}

	void build_computer(builder& b)
	{
		b.build_board();
		b.build_cpu();
		b.build_mem();
		b.build_power();
	}
};

#if 0
int main()
{
	director dire;

	builder_a a;
	dire.build_computer(a);
	product_computer* p1 = a.get_computer();
	p1->show_info();

	builder_b b;
	dire.build_computer(b);
	product_computer* p2 = b.get_computer();
	p2->show_info();

}
#endif


