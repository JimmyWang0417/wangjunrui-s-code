#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <vector>
#include <cstdio>
#include <bitset>
#include <cstring>
#include <iostream>
#include <algorithm>
#define lowbit(x) (x&(-x))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
using namespace std;
const int N=2e4+5;
int fa[N],dis[N];
inline int find(int x)
{
	if(fa[x]==x)
		return x;
	int f=find(fa[x]);
	dis[x]^=dis[fa[x]];
	return fa[x]=f;
}
int id;
bool stop;
inline void unionn(int x,int y,int w)
{
	int fx=find(x),fy=find(y);
	if(fx==fy)
	{
		int d=dis[x]^dis[y];
		if(d!=w)
		{
			printf("The first %d facts are conflicting.\n",id);
			stop=true;
		}
		return;
	}
	if(!fy)
		swap(fx,fy);
	fa[fy]=fx;
	dis[fy]=dis[x]^dis[y]^w;
}
int cnt[N],a[N];
signed main()
{
	int n,m,kase=0;
	while(scanf("%d%d",&n,&m)&&(n||m))
	{
//		printf("   %d %d\n",n,m);
		printf("Case %d:\n",++kase);
		id=0;
		stop=false;
		for(re int i=1; i<=n; ++i)
		{
			fa[i]=i;
			dis[i]=0;
		}
		while(m--)
		{
			char opt[2];
			scanf("%s",opt);
			if(opt[0]=='I')
			{
				++id;
				int p,q,v;
				scanf("%d%d",&p,&q);
				char ch=(char)getchar();
				if(ch==' ')
				{
					scanf("%d",&v);
					unionn(p+1,q+1,v);
				}
				else
					unionn(0,p+1,q);
			}
			else if(opt[0]=='Q')
			{
				bool flag=false;
				int ans=0,k;
				scanf("%d",&k);
				for(re int i=1; i<=k; ++i)
				{
					scanf("%d",&a[i]);
					++a[i];
					int f=find(a[i]);
//					printf("%d ",f);
					if(f)
						++cnt[f];
					ans=ans^dis[a[i]];
				}
//				putchar('\n');
				if(stop)
					continue;
				for(re int i=1; i<=k; ++i)
				{
					int f=find(a[i]);
					if(f)
					{
						if(cnt[f]&1)
							flag=true;
						cnt[f]=0;
					}
				}
				if(flag)
					printf("I don't know.\n");
				else
					printf("%d\n",ans);
			}
		}
		putchar('\n');
	}
	return 0;
}


