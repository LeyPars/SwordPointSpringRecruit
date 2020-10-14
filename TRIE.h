#ifndef __TRIE_H
#define __TRIE_H



//字典树
//前缀树
#define maxnode 10000+5
#define sigma_size 26
struct Trie
{
	int ch[maxnode][sigma_size];
	int val[maxnode];
	int sz;                  //节点总数
	Trie(){
		sz=1;
		memset(ch[0],0,sizeof(ch[0]));
		//初始化根节点
	}
	int idx(char c){return c-'a';} //返回字母对应编号


	void insert(char* s,int v)
	{
		//将字符s插入字典树，且附带信息v（不为0，表示为单词节点）
		int u = 0, n = strlen(s);
		for (int i=0;i<n;++i)
		{
			int c=idx[s[i]];
			if(!ch[u][c])
			{
				//节点不存在(新建中间节点)
				memset(ch[sz],0,sizeof(ch[sz]));  //将新节点的ch数组清0
				val[sz]=0;						  //新节点的val设为0，表示并非单词
				ch[u][c]=sz++;					  //新节点的编号存入上一级ch中，并增加节点编号
			}
			u = ch[u][c];						  //往下走
		}
		val[u]=v;							      //更新单词的附加值
	}
};

#endif
