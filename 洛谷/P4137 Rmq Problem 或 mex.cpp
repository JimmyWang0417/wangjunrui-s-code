#include <bits/stdc++.h>
#define lowbit(x) (x&(-x))
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
const int N=2e5+5;
int n,m,a[N];
int cnt[N];
inline int find()
{
	for(re int i=0; i<=n; ++i)
		if(!cnt[i])
			return i;
	return n+1;
}
using std::cerr;
using std::endl;
using std::min;
using std::lower_bound;
using std::unique;
using std::sort;
int p[N],tot;
int belong[N],L[N],R[N],block,num;
struct Queue
{
	int l,r,id;
	inline bool operator <(const Queue&rhs)const
	{
		return belong[l]==belong[rhs.l]?r>rhs.r:belong[l]<belong[rhs.l];
	}
} q[N];
int ans;
inline void del(int val)
{
	if(!(--cnt[val]))
		ans=min(ans,val);
}
int answer[N];
signed main()
{
	read(n,m);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i]);
		if(a[i]<=n)
			++cnt[a[i]];
	}
	for(re int i=1; i<=m; ++i)
	{
		read(q[i].l,q[i].r);
		q[i].id=i;
	}



	const int MAX=find();
//	printf(" %d\n",cnt[0]);
	for(re int i=1; i<=n; ++i)
		a[i]=min(MAX+1,a[i]);
//	for(re int i=1; i<=n; ++i)
//		printf("%d ",a[i]);
//	putchar('\n');

	block=(int)sqrt(n);
	for(re int i=1; i<=n; ++i)
		belong[i]=(i-1)/block+1;
	num=n/block+(n%block!=0);
	for(re int i=1; i<=num; ++i)
	{
		L[i]=R[i-1]+1;
		R[i]=R[i-1]+block;
	}
	R[num]=n;
//	for(re int i=1; i<=num; ++i)
//		printf("`%d %d\n",L[i],R[i]);
	sort(q+1,q+1+m);

	int lastblock=0,r=0;
	for(re int now=1; now<=m; ++now)
	{
		const int &ql=q[now].l,&qr=q[now].r;
		if(belong[ql]!=lastblock)
		{
			memset(cnt,0,sizeof(cnt));
			lastblock=belong[ql];
			r=qr;
			for(re int i=L[lastblock]; i<=r; ++i)
				++cnt[a[i]];
			ans=find();
//			printf("%d %d %d %d\n",lastblock,L[lastblock],r,ans);
		}
		while(qr<r)
			del(a[r--]);
		int &nowans=answer[q[now].id]=ans;
		for(re int i=L[lastblock]; i<ql; ++i)
		{
			if(!(--cnt[a[i]]))
				nowans=min(nowans,a[i]);
		}
		for(re int i=L[lastblock]; i<ql; ++i)
			++cnt[a[i]];
	}
	for(re int i=1; i<=m; ++i)
		printf("%d\n",answer[i]);


//	cerr<<"time:"<<clock()-start<<"ms"<<endl;


	return 0;
}

