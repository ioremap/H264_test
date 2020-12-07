#include <amqpcpp.h>
#include <amqpcpp/linux_tcp.h>
#include <unistd.h>
#include <event2/event.h>
#include <amqpcpp/libevent.h>

#include <string>
#include <list>
#include <map>
#include <iostream>

usning namespace std;

class c_extend_handler;

void m_recv_msg(const AMQP::Message &message, uint64_t deliveryTag, bool redelivered);

typedef struct tag_recved_data
{
	int len;
	char* pdata;
}recved_data_t;





class c_connect_mode
{
public:
	c_connect_mode(string ex_name, AMQP::ExchangeType ex_type)
	{
		exchange_name = ex_name;
		exchange_type = ex_type;
	}

	string exchange_name;
	AMQP::ExchangeType exchange_type;
};


class c_msg_env
{
public:
	c_msg_env(const string routing_id, const string queue_name, list<c_connect_mode> mode_cfg)
	{
		m_event_handler = nullptr;
		m_connection = nullptr;
		m_msg_channel = nullptr;

		m_msg_route_key = routing_id;
		m_msg_queue_name = queue_name;
		m_mode_cfg = mode_cfg;

		b_connected = 0;
	}

	~c_msg_env()
	{
		if(m_msg_channel)
		{
			delete m_msg_channel;
		}
	}

	void proc_msg()
	{
		cout << "message::proc_msg" << endl;

		auto iter = m_data_list.begin();

		for( ; iter != m_data_list.end(); )
		{

			cout<< "data_len:" << iter->data_len << endl;

			cout<< "data:" << iter->data << endl;


			free(iter->data);

			iter = m_data_list.erase(iter);
		}
	}

	void connect_ready(AMQP::TcpConnection* pconnection)
	{
		cout << "message::connect_ready" << endl;

		b_connected = 1;

		m_connection = pconnection;
 
		create_channel();
	}

	void connect_error(AMQP::TcpConnection* pconnection)
	{
		cout << "message::connect_error" << endl;

		b_connected = 0;
	}

	void create_channel()
	{
		m_msg_channel = new AMQP::TcpChannel(m_connection);


		c_connect_mode temp = m_mode_cfg.front();

		cout<< "queue_name:" << m_msg_queue_name << "  exchange_name:" << temp.exchange_name << "  type:" << temp.exchange_type << endl;

		m_msg_channel->declareQueue(m_msg_queue_name);

    	m_msg_channel->declareExchange(temp.exchange_name, temp.exchange_type); 

    	m_msg_channel->bindQueue(temp.exchange_name, m_msg_queue_name, m_msg_route_key);


    	m_msg_channel->consume(m_msg_queue_name).onReceived(m_recv_msg);

	}

public:
	c_extend_handler* m_event_handler; 

	AMQP::TcpConnection* m_connection;

	AMQP::TcpChannel* m_msg_channel;

	string m_msg_route_key;

	string m_msg_queue_name;

	list<c_connect_mode> m_mode_cfg;

	list<recved_data_t> m_data_list;

	static map<string, c_msg_env*> s_all_msg_env;
	
private:

	int b_connected;
};

class c_extend_handler: public AMQP::LibEventHandler
{
public:
	c_extend_handler(struct event_base *evbase, pmsg_env* penv) :AMQP::LibEventHandler(evbase)
	{
		pmsg_env = penv;

		pmsg_env->m_event_handler = this;
	}
	
    virtual void onReady(AMQP::TcpConnection* connection) 
    {
		pmsg_env->connect_ready(connection);
    }
    
    virtual void onError(AMQP::TcpConnection* connection, const char *message) 
    {
      	pmsg_env->connect_error(connection);
    }

private:
	c_msg_env* pmsg_env;
};


void m_recv_msg(const AMQP::Message &message, uint64_t deliveryTag, bool redelivered)
{
	cout<<"===============recv_msg===================="<< deliveryTag << "   " << redelivered << endl;
	cout<<"===============routingkey:" << message.routingkey() << " exchange:" << message.exchange() << endl;

	cout<<"================size:" << message.size() <<" body size:" << message.bodySize() << endl;

	auto iter = c_msg_env::s_all_msg_env.find( message.routingkey() );
	if(iter != c_msg_env::s_all_msg_env.end())
	{
		c_msg_env* penv = iter->second;
		if(penv)
		{
			recved_data_t data;
			data.len = message.bodySize();
			data.pdata = (char*)malloc( data.len );
			if(data.pdata)
			{
				memcpy(data.pdata, message.body(), data.len);
				penv->m_data_list.push_back(data);
			}

			penv->m_msg_channel->ack(deliveryTag);
			
			penv->proc_msg();
		}
	}
	else
	{
		cout<< "error!!!!!!!!!  m_recv_msg dont find in queue_map" << endl;
	}

}


