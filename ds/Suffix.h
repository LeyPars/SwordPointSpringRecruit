#ifndef __SUFFIX_H
#define __SUFFIX_H

#include <algorithm>
using std::swap;

//��׺���飨��������rank���飩


const int MAXN = 10000+5;
char s[MAXN];
int sa[MAXN],t[MAXN],t2[MAXN],c[MAXN],n;
//�����ַ���s�ĺ�׺���飬ÿ���ַ�ֵ����Ϊ0~m-1
void build_sa(int m)
{
	char s[MAXN] = "1233222755";
	n = 20;
	int i,*x=t,*y=t2;
	//��������
	for (i=0;i<m;++i) c[i]=0;	           //������������
	for (i=0;i<n;++i) c[x[i]=s[i]]++;	   //���ַ�ת��Ϊ���ֲ�����
	for (i=1;i<m;++i) c[i] +=c[i-1];       //������������ǰ׺��
	for (i=n-1;i>=0;i--) sa[--c[x[i]]]=i;  //����ԭ˳�����int���飨��ɢ����

	for (int k=1; k<=n; k<<=1)
	{
		int p=0;
		//ֱ������sa��������ڶ��ؼ���
		for(i=n-k;i<n;i++) y[p++]=i;
		for(i=0;i<n;i++) if(sa[i]>=k) y[p++]=sa[i]-k;
		//���������һ�ؼ���
		for(i=0;i<m;i++) c[i]=0;
		for(i=0;i<n;i++) c[x[y[i]]]++;
		for (i=1;i<m;++i) c[i] +=c[i-1];    
		for (i=n-1;i>=0;i--) sa[--c[x[y[i]]]]=y[i];

		//����sa��y�����µ�x����
		swap(x,y);
		p=1;x[sa[0]]=0;
		for (i=1;i<n;i++)
		{
			x[sa[i]]= y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;
		}
		if(p>=n) break;	 //�Ժ�ʹ����������saҲ����ı䣬�˳�
		m=p;             //�´λ�����������ֵ
	}

}

#endif
