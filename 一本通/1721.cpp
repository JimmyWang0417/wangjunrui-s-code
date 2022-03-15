#include<cstdio>
#include<algorithm>
#include<cstring>
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
const int N=160,M=5010;
int n,m,q,num_edge,f[N][N][N];
struct Edge
{
	int u,v,w;
} edge[M];
inline bool cmp(Edge a,Edge b)
{
	return a.w<b.w;
}
int main()
{
	read(n);
	read(m);
	read(q);
	for(re int i=1; i<=m; i++)
	{
		read(edge[i].u);
		read(edge[i].v);
		read(edge[i].w);
	}
	sort(edge+1,edge+1+m,cmp);
	for(re int i=1; i<=n; i++)
		for(re int j=1; j<=n; j++)
			for(re int k=0; k<=n; k++)
				if(i!=j||k)
					f[i][j][k]=0x3f3f3f3f;
	for(re int k=1; k<=m; k++)
		for(re int i=1; i<=n; i++)
			for(re int j=0; j<=n; j++)
				f[i][edge[k].v][j+1]=min(f[i][edge[k].v][j+1],f[i][edge[k].u][j]+edge[k].w);
	for(re int k=1; k<=n; k++)
		for(re int i=1; i<=n; i++)
			for(re int j=1; j<=n; j++)
				f[i][j][k]=min(f[i][j][k],f[i][j][k-1]);
	re int u,v,w;
	while(q--)
	{
		read(u);
		read(v);
		read(w);
		w=min(n,w);
		printf("%d\n",f[u][v][w]==0x3f3f3f3f?-1:f[u][v][w]);
	}
	///printf("%d\n",f[1][4][2]);
	return 0;
}

