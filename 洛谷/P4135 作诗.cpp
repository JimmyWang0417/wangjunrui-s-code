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
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
const int N=1e5+5,M=405;
int n,c,m,a[N];
int block,num,belong[N],L[M],R[M],cnt[M][N],f[M][M];
int sum[N];
inline void build()
{
	block=(int)sqrt(n),num=n/block+(n%block!=0);
	for(re int i=1; i<=num; ++i)
	{
		L[i]=R[i-1]+1;
		R[i]=std::min(n,R[i-1]+block);
		for(re int j=L[i]; j<=R[i]; ++j)
			belong[j]=i;
	}
	for(re int i=1; i<=num; ++i)
	{
		for(re int j=0; j<=c; ++j)
			cnt[i][j]=cnt[i-1][j];
		for(re int j=L[i]; j<=R[i]; ++j)
			++cnt[i][a[j]];
		int res=0;
		for(re int j=i; j<=num; ++j)
		{
			for(re int k=L[j]; k<=R[j]; ++k)
			{
				if(!sum[a[k]])
				{
					++sum[a[k]];
					continue;
				}
				res-=!(sum[a[k]]&1);
				res+=!((++sum[a[k]])&1);
			}
			f[i][j]=res;
		}
		clear(sum,0,c,0);
	}
}
inline int count(int l,int r,int v)
{
	return cnt[r][v]-cnt[l-1][v]+sum[v];
}
inline int query(int l,int r)
{
	if(belong[r]-belong[l]<=1)
	{
		int ans=0;
		for(re int i=l; i<=r; ++i)
		{
			if(!sum[a[i]])
			{
				++sum[a[i]];
				continue;
			}
			ans-=!(sum[a[i]]&1);
			ans+=!((++sum[a[i]])&1);
		}
		clear(sum,0,c,0);
		return ans;
	}
	int ans=f[belong[l]+1][belong[r]-1];
	for(re int i=l; i<=R[belong[l]]; ++i)
	{
		if(!count(belong[l]+1,belong[r]-1,a[i]))
		{
			++sum[a[i]];
			continue;
		}
		ans-=!(count(belong[l]+1,belong[r]-1,a[i])&1);
		++sum[a[i]];
		ans+=!(count(belong[l]+1,belong[r]-1,a[i])&1);
	}
	for(re int i=L[belong[r]]; i<=r; ++i)
	{
		if(!count(belong[l]+1,belong[r]-1,a[i]))
		{
			++sum[a[i]];
			continue;
		}
		ans-=!(count(belong[l]+1,belong[r]-1,a[i])&1);
		++sum[a[i]];
		ans+=!(count(belong[l]+1,belong[r]-1,a[i])&1);
	}
	clear(sum,0,c,0);
	return ans;
}
signed main()
{
	read(n,c,m);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	build();
//	for(re int i=1; i<=n; ++i)
//		printf(" %d",belong[i]);
//	putchar('\n');
//	for(re int i=1; i<=num; ++i)
//		printf("  %d %d\n",L[i],R[i]);
	int lastans=0;
	for(re int i=1; i<=m; ++i)
	{
		int l,r;
		read(l,r);
		l=(l+lastans)%n+1,r=(r+lastans)%n+1;
		if(l>r)
			std::swap(l,r);
//		printf(" %d %d\n",l,r);
		printf("%d\n",lastans=query(l,r));
	}
	return 0;
}


