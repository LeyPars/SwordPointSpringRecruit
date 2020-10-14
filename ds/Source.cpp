#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <list>
#include <time.h>
#include "RMQ.h"

using namespace std;

const int MaxCount = 100000+5;
const int expr = 100+5;
int d[MaxCount][expr];
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

int main() {
	int n;

	system("PAUSE");
	return 0;
}
