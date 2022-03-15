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
const int N=2e5+5;
struct Circle
{
	int x,y,r;
} a[N];
int line;
struct Queue
{
	int x,opt,id;
	Queue(int _x=0,int _opt=0,int _id=0):x(_x),opt(_opt),id(_id) {}
	inline bool operator <(const Queue&rhs)const
	{
		return x<rhs.x;
	}
} q[N*2];
struct node
{
	int opt,id;
	node(int _opt=0,int _id=0):opt(_opt),id(_id) {}
	inline double calc()const
	{
		return a[id].y+opt*sqrt((ll)a[id].r*a[id].r-(ll)(a[id].x-line)*(a[id].x-line));
	}
	inline bool operator <(const node&rhs)const
	{
		return calc()==rhs.calc()?opt<rhs.opt:calc()<rhs.calc();
	}
};
int n;
int tag[N];
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
	{
		read(a[i].x,a[i].y,a[i].r);
		q[i]=Queue(a[i].x-a[i].r,1,i);
		q[i+n]=Queue(a[i].x+a[i].r,-1,i);
	}
	int m=n*2;
	sort(q+1,q+1+m);
	set<node>s;
	for(int i=1; i<=m; ++i)
	{
		line=q[i].x;
		if(q[i].opt==1)
		{
			set<node>::iterator it=s.upper_bound(node(q[i].opt,q[i].id));
			if(it==s.end())
				tag[q[i].id]=1;
			else
			{
				if((*it).opt==1)
					tag[q[i].id]=-tag[(*it).id];
				else
					tag[q[i].id]=tag[(*it).id];
			}
			s.insert(node(1,q[i].id));
			s.insert(node(-1,q[i].id));
		}
		else
		{
			s.erase(node(1,q[i].id));
			s.erase(node(-1,q[i].id));
		}
	}
	ll ans=0;
	for(int i=1; i<=n; ++i)
		ans+=tag[i]*(ll)a[i].r*a[i].r;
	printf("%lld\n",ans);
	return 0;
}


