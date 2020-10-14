//Range Minimum Query
#ifndef __RMQ_DS
#define __RMQ_DS

#include <vector>
#include <algorithm>
using std::vector;
using std::min;


//˼�룬�����ѯ��Сֵquery[L��R]��
//d(i,j)��ʾ��i��ʼ������Ϊ2��j�η���һ��Ԫ�ص���Сֵ
//d(i,j)=min( d(i,j-1),d(i+len,j-1) ) ���У�lenΪ2��j-1�η�



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


//��ѯ����[L,R]��Сֵ����������� 2��k�η�<= R-L+1 �����kֵ������L��ͷ����R��β����������Ϊ2��k�η�������ض���������
//[L,R]�����ֵ����Ϊ������Сֵ����Щֵ���ظ�����Ҳû��ϵ,
//(R-L+1)Ϊ����ĳ��ȣ�ֻҪ�������߽��ұ�֤ȡ������ֵ����

int RMQ(int L,int R)
{
	int k=0;
	while((1<<(k+1) <= R-L+1)) ++k;
	return min(d[L][k],d[R-(1<<k)+1][k]);
}

#endif