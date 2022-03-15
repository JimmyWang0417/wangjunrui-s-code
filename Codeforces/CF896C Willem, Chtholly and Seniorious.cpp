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
const int N=1e5+5,mod=1e9+7;
inline ll quickpow(ll a,int b,int p)
{
	a%=p;
	ll res=1;
	while(b)
	{
		if(b&1)
			res=res*a%p;
		a=a*a%p;
		b>>=1;
	}
	return res;
}
int n,m,vmax;
ll seed;
inline int rnd()
{
	int ret=(int)seed;
	seed=(seed*7+13)%mod;
	return ret;
}
int a[N];
struct node
{
	int l,r;
	mutable ll v;
	node(int _l,int _r,ll _v):l(_l),r(_r),v(_v) {}
	inline bool operator <(const node &rhs)const
	{
		return l<rhs.l;
	}
};
set<node>se;
inline set<node>::iterator split(int x)
{
	if(x>n)
		return se.end();
	set<node>::iterator it=--se.upper_bound(node(x,0,0));
	if(it->l==x)
		return it;
	int l=it->l,r=it->r;
	ll v=it->v;
	se.erase(it);
	se.insert(node(l,x-1,v));
	return se.insert(node(x,r,v)).first;
}
inline void assign(int l,int r,int v)
{
	set<node>::iterator itr=split(r+1),itl=split(l);
	se.erase(itl,itr);
	se.insert(node(l,r,v));
}
inline void update(int l,int r,int v)
{
	set<node>::iterator itr=split(r+1),itl=split(l);
	for(set<node>::iterator it=itl; it!=itr; ++it)
		it->v+=v;
}
pair<ll,int> p[N];
int tot;
inline ll querykth(int l,int r,int x)
{
	set<node>::iterator itr=split(r+1),itl=split(l);
	tot=0;
	for(set<node>::iterator it=itl; it!=itr; ++it)
		p[++tot]=make_pair(it->v,it->r-it->l+1);
	sort(p+1,p+1+tot);
	for(int i=1; i<=tot; ++i)
	{
		x-=p[i].second;
		if(x<=0)
			return p[i].first;
	}
	return 1145141919810258;
}
inline ll query(int l,int r,int y,int x)//因为后面的值所调用的函数先调用 
{
	ll res=0;
	set<node>::iterator itr=split(r+1),itl=split(l);
	for(set<node>::iterator it=itl; it!=itr; ++it)
		(res+=(it->r-it->l+1)*quickpow(it->v,x,y)%y)%=y;
	return res;

}
inline void print()
{
	for(auto v:se)
		printf("%d %d %lld\n",v.l,v.r,v.v);
	putchar('\n');

}
signed main()
{
	read(n,m,seed,vmax);
	for(int i=1; i<=n; ++i)
	{
		a[i]=rnd()%vmax+1;
		se.insert(node(i,i,a[i]));
	}
	for(int i=1; i<=m; ++i)
	{
		int opt=rnd()%4+1,l=rnd()%n+1,r=rnd()%n+1;
		if(l>r)
			swap(l,r);
		if(opt==1)
			update(l,r,rnd()%vmax+1);
		else if(opt==2)
			assign(l,r,rnd()%vmax+1);
		else if(opt==3)
			printf("%lld\n",querykth(l,r,(rnd()%(r-l+1))+1));
		else
			printf("%lld\n",query(l,r,rnd()%vmax+1,rnd()%vmax+1));
	}
	return 0;
}


