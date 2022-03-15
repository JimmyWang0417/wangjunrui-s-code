#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#define re register
using namespace std;
const int N=15,M=105;
int n,m,u[M],v[M],ind[1<<N],dp[1<<N],best[1<<N],label[N];
bool g[N][N];
inline bool independent(int S)
{
	for(re int i=0; i<N; ++i)
		if(S&(1<<i))
			for(re int j=0; j<N; ++j)
				if((S&(1<<j))&&i!=j&&g[i][j])
					return false;
	return true;
}
inline int DP(int mask)
{
	int &ans=dp[mask];
	if(ans>=0)
		return ans;
	if(mask==0)
		return ans=0;
	ans=N+1;
	for(re int s=mask; s; s=(s-1)&mask)
		if(ind[s])
		{
			int v=DP(mask^s)+1;
			if(ans>v)
			{
				ans=v;
				best[mask]=s;
			}
		}
	return ans;
}
inline void work(int s,int c)
{
	for(re int i=0; i<N; ++i)
		if(s&(1<<i))
			label[i]=c;
}
int main()
{
	while(cin>>n)
	{
		memset(g,0,sizeof(g));
		int useful=0;
		for(re int i=0; i<n; ++i)
		{
			char r1,r2;
			cin>>r1>>r2;
			u[i]=r1-'L';
			v[i]=r2-'L';
			g[u[i]][v[i]]=true;
			useful=useful|(1<<u[i])|(1<<v[i]);
		}
		memset(dp,-1,sizeof(dp));
		memset(ind,false,sizeof(ind));
		for(re int s=useful; s; s=(s-1)&useful)
			ind[s]=independent(s);
		printf("%d\n",DP(useful)-2);
		int s=useful,k=0;
		while(s)
		{
			work(s,k++);
			s=s^best[s];
		}
		for(re int i=0; i<n; ++i)
		{
			if(label[u[i]]<label[v[i]])
				swap(u[i],v[i]);
			printf("%c %c\n",u[i]+'L',v[i]+'L');
		}
	}
}
