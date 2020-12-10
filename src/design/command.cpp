#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*命令模式-----------行为模式*/

/*
//请求以命令的形式包裹在对象中，并传给调用对象。调用对象寻找可以处理该命令的合适的对象，并把该命令传给相应的对象，该对象执行命令。
//
//行为请求者与行为实现者通常是一种紧耦合的关系。在某些场合，比如要对行为进行"记录、撤销/重做、事务"等处理，
//这种无法抵御变化的紧耦合是不合适的,将一组行为抽象为对象，可以实现二者之间的松耦合
//
//Command：抽象命令类
//ConcreteCommand：命令类的具体实现
//Invoker：请求的发送者，它通过命令对象来执行请求。一个调用者并不需要在设计时确定其接收者，因此它只与抽象命令来之间存在关联。
//Receiver：接收者执行与请求相关的操作，真正执行命令的对象
*/

class command
{
public:
	virtual ~command()
	{

	}

	virtual void execute() = 0;

protected:
	command()
	{

	}
};

class receiver
{
public:
	virtual ~receiver()
	{

	}

	virtual void action() = 0;

protected:
	receiver()
	{

	}
};

class command_set: public command
{
public:
	command_set(receiver* p)
	{
		m_precv = p;
	}

	~command_set()
	{

	}

	void execute()
	{
		if(m_precv)
		{
			m_precv->action();
		}
	}
private:
	receiver* m_precv;
};

class receiver_a : public receiver
{
public:
	receiver_a()
	{

	}

	~receiver_a()
	{

	}

	void action()
	{
		cout << "receiver_a::action" << endl;
	}
};

class invoker
{
public:
	invoker(command* p)
	{
		m_pcmd = p;
	}

	~invoker()
	{

	}

	void invoke()
	{
		if(m_pcmd)
		{
			m_pcmd->execute();
		}
	}
private:
	command* m_pcmd;	
};

#if 0
int main()
{
	receiver_a recv;
	command_set cmd_set(&recv);

	invoker ink(&cmd_set);

	ink.invoke();

}
#endif

