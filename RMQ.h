//Range Minimum Query
#ifndef __RMQ_DS
#define __RMQ_DS

#include <vector>
#include <algorithm>
using std::vector;
using std::min;


//思想，区间查询最小值query[L，R]；
//d(i,j)表示从i开始，长度为2的j次方的一段元素的最小值
//d(i,j)=min( d(i,j-1),d(i+len,j-1) ) 其中，len为2的j-1次方



const int MaxCount = 100000+5;
const int exp = 100+5;
int d[MaxCount][exp];
// time complexity O(nlogn)
void RMQ_init(const vector<int>& A)
{
	int n = A.size();
	for (int i=0;i<n;++i)
	{
		d[i][0]=A[i];
	}
	for (int j=1;(1<<j)<=n;++j)
	{
		for (int i=0;i + (1<<j) - 1 < n; ++i)
		{
			d[i][j] = min(d[i][j-1],d[i + (1<<(j-1))][j-1]);
		}
	}
}


//查询区间[L,R]最小值，先求出满足 2的k次方<= R-L+1 的最大k值，则以L开头和以R结尾的两个长度为2的k次方的区间必定包含所有
//[L,R]区间的值，因为是求最小值，有些值被重复包括也没关系,
//(R-L+1)为区间的长度，只要不超出边界且保证取到所有值即可

int RMQ(int L,int R)
{
	int k=0;
	while((1<<(k+1) <= R-L+1)) ++k;
	return min(d[L][k],d[R-(1<<k)+1][k]);
}

#endif