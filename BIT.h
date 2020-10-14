//¶ş²æË÷ÒıÊ÷
#ifndef __BIT_BS
#define __BIT_BS

#include <string.h>
#define lowbit(x)  (x&(-x))


//Bit definition
//begin at index of 1
//C[i] = A[i-lowbit(i)+1]+A[i-lowbit(i)+2]+...+A[i];

const int MaxCount = 10000+5;
int C[MaxCount];

void clear()
{
	memset(C,0,sizeof(C));
}

int sum(int x)
{
	int ret=0;
	while(x>0)
	{
		ret+=C[x];
		x-=lowbit(x);
	}
	return ret;
}

void add(int x,int d)
{
	while (x<MaxCount)
	{
		C[x]+=d;
		x+=lowbit(x);
	}
}

#endif