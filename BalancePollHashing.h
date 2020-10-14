#ifndef __BALANCE_POLL_HASHING
#define __BALANCE_POLL_HASHING

//ƽ����ѯ���ؾ����㷨

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

	//��һ������ÿ̨�������ĵ�ǰȨ�ؼ����Լ���Ӧ��Ȩ��
	for(ServerEngine& server:server_list)
	{
		server.currentWeight += server.weight;
	}
	//�ڶ��������㵱ǰ����currentWeight�ķ�����
	ServerEngine* resultServer = NULL;
	for (ServerEngine& server:server_list)
	{
		if(resultServer == NULL || resultServer->currentWeight < server.currentWeight)
		{
			resultServer = &server;
		}
	}
	//������������ǰ�ṩ����ķ�����currentWeight��ȥ totalWeight
	resultServer->currentWeight -= totalWeight;

	return resultServer;
}

#endif
