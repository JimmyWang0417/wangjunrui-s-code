#include<cstdio>
#include<cstring>
#define re register
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
struct Edge
{
	int next,to,dis;
} edge[14410];
int in[200],dp[200],n,answer,kase;
bool vis[200];
struct node
{
	int x,y,z;
	inline void add(const int & x,const int & y,const int & z)
	{
		this->x=x;
		this->y=y;
		this->z=z;
	}
} cnt[200];
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
inline int DP(int x)
{
	if(vis[x])
		return dp[x];
	vis[x]=true;
	int & ans=dp[x]=cnt[x].z;
	for(re int i=1; i<=n; i++)
		if(cnt[x].x>cnt[i].x&&cnt[x].y>cnt[i].y)
			ans=max(ans,cnt[x].z+DP(i));
	return ans;
}
int main()
{
	while(read(n),n)
	{
		answer=~0x7fffffff;
		n*=0b11;
		memset(vis,false,sizeof(vis));
		for(re int i=1,x,y,z; i<=n; i+=3)
		{
			read(x);
			read(y);
			read(z);
			cnt[i].add(max(x,y),min(x,y),z);
			cnt[i+1].add(max(x,z),min(x,z),y);
			cnt[i+2].add(max(y,z),min(y,z),x);
		}
		for(re int i=1; i<=n; i++)
			answer=max(answer,DP(i));
		printf("Case %d: maximum height = %d\n",++kase,answer);
	}
	return 0;
}

