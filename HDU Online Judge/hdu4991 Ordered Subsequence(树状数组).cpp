#include<cstdio>
#include<algorithm>
#include<cstring>
#define re register
using namespace std;
#define lowbit(x) ((x)&(-x))
const int N=1e4+5,M=1e2+5,mod=123456789,maxn=1e4;
int c[M][N];
int n,m,a[N],p[N];
inline void update(int id,int x,int y)
{
	for(; x<=n; x+=lowbit(x))
		(c[id][x]+=y)%=mod;
}
inline int query(int id,int x)
{
	int res=0;
	for(; x; x-=lowbit(x))
		(res+=c[id][x])%=mod;
	return res;
}
int main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		memset(c,0,sizeof(c));
		for(re int i=1; i<=n; ++i)
		{
			scanf("%d",&a[i]);
			p[i]=a[i];
		}
		stable_sort(p+1,p+1+n);
		int tot=unique(p+1,p+1+n)-p-1;
		for(re int i=1; i<=n; ++i)
			a[i]=lower_bound(p+1,p+1+n,a[i])-p;
//	for(re int i=1; i<=n; ++i)
//		printf("%d ",a[i]);
		for(re int i=1; i<=n; ++i)
		{
			update(1,a[i],1);
			for(re int j=1; j<m; ++j)
			{
				int tmp=query(j,a[i]-1);
				if(!tmp)
					break;
				update(j+1,a[i],tmp);
			}
		}
		printf("%d\n",query(m,n));
	}

	return 0;
}
