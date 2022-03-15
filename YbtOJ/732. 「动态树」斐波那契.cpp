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
const int N=1e5+5,mod=998244353,inv2=(mod+1)/2;
inline void add(int &x,int y)
{
	x+=y;
	if(x>=mod)
		x-=mod;
}
inline int times(int x,int y)
{
	return (int)((ll)x*y%mod);
}
inline int quickpow(ll aaa,int bbb)
{
	ll res=1;
	while(bbb)
	{
		if(bbb&1)
			(res*=aaa)%=mod;
		(aaa*=aaa)%=mod;
		bbb>>=1;
	}
	return (int)res;
}
std::unordered_map<int, int> Result_Of_Inv;
inline int inv(int x) {
    if (Result_Of_Inv.count(x))
        return Result_Of_Inv[x];
    else
        return Result_Of_Inv[x] = quickpow(x, mod - 2);
}
struct newnumber
{
	int a,b;
	newnumber(int _a=0,int _b=0):a(_a),b(_b) {};
	inline newnumber operator + (const newnumber &rhs)const
	{
		newnumber ans=(*this);
		add(ans.a,rhs.a);
		add(ans.b,rhs.b);
		return ans;
	}
	inline newnumber operator - (const newnumber &rhs)const
	{
		newnumber ans=(*this);
		add(ans.a,mod-rhs.a);
		add(ans.b,mod-rhs.b);
		return ans;
	}
	inline newnumber operator * (const newnumber &rhs)const
	{
		return newnumber((int)(((ll)a*rhs.a+(ll)5*b*rhs.b)%mod),(int)(((ll)a*rhs.b+(ll)b*rhs.a)%mod));
	}
	inline newnumber operator / (const newnumber &rhs)const
	{
		int tx,ty,tz;
		tx=(int)(((ll)a*rhs.a-(ll)5*b*rhs.b)%mod);
		add(tx,mod);

		ty=(int)(((ll)b*rhs.a-(ll)a*rhs.b)%mod);
		add(ty,mod);

		tz=(int)(((ll)rhs.a*rhs.a-(ll)5*rhs.b*rhs.b)%mod);
		add(tz,mod);
		tz=inv(tz);

		return newnumber(times(tx,tz),times(ty,tz));
	}
	inline newnumber operator ^(int power)const
	{
		newnumber res(1,0),ab=(*this);
		while(power)
		{
			if(power&1)
				res=res*ab;
			ab=ab*ab;
			power>>=1;
		}
		return res;
	}
	inline bool operator !=(const newnumber &rhs)const
	{
		return a!=rhs.a||b!=rhs.b;
	}
	inline void print()
	{
		printf("(%d,%d)",a,b);
	}
};
struct Tree
{
	int ch[2];
	int size;
	int fa;
	bool rev;

	newnumber taga,tagb;
	newnumber ansa,ansb;
	newnumber prea,preb;
	newnumber sufa,sufb;
	newnumber proa,prob;
	newnumber vala,valb;
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
inline bool check(int x)
{
	return rc(fa(x))==x;
}
inline bool nroot(int x)
{
	return lc(fa(x))==x||rc(fa(x))==x;
}
const newnumber one(1,0),zero(0,0),alpha(inv2,inv2),beta(inv2,mod-inv2);
inline void pushup(int x)
{
	tree[x].size=tree[lc(x)].size+tree[rc(x)].size+1;

	tree[x].proa=tree[lc(x)].proa*tree[x].vala*tree[rc(x)].proa;
	tree[x].prob=tree[lc(x)].prob*tree[x].valb*tree[rc(x)].prob;

	tree[x].prea=tree[lc(x)].prea+(tree[rc(x)].prea+one)*tree[x].vala*tree[lc(x)].proa;
	tree[x].preb=tree[lc(x)].preb+(tree[rc(x)].preb+one)*tree[x].valb*tree[lc(x)].prob;

	tree[x].sufa=tree[rc(x)].sufa+(tree[lc(x)].sufa+one)*tree[x].vala*tree[rc(x)].proa;
	tree[x].sufb=tree[rc(x)].sufb+(tree[lc(x)].sufb+one)*tree[x].valb*tree[rc(x)].prob;

	tree[x].ansa=tree[lc(x)].ansa+tree[rc(x)].ansa+(tree[rc(x)].prea+one)*tree[x].vala*(tree[lc(x)].sufa+one);
	tree[x].ansb=tree[lc(x)].ansb+tree[rc(x)].ansb+(tree[rc(x)].preb+one)*tree[x].valb*(tree[lc(x)].sufb+one);

}
inline void addrev(int x)
{
	if(!x)
		return;
	tree[x].rev^=1;
	swap(tree[x].prea,tree[x].sufa);
	swap(tree[x].preb,tree[x].sufb);
}
inline void addtag(int x,newnumber taga,newnumber tagb)
{
	if(!x)
		return;
	tree[x].taga=tree[x].vala=taga;
	tree[x].tagb=tree[x].valb=tagb;

	newnumber tx,ty;

	tree[x].proa=taga^tree[x].size;
	tx=tree[x].proa*taga;
	ty=one/(taga-one);
	tree[x].sufa=tree[x].prea=(tx-taga)*ty;
	tree[x].ansa=tree[x].prea*newnumber(tree[x].size+1,0)-(newnumber(tree[x].size,0)*tx-tree[x].prea)*ty;

	tree[x].prob=tagb^tree[x].size;
	tx=tree[x].prob*tagb;
	ty=one/(tagb-one);
	tree[x].sufb=tree[x].preb=(tx-tagb)*ty;
	tree[x].ansb=tree[x].preb*newnumber(tree[x].size+1,0)-(newnumber(tree[x].size,0)*tx-tree[x].preb)*ty;
}
inline void pushdown(int x)
{
	if(tree[x].rev)
	{
		swap(lc(x),rc(x));
		addrev(lc(x));
		addrev(rc(x));
		tree[x].rev=false;
	}
	if(tree[x].taga!=zero)
	{
		addtag(lc(x),tree[x].taga,tree[x].tagb);
		addtag(rc(x),tree[x].taga,tree[x].tagb);
		tree[x].taga=tree[x].tagb=zero;
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
int st[N];
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
	addrev(x);
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
inline void update(int u,int v,newnumber taga,newnumber tagb)
{
	split(u,v);
	addtag(v,taga,tagb);
}
int father[N];
int n,m;
signed main()
{
	freopen("fibonacci.in","r",stdin);
	freopen("fibonacci.out","w",stdout);
	tree[0].proa=tree[0].prob=one;
	read(n,m);
	for(int i=1; i<=n; ++i)
	{
		int x;
		read(x);
		tree[i].vala=alpha^x;
		tree[i].valb=beta^x;
		pushup(i);
	}
	for(int i=2; i<=n; ++i)
	{
		read(father[i]);
		fa(i)=father[i];
	}
	for(int i=1; i<=m; ++i)
	{
		int opt,u,v,w;
		read(opt);
		if(opt==1)
		{
			read(u,v);
			cut(father[u],u);
			link(father[u]=v,u);
		}
		else if(opt==2)
		{
			read(u,v,w);
			update(u,v,alpha^w,beta^w);
		}
		else if(opt==3)
		{
			read(u);
			access(u);
			splay(u);
			printf("%d\n",(tree[u].vala-tree[u].valb).b);
		}
		else
		{
			read(u,v);
			split(u,v);
			printf("%d\n",(tree[v].ansa-tree[v].ansb).b);
		}
	}
	return 0;
}

