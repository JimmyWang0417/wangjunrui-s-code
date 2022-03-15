#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#define il inline
using namespace std;

int n;
vector<int> block[30];

//返回木块a所在的p
il int find_p(int a)
{
	int i,j;
	for (i=0; i<n; i++)
	{
		for (j=0; j<block[i].size(); j++)
		{
			if (block[i][j]==a)
				return i;
		}
	}
}

//返回木块a所在的h
il int find_h(int a)
{
	int i,j;
	for (i=0; i<n; i++)
	{
		for (j=0; j<block[i].size(); j++)
		{
			if (block[i][j]==a)
				return j;
		}
	}
}

//把第p堆高为h的木块上面的所有木块移回原位
il void doing(int p,int h)
{
	int i;
	for (i=h+1; i<block[p].size(); i++)
	{
		int where=block[p][i];

		block[where].push_back(where);
	}

	block[p].resize(h+1);
}

//把第p堆高度为h的木块及其以上所有木块的整体移到第p2堆的顶端
il void onto(int p,int h,int pp)
{
	int i;
	for (i=h; i<block[p].size(); i++)
	{
		block[pp].push_back(block[p][i]);
	}

	block[p].resize(h);
}

//初始化
il void init()
{
	scanf("%d",&n);

	int i;
	for (i=0; i<n; i++)
	{
		block[i].push_back(i);
	}
}

//解决
il void solve()
{
	int a,b;
	string s1,s2;
	while (cin>>s1)
	{
		if (s1=="quit") break;

		cin>>a>>s2>>b;

		int pa,pb,ha,hb;

		pa=find_p(a),ha=find_h(a),
		pb=find_p(b),hb=find_h(b);

		if (pa==pb) continue;//非法指令

		if (s2=="onto") doing(pb,hb);
		if (s1=="move") doing(pa,ha);

		onto(pa,ha,pb);
	}
}

//输出
il void print()
{
	int i,j;
	for (i=0; i<n; i++)
	{
		printf("%d:",i);

		for (j=0; j<block[i].size(); j++)
		{
			printf(" %d",block[i][j]);
		}

		printf("\n");
	}
}

int main()
{
	init();
	solve();
	print();

	return 0;
}
