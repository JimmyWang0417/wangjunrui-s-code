#include <map>
#include <cstdio>
#include <vector>
#include <algorithm>
#define re register
#define ll long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
using namespace std;
namespace IO
{
	const int SIZE=30*1e5+30*1e6;
	char ibuf[SIZE],*iS,*iT;
#define gc() (char)(iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT?EOF:*iS++):*iS++)
	template<typename T>
	inline void read(T & x)
	{
		x=0;
		bool b=false;
		char ch=gc();
		while((ch<'0'||ch>'9')&&ch^'-')
			ch=gc();
		if(ch=='-')
		{
			b=true;
			ch=gc();
		}
		while(ch>='0'&&ch<='9')
		{
			x=(x<<1)+(x<<3)+(ch^'0');
			ch=gc();
		}
		if(b)
			x=~x+1;
		return;
	}
	template<typename T,typename ...T1>
	inline void read(T&x,T1&...x1)
	{
		read(x);
		read(x1...);
	}
#undef gc
	char Out[(int)1e5*10],*fe=Out,ch[25];
	int num=0;
	template<typename T>
	inline void write(T x)
	{
		if(!x)
			*fe++='0';
		if(x<0)
		{
			*fe++='-';
			x=-x;
		}
		while(x)
		{
			ch[++num]=(char)(x%10+'0');
			x/=10;
		}
		while(num)
			*fe++=ch[num--];
		*fe++='\n';
	}
	inline void flush()
	{
		fwrite(Out,1,fe-Out,stdout);
		fe=Out;
	}
}
const int N=1e3+5,M=1e5+5;
struct node
{
	int u,v,w;
} a[M];
struct Tree
{
	int ch[2],fa;
	int size;
	int id,max;
	bool reverse;
} tree[N+M];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
#define rev(x) tree[x].reverse
inline bool check(int x)
{
	return rc(fa(x))==x;
}
inline bool nroot(int x)
{
	return lc(fa(x))==x||rc(fa(x))==x;
}
inline int getmax(int x,int y)
{
	return a[x].w>a[y].w?x:y;
}
inline void pushup(int x)
{
	tree[x].size=tree[lc(x)].size+tree[rc(x)].size+1;
	tree[x].max=getmax(tree[x].id,getmax(tree[lc(x)].max,tree[rc(x)].max));
}
inline void pushdown(int x)
{
	if(rev(x))
	{
		swap(lc(x),rc(x));
		if(lc(x))
			rev(lc(x))^=1;
		if(rc(x))
			rev(rc(x))^=1;
		rev(x)=false;
	}
}
inline void rotate(int x)
{
	int y=fa(x),z=fa(y),k=check(x),w=tree[x].ch[k^1];
	if(nroot(y))
		tree[z].ch[check(y)]=x;
	tree[y].ch[k]=w;
	tree[x].ch[k^1]=y;
	if(w)
		fa(w)=y;
	fa(y)=x;
	fa(x)=z;
	pushup(y),pushup(x);
}
int st[N+M];
inline void splay(int x)
{
	int top;
	st[top=1]=x;
	for(re int y=x; nroot(y); y=fa(y))
		st[++top]=fa(y);
	while(top)
		pushdown(st[top--]);
	while(nroot(x))
	{
		if(nroot(fa(x)))
			rotate(check(x)==check(fa(x))?fa(x):x);
		rotate(x);
	}
}
inline void access(int x)
{
	for(re int y=0; x; x=fa(y=x))
	{
		splay(x);
		rc(x)=y;
		pushup(x);
	}
}
inline void makeroot(int x)
{
	access(x);
	splay(x);
	rev(x)^=1;
}
inline int findroot(int x)
{
	access(x);
	splay(x);
	while(pushdown(x),lc(x))
		x=lc(x);
	splay(x);
	return x;
}
inline void split(int x,int y)
{
	makeroot(x);
	access(y);
	splay(y);
}
inline void link(int x,int y)
{
	makeroot(x);
	fa(x)=y;
}
inline void cut(int x,int y)
{
	split(x,y);
	lc(y)=fa(x)=0;
	pushup(y);
}
int n,m,q;
inline void cut(int id)
{
	int &x=a[id].u,&y=a[id].v,now=id+n;
	split(x,y);
	splay(now);
	lc(now)=rc(now)=fa(x)=fa(y)=0;
}
struct Query
{
	int opt,x,y;
} Q[M];
int ans[M];
int fa[N];
inline int find(int x)
{
	if(!fa[x])
		return x;
	return fa[x]=find(fa[x]);
}
inline void unionn(int x,int y)
{
	int fx=find(x),fy=find(y);
	if(fx==fy)
		return;
	fa[fx]=fy;
}
bool vis[M];
int pos[M];
using IO::read;
using IO::write;
signed main()
{
	map<pair<int,int>,int>mp;
	read(n,m,q);
	rep(i,1,m)
	{
		int &u=a[i].u,&v=a[i].v,&w=a[i].w;
		read(u,v,w);
		tree[i+n].id=i;
		if(u>v)
			swap(u,v);
		mp[make_pair(u,v)]=i;
	}
	rep(i,1,n+m)pushup(i);
	rep(i,1,q)
	{
		int &opt=Q[i].opt,&x=Q[i].x,&y=Q[i].y;
		read(opt,x,y);
		if(opt==2)
		{
			if(x>y)
				swap(x,y);
			vis[pos[i]=mp[make_pair(x,y)]]=true;
		}
	}
	rep(i,1,m)
	{
		int &u=a[i].u,&v=a[i].v,&w=a[i].w;
		if(vis[i])
			continue;
		if(find(u)==find(v))
		{
			split(u,v);
			int id=tree[v].max;
			if(a[id].w>w)
			{
				cut(id);
				link(u,i+n),link(i+n,v);
			}
		}
		else
		{
			link(u,i+n),link(i+n,v);
			unionn(u,v);
		}

	}
	int top=0;
	per(i,q,1)
	{
		int &opt=Q[i].opt,&x=Q[i].x,&y=Q[i].y;
		if(opt==1)
		{
			split(x,y);
			ans[++top]=a[tree[y].max].w;
		}
		else if(opt==2)
		{
			int nowid=pos[i];
			makeroot(x);
			if(x==findroot(y))
			{
				split(x,y);
				int id=tree[y].max;
				if(a[id].w>a[nowid].w)
				{
					cut(id);
					link(x,nowid+n),link(nowid+n,y);
				}
			}
			else
			{
				link(x,nowid+n),link(nowid+n,y);
				unionn(x,y);
			}
		}
	}
	while(top)
		write(ans[top--]);
	IO::flush();
	return 0;
}
