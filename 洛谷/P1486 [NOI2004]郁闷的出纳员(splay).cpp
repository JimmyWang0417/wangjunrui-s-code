#include <cstdio>
#define ll long long
#define re register

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
int cnt,root;
struct Tree
{
	int size,cnt;
	int val,ch[2],fa;
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
#define val(x) tree[x].val
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
		{
			if(check(x)==check(y))
				rorate(y);
			else
				rorate(x);
		}
		rorate(x);
	}
	if(!tar)
		root=x;
}
inline void find(int val)
{
	int now=root;
	while(tree[now].ch[val>val(now)]&&tree[now].val!=val)
		now=tree[now].ch[val>val(now)];
	splay(now);
}
inline void insert(int val)
{
	int now=root,las=0;
	while(now&&tree[now].val!=val)
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
		lc(now)=rc(now)=0;
		val(now)=val;
		fa(now)=las;
		tree[now].size=tree[now].cnt=1;
	}
	splay(now);
}
int minn,sum,ans;
inline void del()
{
	int val=minn-sum;
	find(val);
	if(val(root)<val)
	{
		ans+=tree[lc(root)].size+tree[root].cnt;
		root=rc(root);
		rc(fa(root))=0;
		fa(root)=0;
	}
	else
	{
		ans+=tree[lc(root)].size;
		lc(root)=0;
		pushup(root);
	}
}
inline int k_th(int rk)
{
	int now=root;
	while(1)
	{
		if(rk<=tree[lc(now)].size)
			now=lc(now);
		else if(rk>tree[lc(now)].size+tree[now].cnt)
		{
			rk-=tree[lc(now)].size+tree[now].cnt;
			now=rc(now);
		}
		else
		{
			splay(now);
			return now;
		}
	}
}
int n;
int main()
{
	read(n),read(minn);
	while(n--)
	{
		char opt[4];
		int k;
		scanf("%s",opt),read(k);
		if(opt[0]=='I')
		{
			if(k<minn)
				continue;
			insert(k-sum);
		}
		else if(opt[0]=='A')
			sum+=k;
		else if(opt[0]=='S')
		{
			sum-=k;
			del();
		}
		else if(opt[0]=='F')
		{
			if(k>tree[root].size)
				printf("-1\n");
			else
				printf("%d\n",val(k_th(tree[root].size-k+1))+sum);
		}
//		print(root);
	}
	printf("%d\n",ans);
	return 0;
}
