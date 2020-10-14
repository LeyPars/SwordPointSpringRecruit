//segment tree
#ifndef __ST_DS
#define __ST_DS

#include <algorithm>
using std::min;
using std::max;

#define INF 1E9+7
#define MaxCount 10000+5;
//���ڵ��0��ʼ���
//����ÿ�����Ϊi�Ľڵ㣬�������ӽڵ�ı�ŷֱ�Ϊ2i��2i+1


//version1:������£�����ѯ��
namespace ST_VERSION_ONE
{
	//problem primitive:
	//����һ����n��Ԫ�ص�����A��������ݽṹ֧���������ֲ���
	//operation 1��update��x,v�� ��Ax��ֵ�޸�Ϊv;
	//operation 2: Query(L,R) ����min{AL,AL+1,...AR}
	//���ڸ��²�������RMQÿ�ζ�Ҫ���½�������˲�����RMQ

	int minv[MaxCount];    //��������ڵ㱣�����Сֵ

	int ql,qr; //��ѯ[ql,qr]����Сֵ
	int query(int o,int L,int R)    //oΪ��ǰ�ڵ��ţ�L��RΪ��ǰ�ڵ����Ҷ˵�
	{
		int M = L+ (R-L)/2,ans = INF;
		if (ql<=L && R <=qr) return minv[o];
		if (ql<=M)
		{
			//������
			ans = min(ans,query(o*2,L,M));
		}
		if (M < qr)
		{
			//������
			ans = min(ans,query(2*o+1,M+1,R));
		}
		return ans;
	}


	int p,v;     //�޸�A[p]=v;
	void update(int o,int L,int R)
	{
		int M = L+(R-L)/2;
		if(L==R) minv[o] = v;  //Ҷ�ڵ㣬ֱ�Ӹ���
		else
		{
			//�ݹ����
			if (p<=M)
			{
				//����������
				update(o*2,L,M);
			}
			else
			{
				update(2*o+1,M+1,R);
			}
		}
		minv[o] = min(minv[2*o],minv[2*o+1]);
	}
}


//version2��������£�����ѯ�ʣ�ֻ���ǣ����Ʊ�ǣ�
namespace ST_VERSION_TWO
{
	//problem primitive:
	//����һ����n��Ԫ�ص�����A��������ݽṹ֧���������ֲ���
	//operation 1��Add��L,R,v�� ��AL��AR��ֵȫ������v;
	//operation 2: Query(L,R) ����min{AL,AL+1,...AR}
	//             max{AL,AL+1,...AR}��sum{AL,AL+1,...AR}
	int sumv[MaxCount],minv[MaxCount],maxv[MaxCount];
	int addv[MaxCount];

	void maintain(int o,int L,int R)
	{
		int lc=2*o,rc=2*o+1;
		sumv[o]=minv[o]=maxv[o]=0;
		if (R>L)
		{
			sumv[o] = sumv[lc] + sumv[rc];
			maxv[o] = max(maxv[lc],maxv[rc]);
			minv[o] = min(minv[lc],minv[rc]);
		}
		//���뵱ǰ�ڵ�ı��
		sumv[o] += addv[o];maxv[o] += addv[o];minv[o] += addv[o];
	}

	//��[y1,y2]��ֵȫ����v
	void update(int o,int L,int R,int y1,int y2,int v)
	{
		int lc=2*o,rc=2*o+1;
		if(y1<=L && R<=y2)
		{
			addv[o]+=v;
		}
		else
		{
			int M = L+(R-L)/2;
			if(y1<=M) update(lc,L,M,y1,y2,v);
			if(M<y2) update(rc,M+1,R,y1,y2,v);
		}
		maintain(o,L,R);
		//�ݹ���������¼��㱾�ڵ�ĸ�����Ϣ
	}


	//ѯ��ʱ���һ����ǲ����������ۼӱ��
	int _min,_max,_sum;
	void query(int o,int L,int R,int add��int y1,int y2)
	{
		//�ۼƱ�ǣ�ֻ���ǣ��������ƣ�
		if (y1<=L&&R<=y2)
		{
			_sum += sumv[o]+add*(R-L+1);
			_min = min(_min,minv[o]+add);
			_max = max(_max,maxv[o]+add);
		}
		else
		{
			int M = L+(R-L>>1);
			if(y1<=M) query(2*o,L,M,add+addv[o],y1,y2);
			if(M<y2) query(2*o+1,M+1,R,add+addv[o],y1,y2);
		}
	}
}


namespace ST_VERSION_THREE
{
	//problem primitive:
	//����һ����n��Ԫ�ص�����A��������ݽṹ֧���������ֲ���
	//operation 1��Set��L,R,v�� ��AL��AR��ֵ�޸�Ϊv;
	//operation 2: Query(L,R) ����min{AL,AL+1,...AR}
	//             max{AL,AL+1,...AR}��sum{AL,AL+1,...AR}
}



#endif