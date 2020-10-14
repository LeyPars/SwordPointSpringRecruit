#ifndef __TRIE_H
#define __TRIE_H



//�ֵ���
//ǰ׺��
#define maxnode 10000+5
#define sigma_size 26
struct Trie
{
	int ch[maxnode][sigma_size];
	int val[maxnode];
	int sz;                  //�ڵ�����
	Trie(){
		sz=1;
		memset(ch[0],0,sizeof(ch[0]));
		//��ʼ�����ڵ�
	}
	int idx(char c){return c-'a';} //������ĸ��Ӧ���


	void insert(char* s,int v)
	{
		//���ַ�s�����ֵ������Ҹ�����Ϣv����Ϊ0����ʾΪ���ʽڵ㣩
		int u = 0, n = strlen(s);
		for (int i=0;i<n;++i)
		{
			int c=idx[s[i]];
			if(!ch[u][c])
			{
				//�ڵ㲻����(�½��м�ڵ�)
				memset(ch[sz],0,sizeof(ch[sz]));  //���½ڵ��ch������0
				val[sz]=0;						  //�½ڵ��val��Ϊ0����ʾ���ǵ���
				ch[u][c]=sz++;					  //�½ڵ�ı�Ŵ�����һ��ch�У������ӽڵ���
			}
			u = ch[u][c];						  //������
		}
		val[u]=v;							      //���µ��ʵĸ���ֵ
	}
};

#endif
