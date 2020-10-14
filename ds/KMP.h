#ifndef __KMP_H
#define __KMP_H

#include <cstring>
#include <iostream>
#include <vector>
using namespace std;


/*
void find(char* T,char* P,int* f)
{
	//TΪ�ı�����PΪģʽ����fΪʧ�亯��
	int n = strlen(T), m = strlen(P);
	getFail(P,f);
	int j = 0;
	for (int i=0; i<n; i++)
	{
		while(j&&P[j]!=T[i]) j=f[j];  //˳��ʧ����ߣ�ֱ������ƥ��
		if(P[j]==T[i]) j++;
		if(j == m) printf("%d\n",i-m+1);
	}

}


void getFail(char* P,int* f)
{
	int m = strlen(P);
	//c++Ӧ����f����m+1�Ŀռ䣬
	//f�����next���飬f[i]��ʾ��iλ��֮ǰ��ǰ׺�����ƥ�䳤�ȣ�������iλ��ʧ��ʱӦ��������һ��λ��
	f[0]=f[1]=0;
	for (int i=1;i<m;++i)
	{
		int j=f[i];			  //jΪf[i]ʧ��λ��
		while(j&&P[i]!=P[j]) j=f[i];	  //��f[i+1]Ҳ�����ڴ�ƥ�䣬�����ʧ��λ��
		f[i+1] = P[i]==P[j]?j+1:0;
	}
}
*/


namespace KMP
{
	const int MAXN = 5005;
	int next[MAXN];
	void build(string& pattern) {
		const int n = pattern.size();
		for(int i = 0 , j = next[0] = -1; i < n; next[++i] = ++j) {
			while(~j && pattern[i] != pattern[j]) j = next[j];
		}
	}

	void kmp(string pattern,string text) {
		vector<int> res;
		const int n = pattern.size();
		const int m = text.size();
		for(int i = 0, j = 0; i < m; ++i) {
			while(j > 0 && text[i] != pattern[j]) j = next[j];
			if(text[i] == pattern[j]) ++j;
			if(j == n) res.push_back(i - n + 1), j = next[j];
		}

		for(auto spot:res){
			cout<<spot<<endl;
		}
	}
}
#endif
