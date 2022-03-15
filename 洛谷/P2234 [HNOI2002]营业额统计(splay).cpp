#include <cstdio>
#include <algorithm>
#define ll long long
#define re register
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
const int N=1e5+5;
struct Tree
{
	int cnt,size;
	int val,ch[2],fa;
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
#define val(x) tree[x].val
int root,cnt;
inline bool check(int x)
{
	return rc(fa(x))==x;
}
inline void pushup(int now)
{
	tree[now].size=tree[lc(now)].size+tree[rc(now)].size+1;
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
inline void insert(int val)
{
	int now=root,las=0;
	while(now&&val!=val(now))
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
			tree[las].ch[val>tree[las].val]=now;
		fa(now)=las;
		val(now)=val;
		tree[now].cnt=tree[now].size=1;
	}
	splay(now);
}
inline void find(int val)
{
	int now=root;
	while(tree[now].ch[val>val(now)]&&val(now)!=val)
		now=tree[now].ch[val>val(now)];
	splay(now);
}
inline int lower(int val)
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
inline int upper(int val)
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
const int INTMAX=0x3f3f3f3f;
int n,ans;
int main()
{
	insert(INTMAX);
	insert(~INTMAX);
	int val;
	read(n);
	read(val);
	insert(val);
	ans=val;
	while(--n)
	{
		read(val);
		insert(val);
		if(tree[root].cnt>1)
			continue;
		ans+=min(val-val(lower(val)),val(upper(val))-val);
	}
	printf("%d\n",ans);
	return 0;
}
