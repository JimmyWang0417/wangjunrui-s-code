#include<stdio.h>
#include<ctype.h>
#define re register
using namespace std;
namespace IO
{
	template<typename T>
	inline void read(T &x)
	{
		x=0;
		T f=1, ch=getchar();
		while (!isdigit(ch) && ch^'-') ch=getchar();
		if (ch=='-') f=-1, ch=getchar();
		while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
		x*=f;
	}
	char Out[1<<28],*fe=Out;
	inline void flush()
	{
		fwrite(Out,1,fe-Out,stdout);
		fe=Out;
	}
	template<typename T>
	inline void write(T x)
	{
		if (!x) *fe++=48;
		if (x<0) *fe++='-', x=-x;
		T num=0, ch[20];
		while (x) ch[++num]=x%10+48, x/=10;
		while (num) *fe++=ch[num--];
		*fe++='\n';
	}
}
using namespace IO;
#define mod 16
const int N=100010,SIZE=20;
int n,M,ans[N][SIZE],f[N][SIZE],head[N],num_edge,size[N];
long long sum,s[N];
struct Edge
{
	int next,to,dis;
} edge[N<<1];
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=head[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	head[from]=num_edge;
}
#define FOR(k) for(re int k=0;k<16;++k)
inline void dfs1(int u,int father,long long dep)
{
	size[u]=1;
	f[u][0]=1;
	sum+=dep;
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to,&w=edge[i].dis;
		if(v==father)
			continue;
		dfs1(v,u,dep+w);
		size[u]+=size[v];
		FOR(j)
		f[u][(j+w)%mod]+=f[v][j];
	}
	return;
}
inline void dfs2(int u,int father,long long cnt)
{
	s[u]=cnt;
	FOR(i)
	ans[u][i]+=f[u][i];
	for(re int i=head[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to,&w=edge[i].dis;
		if(v==father)
			continue;
		FOR(j)
		ans[v][(j+w)%mod]+=ans[u][j]-f[v][((j-w)%mod+mod)%mod];
		dfs2(v,u,cnt-size[v]*w+(size[1]-size[v])*w);
	}
	return;
}
int main()
{
	read(n);
	read(M);
	for(re int i=1,u,v,w; i<n; ++i)
	{
		read(u);
		read(v);
		read(w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	dfs1(1,0,0);
	/*printf("%d\n",sum);
	for(re int i=1; i<=n; i++)
	{
		for(re int j=0; j<16; j++)
			printf("%d ",f[i][j]);
		putchar('\n');
	}*/
	dfs2(1,0,sum);
	re long long res;
	for(re int i=1; i<=n; ++i)
	{
		res=s[i];
		FOR(j)
		res+=ans[i][j]*((j^M)%mod-j);
		res-=M;
		write(res);
	}
	flush();
	return 0;
}
