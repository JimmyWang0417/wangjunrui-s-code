#include<cstdio>
#include<algorithm>
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
const int N=3e5+5,mod=998244353;
int n,ch[N*60][2],ans[N*60],tot=1;
ll lower,a[N];
inline void add(int &x,int y)
{
	x+=y;
	if(x>=mod)
		x-=mod;
}
inline void insert(ll x,int val)
{
	add(ans[1],val);
	int u=1;
	for(re int i=60; i>=0; --i)
	{
		int c=x>>i&1;
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
		add(ans[u],val);
	}
}
inline int query(ll x)
{
	int answer=0,u=1;
	for(re int i=60; i>=0; --i)
	{
		int c=x>>i&1,d=lower>>i&1;
		if(d)
			u=ch[u][c^1];
		else
		{
			add(answer,ans[ch[u][c^1]]);
			u=ch[u][c];
		}
	}
	add(answer,ans[u]);
	return answer;
}
int main()
{
	int answer=0;
	read(n);
	read(lower);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	sort(a+1,a+1+n);
	for(re int i=1; i<=n; ++i)
	{
		int cur=(query(a[i])+1)%mod;
		insert(a[i],cur);
		//printf("%d ",cur);
		add(answer,cur);
	}
	printf("%d\n",answer);
	return 0;
}
