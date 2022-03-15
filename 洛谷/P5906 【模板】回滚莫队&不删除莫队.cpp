#include <cmath>
#include <cstdio>
#include <bitset>
#include <cstring>
#include <algorithm>
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
using namespace std;
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
const int N=2e5+5;
int n,m,a[N],p[N],c[N];
int block,belong[N];
int num,L[N],R[N];
struct Queue
{
	int l,r,id;
	inline bool operator <(const Queue&rhs)const
	{
		return belong[l]==belong[rhs.l]?r<rhs.r:belong[l]<belong[rhs.l];
	}
} q[N];
int ans,answer[N];
int maxx[N],minn[N],nowmax[N];
inline void add(int pos)
{
	maxx[c[pos]]=max(maxx[c[pos]],pos);
	minn[c[pos]]=min(minn[c[pos]],pos);
	ans=max(ans,maxx[c[pos]]-minn[c[pos]]);
}
signed main()
{
	read(n);
	block=(int)sqrt(n);
	num=n/block+(n%block!=0);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		p[i]=a[i];
		belong[i]=(i-1)/block+1;
	}
	read(m);
	for(re int i=1; i<=m; ++i)
	{
		read(q[i].l,q[i].r);
		q[i].id=i;
	}
	for(re int i=1; i<=num; ++i)
	{
		L[i]=R[i-1]+1;
		R[i]=R[i-1]+block;
	}
	R[num]=n;
	sort(p+1,p+1+n);
	sort(q+1,q+1+m);
	int tot=(int)(unique(p+1,p+1+n)-p-1);
	for(re int i=1; i<=n; ++i)
		c[i]=(int)(lower_bound(p+1,p+1+tot,a[i])-p);
	int lastblock=0,r=0;
	for(re int now=1; now<=m; ++now)
	{
		const int &ql=q[now].l,&qr=q[now].r;
//		printf(" %d %d %d\n",ql,qr,q[now].id);
		int &nowans=answer[q[now].id];
		if(lastblock!=belong[ql])
		{
			memset(minn,0x3f,sizeof(minn));
			memset(maxx,0,sizeof(maxx));
			lastblock=belong[ql];
			r=R[lastblock]-1;
			ans=0;
		}
		if(belong[ql]==belong[qr])
		{
			for(re int i=ql; i<=qr; ++i)
				nowmax[c[i]]=i;
			for(re int i=ql; i<=qr; ++i)
			{
				nowans=max(nowans,nowmax[c[i]]-i);
				nowmax[c[i]]=0;
			}
			continue;
		}
		while(qr>r)
			add(++r);
		nowans=ans;
//		printf("-%d %d %d\n",R[lastblock],r,ans);
		for(re int i=ql; i<R[lastblock]; ++i)
			nowmax[c[i]]=i;
		for(re int i=ql; i<R[lastblock]; ++i)
		{
			nowans=max(nowans,max(nowmax[c[i]],maxx[c[i]])-i);
			nowmax[c[i]]=0;
		}
	}
	for(re int i=1; i<=m; ++i)
		printf("%d\n",answer[i]);
	return 0;
}


