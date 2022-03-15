#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
template<typename T>
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=1e6+5;
int n,m,ans;
int a[N];
int head[N],nxt[N],cnt[N],fa[N];
inline void work()
{
	int opt;
	read(opt);
	if(opt==1)
	{
		int x,y;
		read(x,y);
		if(x==y)
			return;
		if(cnt[fa[x]]>cnt[fa[y]])
			std::swap(fa[x],fa[y]);
		x=fa[x],y=fa[y];
		re int j;
		for(re int i=head[x]; i; i=nxt[i])
			ans-=(a[i-1]==y)+(a[i+1]==y);
		for(re int i=head[x]; i; i=nxt[i])
			a[j=i]=y;
		if(head[x])
		{
			nxt[j]=head[y];
			head[y]=head[x];
		}
		cnt[y]+=cnt[x];
		head[x]=cnt[x]=0;
	}
	else if(opt==2)
		printf("%d\n",ans);
}
signed main()
{
	read(n,m);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		++cnt[a[i]];
		fa[a[i]]=a[i];
		nxt[i]=head[a[i]];
		head[a[i]]=i;
		if(a[i]!=a[i-1])
			++ans;
	}
	while(m--)
		work();
	return 0;
}


