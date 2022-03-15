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
const int N=3e5+5;
struct Tree
{
	int ch[2];
	int size;
} tree[N*35];
int tot=1;
inline void insert(int val)
{
	int u=1;
	for(int i=31; i>=0; --i)
	{
		int c=(val>>i)&1;
		++tree[u].size;
		if(!tree[u].ch[c])
			tree[u].ch[c]=++tot;
		u=tree[u].ch[c];
	}
	++tree[u].size;
}
inline int query(int val)
{
	int u=1;
	int ans=0;
	for(int i=31; i>=0; --i)
	{
		int c=(val>>i)&1;
		--tree[u].size;
		if(tree[tree[u].ch[c]].size)
			u=tree[u].ch[c];
		else
		{
			ans|=1<<i;
			u=tree[u].ch[!c];
		}
	}
	--tree[u].size;
	return ans;
}
int n,a[N],p[N];
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	for(int i=1; i<=n; ++i)
	{
		read(p[i]);
		insert(p[i]);
	}
	for(int i=1; i<=n; ++i)
		printf("%d ",query(a[i]));
	putchar('\n');
	return 0;
}


