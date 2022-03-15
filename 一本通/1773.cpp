#include<cstdio>
#include<cctype>
#include<algorithm>
#define re register
#define Tree(u) for(re int i=head[u],v;v=edge[i].to,i;i=edge[i].next)
using namespace std;
namespace IO
{
	template<typename T>
	inline void read(T &x)
	{
		x=0;
		char ch=getchar();
		bool f=false;
		while (!isdigit(ch) && ch^'-') ch=getchar();
		if (ch=='-') f=true, ch=getchar();
		while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
		if(f)
			x=-x;
		return;
	}
	char Out[1<<28],*fe=Out;
	inline void flush()
	{
		fwrite(Out,1,fe-Out,stdout);
		fe=Out;
		return;
	}
	template<typename T>
	inline void write(T x)
	{
		if (!x) *fe++=48;
		if (x<0) *fe++='-', x=-x;
		T num=0, ch[20];
		while (x) ch[++num]=x%10+48, x/=10;
		while (num) *fe++=ch[num--];
		int t=0;
		return;
	}
	inline void insert_char(char s)
	{
		*fe++=s;
		return;
	}
}
using namespace IO;
const int N=2e5+10;
int n,head[N],num_edge,p[N],suml[N],sumr[N],g[N],f[N],sum[N],ans=0x3f3f3f3f;
int flag,tot;
struct Edge
{
	int next,to;
} edge[N];
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
}
#define z(u) (flag==u?g[u]:f[u])
inline bool cmp(int a,int b)
{
	return z(a)>z(b);
}
inline void dfs1(int u)
{
	Tree(u)
	dfs1(v);
	tot=flag=0;
	Tree(u)
	p[++tot]=v;
	stable_sort(p+1,p+1+tot,cmp);
	for(re int i=1; i<=tot; i++)
		f[u]=max(f[u],i+f[p[i]]);
	return;
}
inline void dfs2(int u)
{
	if(u>1)
		p[tot=1]=flag=u;
	else
		flag=tot=0;
	Tree(u)
	p[++tot]=v;
	stable_sort(p+1,p+1+tot,cmp);
	suml[0]=sumr[tot+1]=0;
	for(re int i=1; i<=tot; i++)
		suml[i]=max(suml[i-1],i+z(p[i]));
	for(re int i=tot; i>=1; i--)
		sumr[i]=max(sumr[i+1],i+z(p[i]));
	for(re int i=1; i<=tot; i++)
	{
		if(p[i]==u)
			continue;
		g[p[i]]=max(suml[i-1],sumr[i+1]-1);
	}
	sum[u]=suml[tot];
	Tree(u)
	dfs2(v);
}
int main()
{
	read(n);
	for(re int i=2,x; i<=n; i++)
	{
		read(x);
		add_edge(x,i);
	}
	dfs1(1);
	dfs2(1);
	for(re int i=1; i<=n; i++)
		ans=min(ans,sum[i]);
	write(ans+1);
	insert_char('\n');
	for(re int i=1; i<=n; i++)
		if(ans==sum[i])
		{
			write(i);
			insert_char(' ');
		}
	insert_char('\n');
	flush();
	return 0;
}
