#include<cstdio>
#include<string>
#include<sstream>
#include<cstring>
#include<iostream>
#define re register
#define ll long long
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
const int N=125,S=9,INF=N*50000;
int s,n,m,dp[N][1<<S][1<<S];
bool vis[N][1<<S][1<<S];
struct node
{
	int st,val;
} a[N];
inline int DP(int i,int s0,int s1,int s2)
{
	if(i==m+n)
		return s2==(1<<s)-1?0:INF;
	int &ans=dp[i][s1][s2];
	if(vis[i][s1][s2])
		return ans;
	vis[i][s1][s2]=true;
	ans=INF;
	if(i>=m)
		ans=DP(i+1,s0,s1,s2);
	int m0=a[i].st&s0,m1=a[i].st&s1;
	s0^=m0,s1=(s1^m1)|m0,s2|=m1;
	return ans=min(ans,a[i].val+DP(i+1,s0,s1,s2));
}
int main()
{
	string st;
	while(getline(cin,st))
	{
		stringstream str(st);
		str>>s>>m>>n;
		if(s==0)
			break;
		for(re int i=0,x; i<m+n; ++i)
		{
			getline(cin,st);
			stringstream str(st);
			str>>a[i].val;
			a[i].st=0;
			while(str>>x)
				a[i].st|=1<<x-1;
		}
//		for(re int i=0;i<m+n;++i)
//		printf("%d %d\n",a[i].val,a[i].st);
		printf("%d\n",DP(0,(1<<s)-1,0,0));
		memset(vis,0,sizeof(vis));
	}
}
