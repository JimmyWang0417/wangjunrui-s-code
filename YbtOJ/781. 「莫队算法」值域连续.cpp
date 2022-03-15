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
using namespace std;
const int N=1e6+5;
int n,m,a[N];
int block,num,belong[N],L[N],R[N];
struct Query
{
	int l,r,id;
	inline bool operator <(const Query&rhs)const
	{
		return belong[l]==belong[rhs.l]?r<rhs.r:l<rhs.l;
	}
} q[N];
int ans,answer[N];
int c[N],cm,lst;
bool vis[N];
int fa[N],cnt[N];
inline int find(int x)
{
	return !fa[x]?x:fa[x]=find(fa[x]);
}
inline void unionn(int x,int y)
{
//	printf("%d %d ",x,y);
	x=find(x),y=find(y);
//	printf(" %d %d\n",x,y);
	if(x==y)
		return;
	fa[y]=x;
	cnt[x]+=cnt[y];
	ans=max(ans,cnt[x]);
}
inline bool cmp(int x,int y)
{
	return a[x]<a[y];
}
signed main()
{
	freopen("permu.in","r",stdin);
	freopen("permu.out","w",stdout);
	read(n,m);
	block=(int)sqrt(n);
	num=n/block+(n%block!=0);
	for(int i=1; i<=num; ++i)
	{
		L[i]=R[i-1]+1;
		R[i]=min(R[i-1]+block,n);
		for(int j=L[i]; j<=R[i]; ++j)
			belong[j]=i;
	}
	for(int i=1; i<=n; ++i)
		read(a[i]);
	for(int i=1; i<=m; ++i)
	{
		read(q[i].l,q[i].r);
		q[i].id=i;
	}
	sort(q+1,q+1+m);
	for(int i=1; i<=m; ++i)
	{
		const int ql=q[i].l,qr=q[i].r;
		if(belong[ql]!=belong[q[i-1].l])
		{
			fill(fa+1,fa+1+n,0);
			fill(cnt+1,cnt+1+n,1);
			fill(vis+1,vis+1+n,false);
			int t=belong[ql];
			ans=1,cm=0;
			for(int j=L[t]; j<=R[t]; ++j)
				c[++cm]=j;
			sort(c+1,c+1+cm,cmp);
//			for(int j=1; j<=cm; ++j)
//				printf("%d ",c[j]);
//			putchar('\n');
			lst=R[t]+1;
		}
		if(belong[ql]==belong[qr])
		{
			int len=1,pre=-1,res=0;
			for(int j=1; j<=cm; ++j)
				if(c[j]>=ql&&c[j]<=qr)
				{
					if(a[c[j]]!=pre)
					{
						res=max(res,len);
						len=1;
					}
					else
						++len;
					pre=a[c[j]]+1;
				}
			res=max(res,len);
			answer[q[i].id]=res;
		}
		else
		{
			for(int j=lst; j<=qr; ++j)
			{
				int v=a[j];
				vis[v]=true;
				if(vis[v-1])
					unionn(v,v-1);
				if(vis[v+1])
					unionn(v,v+1);
			}
//			printf("%d %d\n",q[i].id,ans);
			int res=ans,pre=-1,len=1;
			for(int j=1; j<=cm; ++j)
			{
				if(c[j]>=ql&&c[j]<=qr)
				{
					int v=a[c[j]];
					if(v!=pre)
					{
						res=max(res,len);
						len=1;
						if(vis[v-1])
							len+=cnt[find(v-1)];
					}
					else
						++len;
					if(vis[v+1])
					{
						int w=find(v+1);
						len+=cnt[w];
						pre=v+cnt[w]+1;
					}
					else
						pre=v+1;
				}
			}
			res=max(res,len);
			answer[q[i].id]=res;
			lst=qr+1;
		}
	}
	for(int i=1; i<=m; ++i)
		printf("%d\n",answer[i]);
	return 0;
}


