#ifndef __MONOTONE_STACK_H
#define __MONOTONE_STACK_H

#include <vector>
#include <stack>


//refer to leetcode
//1130.Minimum Cost Tree From Leaf Values
//503.Next Greater Element II
//907.Sum of Subarray Minimums

//paradigm
void Paradigm()
{
   std::vector<int> A;
   // an increasing stack
   std::stack<int> st;
   for (int i=0;i<A.size();++i)
   {
	   while(!st.empty() && st.top()>A[i])
	   {
		   st.pop();
	   }
	   st.push(A[i]);
   }
}



//previous less element(PLE)
void PLE()
{
	std::vector<int> A;

	//store index
	std::stack<int> st;
	std::vector<int> previous_less(A.size,-1);
	for (int i=0;i<A.size();++i)
	{
		while(!st.empty && A[st.top()]>A[i])
		{
			st.pop();
		}
		previous_less[i] = st.empty()?-1:st.top();
		st.push(i);
	}
}


//next less element (NLE)
void NLE()
{
	std::vector<int> A;

	//store index
	std::stack<int> st;
	std::vector<int> next_less(A.size,-1);
	for (int i=0;i<A.size();++i)
	{
		while(!st.empty() && A[st.top()]>A[i])
		{
			auto x = st.top();
			st.pop();
			next_less[x]=A[i];
		}
		st.push(i);
	}
}
#endif
