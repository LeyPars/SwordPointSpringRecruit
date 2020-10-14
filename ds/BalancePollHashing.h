#ifndef __BALANCE_POLL_HASHING
#define __BALANCE_POLL_HASHING

//平衡轮询负载均衡算法

#include <string.h>
#include <string>
#include <vector>
using std::vector;
using std::string;
struct ServerEngine
{
	int weight;
	int currentWeight;
	string ip;
	ServerEngine(int initial_weight,string initial_ip):weight(initial_weight),currentWeight(0),ip(initial_ip){}
};
static int totalWeight = 0;
static vector<ServerEngine> server_list;

void initialServerList()
{
	server_list.clear();
	server_list.push_back(ServerEngine(5,"196.152.20.0"));
	server_list.push_back(ServerEngine(1,"196.152.20.1"));
	server_list.push_back(ServerEngine(1,"196.152.20.2"));

	totalWeight = 0;
	for(ServerEngine server:server_list)
	{
		totalWeight	+= server.weight;
	}
}

ServerEngine* getServer()
{
	if(totalWeight == 0) initialServerList();

	//第一步：将每台服务器的当前权重加上自己对应的权重
	for(ServerEngine& server:server_list)
	{
		server.currentWeight += server.weight;
	}
	//第二步：计算当前最大的currentWeight的服务器
	ServerEngine* resultServer = NULL;
	for (ServerEngine& server:server_list)
	{
		if(resultServer == NULL || resultServer->currentWeight < server.currentWeight)
		{
			resultServer = &server;
		}
	}
	//第三步，将当前提供服务的服务器currentWeight减去 totalWeight
	resultServer->currentWeight -= totalWeight;

	return resultServer;
}

#endif
