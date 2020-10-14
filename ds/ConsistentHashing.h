#ifndef __CONSISTENT_HASHING
#define __CONSISTENT_HASHING


//Դ��ַ��https://blog.csdn.net/kefengwang/article/details/81628977
#include <math.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <map>
#include <set>
using std::string;
using std::map;
using std::set;
using std::pair;
// 32λ�� Fowler-Noll-Vo ��ϣ�㷨
// https://en.wikipedia.org/wiki/Fowler�CNoll�CVo_hash_function
static long FNVHash(string key) {
	const int p = 16777619;
	long hash = 2166136261;
	for (int idx = 0, num = key.length(); idx < num; ++idx) {
		hash = (hash ^ key[idx]) * p;
	}
	hash += hash << 13;
	hash ^= hash >> 7;
	hash += hash << 3;
	hash ^= hash >> 17;
	hash += hash << 5;

	if (hash < 0) {
		hash = abs(hash);
	}
	return hash;
}

int VIRTUAL_COPIES = 1048576;

set<string> physicalNodes; 
map<long, string> virtualNodes; // ��ϣֵ => ����ڵ�

void addPhyicalNode(string nodeIp)
{
	for (int idx = 0; idx < VIRTUAL_COPIES; ++idx) {
		long hash = FNVHash(nodeIp + "#" + std::to_string(idx));
		virtualNodes.insert(make_pair(hash, nodeIp));
	}
}

void removePhyicalNode(string nodeIp)
{
	for (int idx = 0; idx < VIRTUAL_COPIES; ++idx) {
		long hash = FNVHash(nodeIp + "#" + std::to_string(idx));
		virtualNodes.erase(hash);
	}
}

void constistent_hashing_init(int virtualNumber = 0)
{
   if(virtualNumber > 0) {
	   VIRTUAL_COPIES = virtualNumber;
   }
   physicalNodes.clear();
   physicalNodes.insert("192.168.1.101");
   physicalNodes.insert("192.168.1.102");
   physicalNodes.insert("192.168.1.103");
   physicalNodes.insert("192.168.1.104");

   for (string nodeIp : physicalNodes) {
	   	addPhyicalNode(nodeIp);
   }
}

// ���Ҷ���ӳ��Ľڵ�
string getObjectNode(string object) {
	long hash = FNVHash(object);
	map<long,string>::iterator iter = virtualNodes.lower_bound(hash);
	string resultNode = (iter==virtualNodes.end() ? virtualNodes.begin()->second : iter->second);
	return resultNode;
}


// ͳ�ƶ�����ڵ��ӳ���ϵ
void dumpObjectNodeMap(string label, int objectMin, int objectMax) {
	// ͳ��
	map<string, int> objectNodeMap;
	for (int object = objectMin; object <= objectMax; ++object) {
		string nodeIp = getObjectNode(std::to_string(object));
		objectNodeMap[nodeIp]++;
	}

	// ��ӡ
	double totalCount = objectMax - objectMin + 1;
	printf("======== %s ========",label);
	for (pair<string,int> psi:objectNodeMap) {
		int percent = (int) (100 * psi.second / totalCount);
		printf("IP=%d : RATE=%d\%\n",psi.first,percent);
	}
}
#endif
