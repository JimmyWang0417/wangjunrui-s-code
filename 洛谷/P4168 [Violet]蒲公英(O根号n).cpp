#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
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
const int N=4e4+5,M=205;
int n,m,a[N];
int p[N],tot;
int block,num,cnt[M][N],f[M][N],L[M],R[M],belong[N];
int sum[N];
inline void build()
{
	block=(int)sqrt(n),num=n/block+(n%block!=0);
	for(re int i=1; i<=num; ++i)
	{
		L[i]=R[i-1]+1;
		R[i]=R[i-1]+block;
		for(re int j=L[i]; j<=R[i]; ++j)
			belong[j]=i;
	}
	R[num]=n;
	for(re int i=1; i<=num; ++i)
	{
		memcpy(cnt[i]+1,cnt[i-1]+1,tot*sizeof(int));
		for(re int j=L[i]; j<=R[i]; ++j)
			++cnt[i][a[j]];
		int res=0;
		for(re int j=i; j<=num; ++j)
		{
			for(re int k=L[j]; k<=R[j]; ++k)
			{
				++sum[a[k]];
				if(sum[a[k]]>sum[res]||sum[a[k]]==sum[res]&&a[k]<res)
					res=a[k];
			}
			f[i][j]=res;
		}
		clear(sum,1,tot,0);
	}
}
#define count(l,r,v) (cnt[r][v]-cnt[(l)-1][v]+sum[v])
inline int query(int l,int r)
{
	if(belong[r]-belong[l]<=1)
	{
		int ans=0;
		for(re int i=l; i<=r; ++i)
		{
			++sum[a[i]];
			if(sum[a[i]]>sum[ans]||sum[a[i]]==sum[ans]&&a[i]<ans)
				ans=a[i];
		}
		clear(sum,1,tot,0);
		return ans;
	}
	int ans=f[belong[l]+1][belong[r]-1];
	for(re int i=l; i<=R[belong[l]]; ++i)
	{
		++sum[a[i]];
		if(count(belong[l]+1,belong[r]-1,a[i])>count(belong[l]+1,belong[r]-1,ans)||
		        count(belong[l]+1,belong[r]-1,a[i])==count(belong[l]+1,belong[r]-1,ans)&&a[i]<ans)
			ans=a[i];
	}
	for(re int i=L[belong[r]]; i<=r; ++i)
	{
		++sum[a[i]];
		if(count(belong[l]+1,belong[r]-1,a[i])>count(belong[l]+1,belong[r]-1,ans)||
		        count(belong[l]+1,belong[r]-1,a[i])==count(belong[l]+1,belong[r]-1,ans)&&a[i]<ans)
			ans=a[i];
	}
	clear(sum,1,tot,0);
	return ans;
}
signed main()
{
	read(n,m);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		p[i]=a[i];
	}
	std::sort(p+1,p+1+n);
	tot=(int)(std::unique(p+1,p+1+n)-p-1);
	for(re int i=1; i<=n; ++i)
		a[i]=(int)(std::lower_bound(p+1,p+1+tot,a[i])-p);
//	for(re int i=1; i<=n; ++i)
//	{
//		printf("%d ",a[i]);
//	}
//	putchar('\n');
	build();
//	for(re int i=1; i<=num; ++i)
//		printf(" %d %d\n",L[i],R[i]);
//	for(re int i=1; i<=n; ++i)
//		printf(" %d",belong[i]);
//	putchar('\n');
	int lastans=0;
	for(re int i=1; i<=m; ++i)
	{
		int l,r;
		read(l,r);
		l=(l+lastans-1)%n+1,r=(r+lastans-1)%n+1;
		if(l>r)
			std::swap(l,r);
//		printf(" %d %d\n",l,r);
		printf("%d\n",lastans=p[query(l,r)]);
	}
	return 0;
}
