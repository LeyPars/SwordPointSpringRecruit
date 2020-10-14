#ifndef __SUFFIX_H
#define __SUFFIX_H

#include <algorithm>
using std::swap;

//后缀数组（倍增法求rank数组）


const int MAXN = 10000+5;
char s[MAXN];
int sa[MAXN],t[MAXN],t2[MAXN],c[MAXN],n;
//构造字符串s的后缀数组，每个字符值必须为0~m-1
void build_sa(int m)
{
	char s[MAXN] = "1233222755";
	n = 20;
	int i,*x=t,*y=t2;
	//基数排序
	for (i=0;i<m;++i) c[i]=0;	           //计数数组清零
	for (i=0;i<n;++i) c[x[i]=s[i]]++;	   //将字符转存为数字并计数
	for (i=1;i<m;++i) c[i] +=c[i-1];       //将计数数组求前缀和
	for (i=n-1;i>=0;i--) sa[--c[x[i]]]=i;  //按照原顺序插入int数组（离散化）

	for (int k=1; k<=n; k<<=1)
	{
		int p=0;
		//直接利用sa数组排序第二关键字
		for(i=n-k;i<n;i++) y[p++]=i;
		for(i=0;i<n;i++) if(sa[i]>=k) y[p++]=sa[i]-k;
		//基数排序第一关键字
		for(i=0;i<m;i++) c[i]=0;
		for(i=0;i<n;i++) c[x[y[i]]]++;
		for (i=1;i<m;++i) c[i] +=c[i-1];    
		for (i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];

		//根据sa和y计算新的x数组
		swap(x,y);
		p=1;x[sa[0]]=0;
		for (i=1;i<n;i++)
		{
			x[sa[i]]= y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;
		}
		if(p>=n) break;	 //以后即使继续倍增，sa也不会改变，退出
		m=p;             //下次基数排序的最大值
	}

}

#endif
