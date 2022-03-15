#include<cstdio>
#include<cctype>
#include<algorithm>
#define re register
using namespace std;
namespace IO
{
	template<typename T>
	inline void read(T & x)
	{
		x=0;
		bool bo=false;
		char ch=getchar();
		while(!isdigit(ch)&&ch^'-')
			ch=getchar();
		if(ch=='-')
		{
			bo=true;
			ch=getchar();
		}
		while(isdigit(ch))
		{
			x=(x<<1)+(x<<3)+(ch^'0');
			ch=getchar();
		}
		if(bo)
			x=-x;
		return;
	}
	char Out[6*1000000],*fe=Out;
	char ch[30];
	int num;
	template<typename T>
	inline void write(T x)
	{
		if(!x)
			*fe++=48;
		if(x<0)
		{
			x=-x;
			*fe++='-';
		}
		num=0;
		while(x)
		{
			ch[++num]=x%10+'0';
			x/=10;
		}
		while(num)
			*fe++=ch[num--];
		*fe++='\n';
	}
	inline void flush()
	{
		fwrite(Out,1,fe-Out,stdout);
		fe=Out;
	}
}
using IO::read;
using IO::write;
#define mod 10007
#define e(i,u) for(re int i=head[u];i;i=edge[i].next)
const int N=1010;
int T,head[N],ans,c[N][N],num_edge,tmp[N],f[N],size[N],n;
struct Edge
{
	int next,to,dis;
} edge[N];
inline void add_edge(int from,int to)
{
	edge[++num_edge].next=head[from];
	head[from]=num_edge;
	edge[num_edge].to=to;
}
inline void dfs(int u)
{
	f[u]=size[u]=1;
	e(i,u)
	{
		int &v=edge[i].to;
		dfs(v);
		size[u]+=size[v];
	}
	int num=size[u]-2;
	e(i,u)
	{
		int &v=edge[i].to;
		f[u]=1ll*f[u]*f[v]%mod*c[num][size[v]-1]%mod;
		num-=size[v];
	}
	return;

}
int main()
{
	for(re int i=0; i<=1000; i++)
		c[i][0]=1;
	for(re int i=1; i<=1000; i++)
		for(re int j=1; j<=i; j++)
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
	read(T);
	while(T--)
	{
		read(n);
		for(re int i=1,tot; i<=n; i++)
		{
			read(tot);
			for(re int j=1; j<=tot; j++)
				read(tmp[j]);
			for(re int j=tot; j>=1; j--)
				add_edge(i,tmp[j]);
		}
		dfs(1);
		write(f[1]);
		fill(head+1,head+1+n,0);
		num_edge=0;
	}
	IO::flush();
	return 0;
}
