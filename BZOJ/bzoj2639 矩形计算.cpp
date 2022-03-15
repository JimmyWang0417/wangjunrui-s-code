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
const int N=205,M=1e6+5;
int n,m,q;
int block;
int belong[M];
struct Query
{
	int x1,y1,x2,y2,id;
	inline bool operator <(const Query &rhs)const
	{
		return belong[x1]==belong[rhs.x1]?
		       (belong[y1]==belong[rhs.y1]?
		        (belong[x2]==belong[rhs.x2]?y2<rhs.y2:x2<rhs.x2):y1<rhs.y1):x1<rhs.x1;
	}
} b[M];

int p[M],tot;
int a[N][N];

int cnt[M];
ll ans,answer[M];
inline void add(int val)
{
	ans-=(ll)cnt[val]*cnt[val];
	++cnt[val];
	ans+=(ll)cnt[val]*cnt[val];
}
inline void del(int val)
{
	ans-=(ll)cnt[val]*cnt[val];
	--cnt[val];
	ans+=(ll)cnt[val]*cnt[val];
}
signed main()
{
//	freopen("vegetable.in","r",stdin);
//	freopen("vegetable.out","w",stdout);
	read(n,m);
	block=(int)sqrt(max(n,m));
	for(int i=1; i<=max(n,m); ++i)
		belong[i]=(i-1)/block+1;

	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
		{
			read(a[i][j]);
			p[++tot]=a[i][j];
		}
	read(q);
	for(int i=1; i<=q; ++i)
	{
		read(b[i].x1,b[i].y1,b[i].x2,b[i].y2);

		if(b[i].x1>b[i].x2)
			swap(b[i].x1,b[i].x2);
		if(b[i].y1>b[i].y2)
			swap(b[i].y1,b[i].y2);

//		printf("%d %d %d %d\n",b[i].x1,b[i].y1,b[i].x2,b[i].y2);

		b[i].id=i;
	}

	sort(p+1,p+1+tot);
	tot=(int)(unique(p+1,p+1+tot)-p-1);
	for(int i=1; i<=n; ++i)
		for(int j=1; j<=m; ++j)
			a[i][j]=(int)(lower_bound(p+1,p+1+tot,a[i][j])-p);

	sort(b+1,b+1+q);
	int x1=1,y1=1,x2=1,y2=1;
	add(a[1][1]);
	for(int kase=1; kase<=q; ++kase)
	{
		while(x2<b[kase].x2)
		{
			++x2;
			for(int i=y1; i<=y2; ++i)
				add(a[x2][i]);
		}
		while(y2<b[kase].y2)
		{
			++y2;
			for(int i=x1; i<=x2; ++i)
				add(a[i][y2]);
		}
		while(x1>b[kase].x1)
		{
			--x1;
			for(int i=y1; i<=y2; ++i)
				add(a[x1][i]);
		}
		while(y1>b[kase].y1)
		{
			--y1;
			for(int i=x1; i<=x2; ++i)
				add(a[i][y1]);
		}

		while(x2>b[kase].x2)
		{
			for(int i=y1; i<=y2; ++i)
				del(a[x2][i]);
			--x2;
		}
		while(y2>b[kase].y2)
		{
			for(int i=x1; i<=x2; ++i)
				del(a[i][y2]);
			--y2;
		}
		while(x1<b[kase].x1)
		{
			for(int i=y1; i<=y2; ++i)
				del(a[x1][i]);
			++x1;
		}
		while(y1<b[kase].y1)
		{
			for(int i=x1; i<=x2; ++i)
				del(a[i][y1]);
			++y1;
		}
		answer[b[kase].id]=ans;
	}
	for(int i=1; i<=q; ++i)
		printf("%lld\n",answer[i]);
	return 0;
}


