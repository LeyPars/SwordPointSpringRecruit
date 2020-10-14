/*
MESI����һ����Э�飺
1.CPU����Ļ�����λΪ������
2.M��Modified��,E(Exclusive),S(Shared),I(Invalid)
3.M:���������е����ݱ��޸��ˣ��˻����е����ݺ��ڴ��еĲ�һ��
  E:�û����е�����ֻ����ǰCPU���棬���������ڴ���һ��
  S:�û����б����CPU���棬�һ��������ڴ�һ��
  I:��ǰ�����е���������Ч��


LRU-K�����㷨
���������LRU�㷨�Ļ�����Ⱦ���⣬����˼���ǽ������ʹ�ù�1�Ρ����жϱ�׼��չΪ�����ʹ�ù�k�Ρ�
����ԭ��
     �����LRU,LRU-K��Ҫ��ά��һ�����У����ڼ�¼���л������ݱ����ʵ���ʷ��ֻ�е����ݵ�
	 ���ʴ����ﵽK�ε�ʱ�򣬲Ž����ݷ��뻺�档����Ҫ��̭����ʱ��LRU-K����̭��K�η���ʱ���
	 ��ǰʱ����������
��ϸʵ�����£�
	1.���ݵ�һ�η��ʣ����뵽������ʷ�б�
	2.��������ڷ�����ʷ�б���û�дﵽK�η��ʣ�����һ��������̭��FIFO,LRU��
	3.��������ʷ�����е����ݷ��ʴ����ﵽK�κ󣬽�������������ʷ������ɾ�����������ƶ����������
	  �У�����������ݣ�����������°���ʱ������
	4.�������ݶ����б��ڴ˷��ʺ���������
	5.��Ҫ��̭����ʱ����̭�������������ĩβ�����ݣ�����̭������K�η�����������õ�����
*/
#include <list>
#include <map>
using namespace std;
typedef pair<int,int> PII;
class LRU_K
{
private:
	int K;        //LRU-K��Kֵ
	list<int> qu; //������ʷ����
	int qu_capacity; //��ʷ���еĴ�С
	unordered_map<int,int> quhash;  //������ʷ���м���

	list<PII> lrulist;
	unordered_map<int,list<PII>::iterator> lruhash;
	int capacity;
public:
	int visit(int key)
	{
		if(lruhash.count(key))
		{
			return LRU_Get(key);
		}

		//���ڴ��л�����ж�ȡkey����ֵ
		int val = 0;
		//����key
		if(quhash.count(key) && quhash[key] + 1 == K)
		{
			//�Ƴ����е�keyֵ������뻺�����
			auto tarversal = qu.begin();
			while(tarversal != nullptr)
			{
				if(*tarversal == key)
				{
					auto nxt = tarversal + 1;
					lrulist.erase(tarversal);
					tarversal = nxt;
				} else {
					tarversal = tarversal + 1;
				}
			}
			quhash.erase(key);
			LRU_Set(key,val);
		} else {
			if (qu.size() == qu_capacity) {
				int dyingoff = qu.front();
				qu.pop_front();
				if(--quhash[dyingoff]==0) quhash.erase(dyingoff);
			}
			qu.push_back(key);
			quhash[key]++;
		}
		return val;
	}

private:
	int LRU_Get(int key)
	{
		auto spot = lruhash.find(key);
		if(spot==lruhash.end()) return -1;
		int ans = spot->second->second;
		lrulist.push_front(make_pair(key,ans));
		lrulist.erase(spot->second);
		lruhash[key] = lrulist.begin();
		return ans;
	}

	void LRU_Set(int key,int val)
	{
		auto spot = lruhash.find(key);
		if(spot != lruhash.end())
		{
			lrulist.erase(spot->second);
		} else if(lruhash.size() == capacity)
		{
			lruhash.erase(lrulist.back().first);
			lrulist.pop_back();
		}
		lrulist.push_front(make_pair(key,val));
		lruhash[key] = lrulist.begin();
	}
};
/*
2Q����

*/