#include <cstdio>
#include <algorithm>
#define ll long long
#define re register
#define mod 1000000
using std::min;

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
const int N=8e4+5;
struct Tree
{
	int size,cnt;
	int val,fa,ch[2];
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
#define val(x) tree[x].val
int cnt,root;
inline bool check(int x)
{
	return rc(fa(x))==x;
}
inline void pushup(int now)
{
	tree[now].size=tree[lc(now)].size+tree[rc(now)].size+tree[now].cnt;
}
inline void rorate(int x)
{
	int y=fa(x),z=fa(y),k=check(x),w=tree[x].ch[k^1];
	tree[y].ch[k]=w,fa(w)=y;
	tree[z].ch[check(y)]=x,fa(x)=z;
	tree[x].ch[k^1]=y,fa(y)=x;
	pushup(y),pushup(x);
}
inline void splay(int x,int tar=0)
{
	while(fa(x)!=tar)
	{
		int y=fa(x),z=fa(y);
		if(z!=tar)
			check(x)==check(y)?rorate(y):rorate(x);
		rorate(x);
	}
	if(!tar)
		root=x;
}
inline void find(int val)
{
	int now=root;
	while(tree[now].ch[val>val(now)]&&val!=val(now))
		now=tree[now].ch[val>val(now)];
	splay(now);
}
inline void insert(int val)
{
	int now=root,las=0;
	while(now&&val(now)!=val)
	{
		las=now;
		now=tree[now].ch[val>val(now)];
	}
	if(now)
		++tree[now].cnt;
	else
	{
		now=++cnt;
		if(las)
			tree[las].ch[val>val(las)]=now;
		fa(now)=las;
		val(now)=val;
		tree[now].size=tree[now].cnt=1;
	}
	splay(now);
}
inline int lower1(int val)
{
	find(val);
	if(tree[root].val<val)
		return root;
	int now=lc(root);
	while(rc(now))
		now=rc(now);
	splay(now);
	return now;
}
inline int upper1(int val)
{
	find(val);
	if(tree[root].val>val)
		return root;
	int now=rc(root);
	while(lc(now))
		now=lc(now);
	splay(now);
	return now;
}
inline void del(int val)
{
	int pre=lower1(val),nxt=upper1(val);
	splay(pre),splay(nxt,pre);
	int now=lc(nxt);
	if(tree[now].cnt>1)
	{
		--tree[now].cnt;
		splay(now);
	}
	else
		lc(nxt)=0;
	pushup(nxt),pushup(root);
}
inline int lower(int val)
{
	find(val);
	if(tree[root].val<=val)
		return root;
	int now=lc(root);
	while(rc(now))
		now=rc(now);
	splay(now);
	return now;
}
inline int upper(int val)
{
	find(val);
	if(tree[root].val>=val)
		return root;
	int now=rc(root);
	while(lc(now))
		now=lc(now);
	splay(now);
	return now;
}
int ans;
inline void query(int val)
{
	int pre=val(lower(val)),nxt=val(upper(val)),now;
	if(nxt-val<val-pre)
		now=nxt;
	else
		now=pre;
	(ans+=abs(now-val))%=mod;
	del(now);
}
const int INF=0x3f3f3f3f;
bool flag;
inline void work()
{
	int opt,val;
	read(opt),read(val);
	if(opt==flag)
		insert(val);
	else
	{
		if(tree[root].size==2)
		{
			flag=opt; 
			insert(val);
		}
		else
			query(val);
	}
}
int main()
{
	insert(INF);
	insert(~INF);
	int n;
	read(n);
	while(n--)
		work();
	printf("%d\n",ans);
	return 0;
}
