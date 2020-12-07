#include <amqpcpp.h>
#include <amqpcpp/linux_tcp.h>
#include <unistd.h>
#include <iostream>
#include <event2/event.h>
#include <amqpcpp/libevent.h>

#include <string>
#include <list>
#include <map>


//当发送一套消息到fanout交换器时，它会把消息投递给所有附加在此交换器上的队列     ------广播

//direct交换器：如果路由键匹配，消息就会被投递到对应的队列

int main()
{

	std::list<msg_chn_cfg> config_list;
	msg_chn_cfg message1("ampq.fanout", AMQP::fanout);
	config_list.push_back(message1);

	message_q m1("my-routing-key", "test_queue", config_list);

	message_q::queue_map.insert( std::pair<std::string, message_q*>(m1.m_queue_name, &m1) );




	auto evbase = event_base_new();
    my_handler handler(evbase, &m1);
    AMQP::TcpConnection connection(&handler, AMQP::Address("amqp://tn:123456@192.168.1.148/"));

    


    event_base_dispatch(evbase);

    event_base_free(evbase);


	return 0;
}
