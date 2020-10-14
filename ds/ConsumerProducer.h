#ifndef __CONSUMER_PRODUCER
#define __CONSUMER_PRODUCER

#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include <iostream>

using std::mutex;
using std::condition_variable;
using std::unique_lock;
using std::thread;
using std::queue;
using std::cout;
using std::endl;

condition_variable consumer,producer;
mutex data_mutex;
queue<int> qu;
int capacity = 10;
int pack_id = 0;

void consumer_one_pack() {
	while (1){
		std::this_thread::sleep_for(std::chrono::seconds(1));
		unique_lock<mutex> lck(data_mutex);
		consumer.wait(lck,[] {return qu.size()!= 0;});
		cout<<"(consumer)thread "<<std::this_thread::get_id()<<" consumer one pack"<<endl;
		cout<<"(consumer)pack id:"<<qu.front()<<endl;
		qu.pop();
		producer.notify_all();
	}
}

void producer_one_pack(){
	while(1) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		unique_lock<mutex> lck(data_mutex);
		producer.wait(lck,[] {return qu.size() != capacity;});
		cout<<"(producer)thread "<<std::this_thread::get_id()<<" producer one pack"<<endl;
		cout<<"(producer)pack id: "<<pack_id<<endl;
		qu.push(pack_id++);
		consumer.notify_all();
	}
}


#endif
