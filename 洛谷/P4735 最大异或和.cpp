#include<cstdio>
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
const int N=300010;
int tot,ch[N*70][2],sum[N*70],tree_node,root[N*70],n,m;
inline void insert(int x)
{
	int rt=root[tree_node];
	root[++tree_node]=++tot;
	for(re int i=27; i>=0; i--)
	{
		bool c=(x>>i)&1;
		sum[tot]=sum[rt]+1;
		ch[tot][!c]=ch[rt][!c];
		ch[tot][c]=tot+1;
		rt=ch[rt][c];
		tot++;
	}
	sum[tot]=sum[rt]+1;
	return;

}
inline int query(int l,int r,int x)
{
	int lc=root[l],rc=root[r],ans=0;
	for(re int i=27; i>=0; i--)
	{
		bool c=(x>>i)&1;
		if(sum[ch[rc][!c]]-sum[ch[lc][!c]]>0)
		{
			lc=ch[lc][!c];
			rc=ch[rc][!c];
			ans|=(1<<i);
		}
		else
		{
			lc=ch[lc][c];
			rc=ch[rc][c];
		}
	}
	return ans;
}
inline bool getc()
{
	char ch=getchar();
	while(ch<'A'||ch>'Z')ch=getchar();
	return ch=='A';
}
int main()
{
	read(n);
	read(m);
	int ans=0;
	insert(0);
	for(re int i=1,x; i<=n; i++)
	{
		read(x);
		ans^=x;
		insert(ans);
	}
	for(re int i=1,x,l,r; i<=m; i++)
	{
		if(getc())
		{
			read(x);
			ans^=x;
			insert(ans);
		}
		else
		{
			read(l);
			read(r);
			read(x);
			printf("%d\n",query(l-1,r,ans^x));
		}
	}
	return 0;
}
