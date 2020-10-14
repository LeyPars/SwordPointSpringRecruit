#ifndef __SKIP_LIST
#define __SKIP_LIST

template <class K,class E>
struct skipNode
{
	typedef pair<const K,E> pairType;
	pairType element;
	skipNode** next;   //ָ������
	skipNode(const pairType& thePair,int size):element(thePair) {next = new skipNode<K,E>*[size];}
};

template <class K,class E>
class skipList
{
private:
	float cutoff;       //ȷ������
	int levels;         //��ǰ���ķǿ�����
	int dSize;          //�ֵ�����Ը���
	int maxLevel;       //���������������
	K tailKey;          //���ؼ���
	skipNode<K,E>* headerNode;  //ͷ���ָ��
	skipNode<K,E>* tailNode;    //β���ָ��
	skipNode<K,E>** last;       //last[i]��ʾi��������

public:
	skipList(K largeKey,int maxPairs,float prob)
	{
		//
		cutoff = prob * RAND_MAX;
		maxLevel = (int)ceil(logf((float)maxPairs)/logf(1/prob)) - 1;
		levels = 0;
		dSize = 0;
		tailKey = largeKey;

		//����ͷ��㣬β��������last
		pair<K,E> tailPair;
		tailPair.first = tailKey;
		headerNode = new skipNode<K, E>(tailPair,maxLevel+1);
		tailNode = new skipNode<K,E>(tailPair,0);
		last = new skipNode<K,E>* [maxLevel+1];

		for (int i = 0; i <= maxLevel; ++i)
		{
			headerNode->next[i] = tailNode;
		}
	}

	pair<const K,E>* find(const K& theKey) const
	{
		if(theKey >= tailKey) return NULL;
		skipNode<K,E>* beforeNode = headerNode;
		for (int i = levels; i >= 0; i--)
		{
			while(beforeNode->next[i]->element.first < theKey)
				beforeNode = beforeNode->next[i];
		}

		if(beforeNode->next[0]->element.first == theKey) 
			return &beforeNode->next[0]->element;
		return NULL;
	}

	int level() const
	{
		int lev = 0;
		while (rand() <= cutoff)
		{
			++lev;
		}
		return min(lev,maxLevel);
	}
	skipList<K,E>* search(const K& theKey) const
	{
		skipNode* beforeNode = headerNode;
		for (int i = levels; i >= 0; --i)
		{
			while(beforeNode->next[i]->element->first < theKey)
				beforeNode = beforeNode->next[i];
			last[i] = beforeNode;
		}
		return beforeNode->next[0];
	}

	void insert(const pair<const K,E>& thePair)
	{
		if(thePair.first >= tailKey)
		{
			ostringstream s;
			s<<"key = "<<thePair.first<<"Must be"<<tailKey;
			return;
		}

		skipNode<K,E>* theNode = search(thePair.first);
		if(theNode->element.first == thePair.first)
		{
			theNode->element.second = thePair.second;
			return;
		}

		int theLevel = level();
		if(theLevel > levels)
		{
			theLevel = ++levels;
			last[theLevel] = headerNode;
		}

		skipNode<K,E>* newNode = new skipNode<K, E>(thePair,theLevel+1);
		for (int i = 0; i <= theLevel; i++)
		{
			newNode->next[i] = last[i]->next[i];
			last[i]->next[i] = newNode;
		}

		dSize++;

		return;
	}

	void erase(const K& theKey)
	{
		if(theKey = tailKey) return;
		skipNode<K,E>* theNode = search(theKey);
		if (theNode->element.first != theKey)
		{
			return;
		}
		for (int i = 0; i <= theLevel && last[i]->next[i] == theNode; i++)
		{
			last[i]->next = theNode->next[i];
		}

		while(levels > 0 && headerNode->next[levels] == tailNode)
		{
			levels--;

			//�˴��Ƿ���д��󣬴��ڶ��ɾ���Ŀ�����
			//delete theNode;
			//dSize--;
		}

		delete theNode;
		dSize--;
	}
};

#endif