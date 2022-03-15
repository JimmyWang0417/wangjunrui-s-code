#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include <bits/stdc++.h>
#define int ll
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
const int N=5e5+5;
const int mod=1e9+7;
const int INF=0x3f3f3f3f;
struct Tree
{
	int l,r;
	int size;

	int key;

	int val;
	int max,cnt;

	int lcnt,rcnt;

	int lans,rans;

	int begin,end;

	bool rev;
} tree[N];
#define lc(x) tree[x].l
#define rc(x) tree[x].r
int cnt,root;
inline int newnode(int val)
{
	int now=++cnt;

	lc(now)=rc(now)=0;
	tree[now].size=1;

	tree[now].key=rand();

	tree[now].max=tree[now].val=val;
	tree[now].cnt=1;

	tree[now].lcnt=tree[now].rcnt=tree[now].lans=tree[now].rans=0;

	tree[now].begin=tree[now].end=val;

	tree[now].rev=false;
	return now;
}
inline void rev(int now)
{
	swap(lc(now),rc(now));
	swap(tree[now].lcnt,tree[now].rcnt);
	swap(tree[now].lans,tree[now].rans);
	swap(tree[now].begin,tree[now].end);
	tree[now].rev^=1;
}
inline void pushdown(int now)
{
	if(tree[now].rev)
	{
		if(lc(now))
			rev(lc(now));
		if(rc(now))
			rev(rc(now));
		tree[now].rev=false;
	}
}
inline void pushup(int now)
{
	tree[now].size=tree[lc(now)].size+tree[rc(now)].size+1;
	tree[now].max=tree[now].val;
	tree[now].cnt=1;

	tree[now].begin=tree[now].end=tree[now].val;

	tree[now].lcnt=tree[now].rcnt=tree[now].lans=tree[now].rans=0;

	if(lc(now))
	{
		tree[now].begin=tree[lc(now)].begin;
		if(tree[now].max<tree[lc(now)].max)
		{
			tree[now].max=tree[lc(now)].max;
			tree[now].cnt=tree[lc(now)].cnt;
		}
		else if(tree[now].max==tree[lc(now)].max)tree[now].cnt+=tree[lc(now)].cnt;

		tree[now].lans+=tree[lc(now)].lans+(tree[rc(now)].size+1)*tree[lc(now)].lcnt;
		tree[now].rans+=tree[lc(now)].rans;
		tree[now].lcnt+=tree[lc(now)].lcnt;
		tree[now].rcnt+=tree[lc(now)].rcnt;

		if(tree[lc(now)].end>tree[now].val)
		{
			tree[now].lans+=tree[rc(now)].size+1;
			++tree[now].lcnt;
		}
		else if(tree[lc(now)].end<tree[now].val)
		{
			tree[now].rans+=tree[lc(now)].size;
			++tree[now].rcnt;
		}
	}
	if(rc(now))
	{
		tree[now].end=tree[rc(now)].end;
		if(tree[now].max<tree[rc(now)].max)
		{
			tree[now].max=tree[rc(now)].max;
			tree[now].cnt=tree[rc(now)].cnt;
		}
		else if(tree[now].max==tree[rc(now)].max)tree[now].cnt+=tree[rc(now)].cnt;

		tree[now].lans+=tree[rc(now)].lans;
		tree[now].rans+=tree[rc(now)].rans+(tree[lc(now)].size+1)*tree[rc(now)].rcnt;
		tree[now].lcnt+=tree[rc(now)].lcnt;
		tree[now].rcnt+=tree[rc(now)].rcnt;
		if(tree[now].val>tree[rc(now)].begin)
		{
			tree[now].lans+=tree[rc(now)].size;
			++tree[now].lcnt;
		}
		else if(tree[now].val<tree[rc(now)].begin)
		{
			tree[now].rans+=tree[lc(now)].size+1;
			++tree[now].rcnt;
		}
	}
}
inline void split(int now,int size,int &x,int &y)
{
	if(!now)
		x=y=0;
	else
	{
		pushdown(now);
		if(tree[lc(now)].size<size)
		{
			x=now;
			split(rc(now),size-tree[lc(now)].size-1,rc(now),y);
		}
		else
		{
			y=now;
			split(lc(now),size,x,lc(now));
		}
		pushup(now);
	}
}
inline int merge(int x,int y)
{
	if(!x||!y)
		return x|y;
	if(tree[x].key>tree[y].key)
	{
		pushdown(x);
		rc(x)=merge(rc(x),y);
		pushup(x);
		return x;
	}
	else
	{
		pushdown(y);
		lc(y)=merge(x,lc(y));
		pushup(y);
		return y;
	}
}
inline int find(int rt)
{
//	printf("%d %d %d\n",tree[lc(rt)].max,tree[rc(rt)].max,tree[rt].cnt);
	int val=tree[rt].max,nowcnt=(tree[rt].cnt+1)/2,pos=0;
//	printf("%d %d\n",val,nowcnt);
	int now=rt;
	while(now)
	{
//		printf("%d %d %d\n",now,lc(now),rc(now));
		pushdown(now);
		int sum=0;
		if(val==tree[lc(now)].max)
			sum+=tree[lc(now)].cnt;
		if(tree[now].val==val)
		{
			if(nowcnt==sum+1)
				return pos+tree[lc(now)].size+1;
			else
				++sum;
		}

		if(nowcnt>sum)
		{
			nowcnt-=sum;
			pos+=tree[lc(now)].size+1;
			now=rc(now);
		}
		else
			now=lc(now);
	}
	return pos+1;
}
//inline void print(int now)
//{
//	pushdown(now);
//	if(lc(now))
//		print(lc(now));
//	printf("rt=%lld lc=%lld rc=%lld size=%lld val=%lld begin=%lld end=%lld\n",now,lc(now),rc(now),tree[now].size,tree[now].val,tree[now].begin,tree[now].end);
//	if(rc(now))
//		print(rc(now));
//}
int n;
inline void work()
{
	char opt[4];
	scanf("%s",opt);
	if(opt[0]=='I')
	{
		int h,pos;
		read(h,pos);
		int x,y;
		split(root,pos,x,y);
		root=merge(x,merge(newnode(h),y));
	}
	else if(opt[0]=='R')
	{
		int l,r;
		read(l,r);
		int x,y,z;
		split(root,l-1,x,y);
		split(y,r-l+1,y,z);
		rev(y);
		root=merge(x,merge(y,z));
	}
	else if(opt[0]=='Q')
	{
		int l,r;
		read(l,r);
		int x,y,z;
		split(root,l-1,x,y);
		split(y,r-l+1,y,z);
//		printf("nmsl\n");
		int pos=find(y);
//		printf("%d:\n",y);
//		print(y);
//		printf("%d\n",pos);
		int a,b,c;
		split(y,pos-1,a,b);
		split(b,1,b,c);
//		printf("a:\n");
//		print(a);
//		printf("c:\n");
//		print(c);
//		printf("%d %d %d %d\n",tree[a].lans,tree[a].lcnt,tree[c].rans,tree[c].rcnt);
		int ans=(tree[a].lans+tree[a].lcnt)+(tree[c].rans+tree[c].rcnt);
		y=merge(a,merge(b,c));
		root=merge(x,merge(y,z));
		printf("%lld\n",ans%mod);
	}
//	printf("root:\n");
//	print(root);
}
signed main()
{
	srand(1919810);
	freopen("train.in","r",stdin),freopen("train.out","w",stdout);
	tree[0].val=INF;
	tree[0].max=-INF;
	read(n);
//	for(int i=1; i<=n; ++i)
//		read(a[i]);
//	a[0]=a[n+1]=INF;
//	for(int i=1; i<=n; ++i)
//	{
//		int now=newnode(a[i]);
//		if(a[i]>a[i+1])
//		{
//			tree[now].lcnt=tree[now].nowlcnt=1;
//			tree[now].lans=tree[now].nowlans=i;
//		}
//		if(a[i]>a[i-1])
//		{
//			tree[now].rcnt=tree[now].nowrcnt=1;
//			tree[now].rans=tree[now].nowrans=i;
//		}
//		root=merge(root,now);
//	}
	while(n--)
		work();
	return 0;
}
/*
 * ©°©¤©¤©¤©´   ©°©¤©¤©¤©Ð©¤©¤©¤©Ð©¤©¤©¤©Ð©¤©¤©¤©´ ©°©¤©¤©¤©Ð©¤©¤©¤©Ð©¤©¤©¤©Ð©¤©¤©¤©´ ©°©¤©¤©¤©Ð©¤©¤©¤©Ð©¤©¤©¤©Ð©¤©¤©¤©´ ©°©¤©¤©¤©Ð©¤©¤©¤©Ð©¤©¤©¤©´
 * ©¦Esc©¦   ©¦ F1©¦ F2©¦ F3©¦ F4©¦ ©¦ F5©¦ F6©¦ F7©¦ F8©¦ ©¦ F9©¦F10©¦F11©¦F12©¦ ©¦P/S©¦S L©¦P/B©¦  ©°©´    ©°©´    ©°©´
 * ©¸©¤©¤©¤©¼   ©¸©¤©¤©¤©Ø©¤©¤©¤©Ø©¤©¤©¤©Ø©¤©¤©¤©¼ ©¸©¤©¤©¤©Ø©¤©¤©¤©Ø©¤©¤©¤©Ø©¤©¤©¤©¼ ©¸©¤©¤©¤©Ø©¤©¤©¤©Ø©¤©¤©¤©Ø©¤©¤©¤©¼ ©¸©¤©¤©¤©Ø©¤©¤©¤©Ø©¤©¤©¤©¼  ©¸©¼    ©¸©¼    ©¸©¼
 * ©°©¤©¤©¤©Ð©¤©¤©¤©Ð©¤©¤©¤©Ð©¤©¤©¤©Ð©¤©¤©¤©Ð©¤©¤©¤©Ð©¤©¤©¤©Ð©¤©¤©¤©Ð©¤©¤©¤©Ð©¤©¤©¤©Ð©¤©¤©¤©Ð©¤©¤©¤©Ð©¤©¤©¤©Ð©¤©¤©¤©¤©¤©¤©¤©´ ©°©¤©¤©¤©Ð©¤©¤©¤©Ð©¤©¤©¤©´ ©°©¤©¤©¤©Ð©¤©¤©¤©Ð©¤©¤©¤©Ð©¤©¤©¤©´
 * ©¦~ `©¦! 1©¦@ 2©¦# 3©¦$ 4©¦% 5©¦^ 6©¦& 7©¦* 8©¦( 9©¦) 0©¦_ -©¦+ =©¦ BacSp ©¦ ©¦Ins©¦Hom©¦PUp©¦ ©¦Num©¦ / ©¦ * ©¦ - ©¦
 * ©À©¤©¤©¤©Ø©¤©Ð©¤©Ø©¤©Ð©¤©Ø©¤©Ð©¤©Ø©¤©Ð©¤©Ø©¤©Ð©¤©Ø©¤©Ð©¤©Ø©¤©Ð©¤©Ø©¤©Ð©¤©Ø©¤©Ð©¤©Ø©¤©Ð©¤©Ø©¤©Ð©¤©Ø©¤©Ð©¤©Ø©¤©Ð©¤©¤©¤©¤©¤©È ©À©¤©¤©¤©à©¤©¤©¤©à©¤©¤©¤©È ©À©¤©¤©¤©à©¤©¤©¤©à©¤©¤©¤©à©¤©¤©¤©È
 * ©¦ Tab ©¦ Q ©¦ W ©¦ E ©¦ R ©¦ T ©¦ Y ©¦ U ©¦ I ©¦ O ©¦ P ©¦{ [©¦} ]©¦ | \ ©¦ ©¦Del©¦End©¦PDn©¦ ©¦ 7 ©¦ 8 ©¦ 9 ©¦   ©¦
 * ©À©¤©¤©¤©¤©¤©Ø©Ð©¤©¤©Ø©Ð©¤©¤©Ø©Ð©¤©¤©Ø©Ð©¤©¤©Ø©Ð©¤©¤©Ø©Ð©¤©¤©Ø©Ð©¤©¤©Ø©Ð©¤©¤©Ø©Ð©¤©¤©Ø©Ð©¤©¤©Ø©Ð©¤©¤©Ø©Ð©¤©¤©Ø©¤©¤©¤©¤©¤©È ©¸©¤©¤©¤©Ø©¤©¤©¤©Ø©¤©¤©¤©¼ ©À©¤©¤©¤©à©¤©¤©¤©à©¤©¤©¤©È + ©¦
 * ©¦ Caps ©¦ A ©¦ S ©¦ D ©¦ F ©¦ G ©¦ H ©¦ J ©¦ K ©¦ L ©¦: ;©¦" '©¦ Enter  ©¦               ©¦ 4 ©¦ 5 ©¦ 6 ©¦   ©¦
 * ©À©¤©¤©¤©¤©¤©¤©Ø©¤©Ð©¤©Ø©¤©Ð©¤©Ø©¤©Ð©¤©Ø©¤©Ð©¤©Ø©¤©Ð©¤©Ø©¤©Ð©¤©Ø©¤©Ð©¤©Ø©¤©Ð©¤©Ø©¤©Ð©¤©Ø©¤©Ð©¤©Ø©¤©Ð©¤©Ø©¤©¤©¤©¤©¤©¤©¤©¤©È     ©°©¤©¤©¤©´     ©À©¤©¤©¤©à©¤©¤©¤©à©¤©¤©¤©à©¤©¤©¤©È
 * ©¦ Shift  ©¦ Z ©¦ X ©¦ C ©¦ V ©¦ B ©¦ N ©¦ M ©¦< ,©¦> .©¦? /©¦  Shift   ©¦     ©¦ ¡ü ©¦     ©¦ 1 ©¦ 2 ©¦ 3 ©¦   ©¦
 * ©À©¤©¤©¤©¤©¤©Ð©¤©¤©Ø©¤©Ð©¤©Ø©¤©¤©Ð©Ø©¤©¤©¤©Ø©¤©¤©¤©Ø©¤©¤©¤©Ø©¤©¤©¤©Ø©¤©¤©¤©Ø©¤©¤©Ð©Ø©¤©¤©¤©à©¤©¤©¤©Ø©Ð©¤©¤©¤©¤©Ð©¤©¤©¤©¤©È ©°©¤©¤©¤©à©¤©¤©¤©à©¤©¤©¤©´ ©À©¤©¤©¤©Ø©¤©¤©¤©à©¤©¤©¤©È E©¦©¦
 * ©¦ Ctrl©¦ Win©¦ Alt©¦         Space         ©¦ Alt©¦ Win©¦Menu©¦Ctrl©¦ ©¦ ¡û ©¦ ¡ý ©¦ ¡ú ©¦ ©¦   0   ©¦ . ©¦¡û©¤©¼©¦
 * ©¸©¤©¤©¤©¤©¤©Ø©¤©¤©¤©¤©Ø©¤©¤©¤©¤©Ø©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©Ø©¤©¤©¤©¤©Ø©¤©¤©¤©¤©Ø©¤©¤©¤©¤©Ø©¤©¤©¤©¤©¼ ©¸©¤©¤©¤©Ø©¤©¤©¤©Ø©¤©¤©¤©¼ ©¸©¤©¤©¤©¤©¤©¤©¤©Ø©¤©¤©¤©Ø©¤©¤©¤©¼
 */

