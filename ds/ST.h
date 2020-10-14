//segment tree
#ifndef __ST_DS
#define __ST_DS

#include <algorithm>
using std::min;
using std::max;

#define INF 1E9+7
#define MaxCount 10000+5;
//根节点从0开始编号
//对于每个编号为i的节点，其左右子节点的编号分别为2i和2i+1


//version1:单点更新，区间询问
namespace ST_VERSION_ONE
{
	//problem primitive:
	//给定一个含n个元素的数组A，设计数据结构支持以下两种操作
	//operation 1：update（x,v） 把Ax的值修改为v;
	//operation 2: Query(L,R) 计算min{AL,AL+1,...AR}
	//由于更新操作会让RMQ每次都要重新建立，因此不适用RMQ

	int minv[MaxCount];    //储存各个节点保存的最小值

	int ql,qr; //查询[ql,qr]的最小值
	int query(int o,int L,int R)    //o为当前节点编号，L，R为当前节点左右端点
	{
		int M = L+ (R-L)/2,ans = INF;
		if (ql<=L && R <=qr) return minv[o];
		if (ql<=M)
		{
			//往左走
			ans = min(ans,query(o*2,L,M));
		}
		if (M < qr)
		{
			//往右走
			ans = min(ans,query(2*o+1,M+1,R));
		}
		return ans;
	}


	int p,v;     //修改A[p]=v;
	void update(int o,int L,int R)
	{
		int M = L+(R-L)/2;
		if(L==R) minv[o] = v;  //叶节点，直接更新
		else
		{
			//递归更新
			if (p<=M)
			{
				//更新左子树
				update(o*2,L,M);
			}
			else
			{
				update(2*o+1,M+1,R);
			}
		}
		minv[o] = min(minv[2*o],minv[2*o+1]);
	}
}


//version2：区间更新，区间询问（只打标记，不推标记）
namespace ST_VERSION_TWO
{
	//problem primitive:
	//给定一个含n个元素的数组A，设计数据结构支持以下两种操作
	//operation 1：Add（L,R,v） 把AL到AR的值全部增加v;
	//operation 2: Query(L,R) 计算min{AL,AL+1,...AR}
	//             max{AL,AL+1,...AR}，sum{AL,AL+1,...AR}
	int sumv[MaxCount],minv[MaxCount],maxv[MaxCount];
	int addv[MaxCount];

	void maintain(int o,int L,int R)
	{
		int lc=2*o,rc=2*o+1;
		sumv[o]=minv[o]=maxv[o]=0;
		if (R>L)
		{
			sumv[o] = sumv[lc] + sumv[rc];
			maxv[o] = max(maxv[lc],maxv[rc]);
			minv[o] = min(minv[lc],minv[rc]);
		}
		//加入当前节点的标记
		sumv[o] += addv[o];maxv[o] += addv[o];minv[o] += addv[o];
	}

	//将[y1,y2]的值全部加v
	void update(int o,int L,int R,int y1,int y2,int v)
	{
		int lc=2*o,rc=2*o+1;
		if(y1<=L && R<=y2)
		{
			addv[o]+=v;
		}
		else
		{
			int M = L+(R-L)/2;
			if(y1<=M) update(lc,L,M,y1,y2,v);
			if(M<y2) update(rc,M+1,R,y1,y2,v);
		}
		maintain(o,L,R);
		//递归结束后重新计算本节点的附加信息
	}


	//询问时另加一个标记参数，用于累加标记
	int _min,_max,_sum;
	void query(int o,int L,int R,int add，int y1,int y2)
	{
		//累计标记（只打标记，不往下推）
		if (y1<=L&&R<=y2)
		{
			_sum += sumv[o]+add*(R-L+1);
			_min = min(_min,minv[o]+add);
			_max = max(_max,maxv[o]+add);
		}
		else
		{
			int M = L+(R-L>>1);
			if(y1<=M) query(2*o,L,M,add+addv[o],y1,y2);
			if(M<y2) query(2*o+1,M+1,R,add+addv[o],y1,y2);
		}
	}
}


namespace ST_VERSION_THREE
{
	//problem primitive:
	//给定一个含n个元素的数组A，设计数据结构支持以下两种操作
	//operation 1：Set（L,R,v） 把AL到AR的值修改为v;
	//operation 2: Query(L,R) 计算min{AL,AL+1,...AR}
	//             max{AL,AL+1,...AR}，sum{AL,AL+1,...AR}
}



#endif