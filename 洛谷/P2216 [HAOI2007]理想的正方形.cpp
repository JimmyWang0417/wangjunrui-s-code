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
const int N=1e3+5;
struct queuemax
{
	int head,tail,limit,q[N],valq[N];
	inline void init(int _limit)
	{
		head=1,tail=0;
		limit=_limit;
	}
	inline void insert(int pos,int val)
	{
		while(head<=tail&&q[head]<pos-limit+1)
			++head;

		while(head<=tail&&valq[tail]<val)
			--tail;

		++tail;
		q[tail]=pos;
		valq[tail]=val;
	}
	inline int top()
	{
		return valq[head];
	}
} qmax1[N],qmax;
struct queuemin
{

	int head,tail,limit,q[N],valq[N];
	inline void init(int _limit)
	{
		head=1,tail=0;
		limit=_limit;
	}
	inline void insert(int pos,int val)
	{
		while(head<=tail&&q[head]<pos-limit+1)
			++head;

		while(head<=tail&&valq[tail]>val)
			--tail;

		++tail;
		q[tail]=pos;
		valq[tail]=val;
	}
	inline int top()
	{
		return valq[head];
	}
} qmin1[N],qmin;
int a,b,n,h[N][N];
signed main()
{
	read(a,b,n);
	for(int i=1; i<=a; ++i)
		for(int j=1; j<=b; ++j)
			read(h[i][j]);
	for(int j=1; j<=b; ++j)
	{
		qmax1[j].init(n),qmin1[j].init(n);
		for(int i=1; i<n; ++i)
		{
			qmax1[j].insert(i,h[i][j]);
			qmin1[j].insert(i,h[i][j]);
		}
	}
	int ans=0x7fffffff;
	for(int i=n; i<=a; ++i)
	{
		for(int j=1;j<=b;++j)
		{
			qmax1[j].insert(i,h[i][j]);
			qmin1[j].insert(i,h[i][j]);
		}
		qmax.init(n),qmin.init(n);
		for(int j=1;j<n;++j)
		{
			qmax.insert(j,qmax1[j].top());
			qmin.insert(j,qmin1[j].top());
		}
		for(int j=n;j<=b;++j)
		{
			qmax.insert(j,qmax1[j].top());
			qmin.insert(j,qmin1[j].top());
			ans=min(ans,qmax.top()-qmin.top());
		}
	}
	printf("%d\n",ans);
	return 0;
}


