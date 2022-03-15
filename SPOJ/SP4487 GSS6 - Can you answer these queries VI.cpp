#include <ctime>
#include <cstdio>
#include <random>
#include <algorithm>
#define re register
#define ll long long
#define lc(x) tree[x].l
#define rc(x) tree[x].r
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

using std::max;
const ll INF=1e18;
struct Tree
{
	int l,r,size;
	int val,key;
	ll suf,pre,sum,ans;
} tree[200000+5];
int cnt,root;
std::mt19937 rnd((unsigned int)time(0));
inline int newnode(int val)
{
	++cnt;
	tree[cnt].suf=tree[cnt].pre=tree[cnt].sum=tree[cnt].ans=tree[cnt].val=val;
	tree[cnt].key=rnd();
	tree[cnt].size=1;
	lc(cnt)=rc(cnt)=0;
	return cnt;
}
inline void update(int now)
{
	tree[now].size=tree[lc(now)].size+tree[rc(now)].size+1;
	tree[now].sum=tree[lc(now)].sum+tree[now].val+tree[rc(now)].sum;
	tree[now].pre=max(tree[lc(now)].pre,tree[lc(now)].sum+tree[now].val+max(0ll,tree[rc(now)].pre));
	tree[now].suf=max(tree[rc(now)].suf,tree[rc(now)].sum+tree[now].val+max(0ll,tree[lc(now)].suf));
	tree[now].ans=max(max(tree[lc(now)].ans,tree[rc(now)].ans),max(0ll,tree[lc(now)].suf)+tree[now].val+max(0ll,tree[rc(now)].pre));
}
inline void split(int now,int size,int &x,int &y)
{
	if(!now)
		x=y=0;
	else
	{
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
		update(now);
	}
}
inline int merge(int x,int y)
{
	if(!x||!y)
		return x|y;
	if(tree[x].key>tree[y].key)
	{
		rc(x)=merge(rc(x),y);
		update(x);
		return x;
	}
	else
	{
		lc(y)=merge(x,lc(y));
		update(y);
		return y;
	}
}
inline void insert(int pos,int val)
{
	int x,y;
	split(root,pos-1,x,y);
	root=merge(merge(x,newnode(val)),y);
}
inline void del(int pos)
{
	int x,y,z;
	split(root,pos-1,x,y);
	split(y,1,y,z);
	root=merge(x,z);
}
inline void replace(int pos,int val)
{
	int x,y,z;
	split(root,pos-1,x,y);
	split(y,1,y,z);
	tree[y].val=val;
	update(y);
	root=merge(x,merge(y,z));
}
inline void maxsum(int l,int r)
{
	int x,y,z;
	split(root,r,x,z);
	split(x,l-1,x,y);
	printf("%lld\n",tree[y].ans);
	root=merge(merge(x,y),z);
}
int sta[100000+5];
int n,m;
inline int build(int tot)
{
	int val,top;
	read(val);
	sta[top=1]=newnode(val);
	for(re int i=1; i<tot; ++i)
	{
		read(val);
		int last=0,res=newnode(val);
		while(top&&tree[res].key>tree[sta[top]].key)
			update(last=sta[top--]);
		lc(res)=last;
		update(res);
		if(top)
		{
			rc(sta[top])=res;
			update(sta[top]);
		}
		sta[++top]=res;
	}
	while(top)
		update(sta[top--]);
	return sta[1];
}
char str[5];
int main()
{
	tree[0].pre=tree[0].suf=tree[0].ans=-INF;
	read(n);
	root=build(n);
	read(m);
	while(m--)
	{
		scanf("%s",str);
		int pos,val;
		read(pos);
		if(str[0]=='D')
			del(pos);
		else
		{
			read(val);
			if(str[0]=='I')
				insert(pos,val);
			else if(str[0]=='R')
				replace(pos,val);
			else
				maxsum(pos,val);
		}
	}
	return 0;
}
