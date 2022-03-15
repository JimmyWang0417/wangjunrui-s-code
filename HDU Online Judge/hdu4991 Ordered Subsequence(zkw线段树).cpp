#include<cstdio>
#include<algorithm>
#include<cstring>
#define re register
using namespace std;
#define lowbit(x) ((x)&(-x))
const int M=1e4+5,N=1e2+5,mod=123456789,maxn=1e4;
int tr[N][M<<1|1];
int n,m,a[M],p[M];
inline void update(int id,int x,int y)
{
	int *tree=tr[id];
	for(tree[x+=M]+=y,x>>=1; x; x>>=1)
		tree[x]=(tree[x<<1]+tree[x<<1|1])%mod;
}
inline int query(int id,int x,int y)
{
	int res=0;
	int *tree=tr[id];
	for(re int s=x+M-1,t=y+M+1; s^t^1; s>>=1,t>>=1)
	{
		if(~s&1)
			(res+=tree[s^1])%=mod;
		if(t&1)
			(res+=tree[t^1])%=mod;
	}
	return res;
}
int main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
	{
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
				int tmp=query(j,1,a[i]-1);
				if(!tmp)
					break;
				update(j+1,a[i],tmp);
			}
		}
		printf("%d\n",query(m,1,n));
		for(re int i=1; i<=m; ++i)
		{
			int *tree=tr[i];
			memset(tree,0,4*(n+M+1));
		}
	}
	return 0;
}
