/*
MESI缓存一致性协议：
1.CPU缓存的基本单位为缓存行
2.M（Modified）,E(Exclusive),S(Shared),I(Invalid)
3.M:代表缓存行中的内容被修改了，此缓存行的数据和内存中的不一样
  E:该缓存行的内容只被当前CPU缓存，且内容与内存中一致
  S:该缓存行被多个CPU缓存，且缓存行与内存一致
  I:当前缓存行的数据是无效的


LRU-K缓存算法
背景：解决LRU算法的缓存污染问题，核心思想是将“最近使用过1次”的判断标准扩展为“最近使用过k次”
工作原理：
     相比于LRU,LRU-K需要多维护一个队列，用于记录所有缓存数据被访问的历史，只有当数据的
	 访问次数达到K次的时候，才将数据放入缓存。当需要淘汰数据时，LRU-K会淘汰第K次访问时间距
	 当前时间最大的数据
详细实现如下：
	1.数据第一次访问，加入到访问历史列表；
	2.如果数据在访问历史列表里没有达到K次访问，则按照一定规则淘汰（FIFO,LRU）
	3.当访问历史队列中的数据访问次数达到K次后，将数据索引从历史队列中删除，将数据移动到缓存队列
	  中，并缓存此数据，缓存队列重新按照时间排序
	4.缓存数据队列中被在此访问后，重新排序
	5.需要淘汰数据时，淘汰缓存队列中排在末尾的数据，即淘汰倒数第K次访问离现在最久的数据
*/
#include <list>
#include <map>
using namespace std;
typedef pair<int,int> PII;
class LRU_K
{
private:
	int K;        //LRU-K的K值
	list<int> qu; //访问历史队列
	int qu_capacity; //历史队列的大小
	unordered_map<int,int> quhash;  //访问历史队列计数

	list<PII> lrulist;
	unordered_map<int,list<PII>::iterator> lruhash;
	int capacity;
public:
	int visit(int key)
	{
		if(lruhash.count(key))
		{
			return LRU_Get(key);
		}

		//从内存中或磁盘中读取key的数值
		int val = 0;
		//访问key
		if(quhash.count(key) && quhash[key] + 1 == K)
		{
			//移除所有的key值将其放入缓存队列
			auto tarversal = qu.begin();
			while(tarversal != nullptr)
			{
				if(*tarversal == key)
				{
					auto nxt = tarversal + 1;
					lrulist.erase(tarversal);
					tarversal = nxt;
				} else {
					tarversal = tarversal + 1;
				}
			}
			quhash.erase(key);
			LRU_Set(key,val);
		} else {
			if (qu.size() == qu_capacity) {
				int dyingoff = qu.front();
				qu.pop_front();
				if(--quhash[dyingoff]==0) quhash.erase(dyingoff);
			}
			qu.push_back(key);
			quhash[key]++;
		}
		return val;
	}

private:
	int LRU_Get(int key)
	{
		auto spot = lruhash.find(key);
		if(spot==lruhash.end()) return -1;
		int ans = spot->second->second;
		lrulist.push_front(make_pair(key,ans));
		lrulist.erase(spot->second);
		lruhash[key] = lrulist.begin();
		return ans;
	}

	void LRU_Set(int key,int val)
	{
		auto spot = lruhash.find(key);
		if(spot != lruhash.end())
		{
			lrulist.erase(spot->second);
		} else if(lruhash.size() == capacity)
		{
			lruhash.erase(lrulist.back().first);
			lrulist.pop_back();
		}
		lrulist.push_front(make_pair(key,val));
		lruhash[key] = lrulist.begin();
	}
};
/*
2Q缓存

*/