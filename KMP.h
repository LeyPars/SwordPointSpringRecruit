#ifndef __KMP_H
#define __KMP_H

#include <cstring>
#include <iostream>
#include <vector>
using namespace std;


/*
void find(char* T,char* P,int* f)
{
	//T为文本串，P为模式串，f为失配函数
	int n = strlen(T), m = strlen(P);
	getFail(P,f);
	int j = 0;
	for (int i=0; i<n; i++)
	{
		while(j&&P[j]!=T[i]) j=f[j];  //顺着失配边走，直到可以匹配
		if(P[j]==T[i]) j++;
		if(j == m) printf("%d\n",i-m+1);
	}

}


void getFail(char* P,int* f)
{
	int m = strlen(P);
	//c++应当给f分配m+1的空间，
	//f数组或next数组，f[i]表示在i位置之前的前缀的最大匹配长度，亦是在i位置失配时应当检查的下一个位置
	f[0]=f[1]=0;
	for (int i=1;i<m;++i)
	{
		int j=f[i];			  //j为f[i]失配位置
		while(j&&P[i]!=P[j]) j=f[i];	  //若f[i+1]也不能在此匹配，则更新失配位置
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
