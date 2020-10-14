#ifndef __RANDOM_WITH_WEIGHT
#define __RANDOM_WITH_WEIGHT

//随机算法：从n个带权节点中按照权重比例选择m个（m<=n）
//概率论问题：是否正确不一定

#include <vector>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string>
#include <algorithm>
using std::vector;
using std::string;
/*
struct weightNode{
	int weight;
	string obj;
	weightNode(int w,int o):weight(w),obj(o){}
};

vector<weightNode> getNodes(vector<weightNode>& candi,int m)
{
	const int n = candi.size();
	if(n<m) m = n;

	int totalWeight = 0;
	for (const weightNode& node:candi)
	{
		totalWeight+=node.weight;
	}
	std::sort(begin(candi),end(candi),[&](const weightNode& a,const weightNode& b) {
		if(a.weight!=b.weight) return a.weight > a.weight;
		return a.obj < b.obj;
	});
	srand(time(NULL));
	int sum = totalWeight;
	int quota = m;
	vector<weightNode> ans;
	for (int i = 0; i < n; ++i)
	{
		int curWeight = candi[i].weight;
		if((rand()%sum)< curWeight * m)
		{
		   m--;
		   ans.push_back(candi[i]);
		}
		sum -= curWeight;
	}
	return ans;
}

*/


//蓄水池抽样算法
//https://www.jianshu.com/p/7a9ea6ece2af
namespace RESERVOIR_SAMPLING
{
	int m;
	vector<int> ans;
	int cursor,sum;  //计数浮标以及总的元素数目
	void init(int sampling_size)
	{
		srand(time(NULL));
		m = sampling_size;
		cursor = 0;
		sum = 0;
		ans.resize(m,0);
	}
	void addElement(int element)
	{
		++sum;
		if(cursor < m) ans[cursor++] = element;
		else {
			int index = rand()%sum;
			if(index < m)
			{
				ans[index] = element;
			}
		}
	}
	vector<int>& getResult()
	{
		return ans;
	}
}

#endif
