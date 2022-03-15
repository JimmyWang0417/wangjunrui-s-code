#include<cstdio>
using namespace std;
const int infinite=0b111111111111111111111111111111;
struct Edge
{
	int next,to,dis;
} edge[0b11110100001001110010];
int num_edge,first[0b11000011010100001],n,m,a,b,c,q[0b11000011010100001],dis[0b11000011010100001];
bool exist[0b11000011010100001];
inline int read()
{
	register char s=getchar();
	register int x=0;
	while(s<'0'||s>'9')
		s=getchar();
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	return x;
}
inline void add_edge(int from,int to,int dis)
{
	edge[++num_edge].next=first[from];
	edge[num_edge].to=to;
	edge[num_edge].dis=dis;
	first[from]=num_edge;
}
int main()
{
	n=read();
	m=read();
	for(register int i=1; i<=m; i++)
	{
		a=read();
		b=read();
		c=read();
		add_edge(a,b,c);
		add_edge(b,a,c);
	}
	register int head=0,tail=1;
	q[1]=1;
	exist[1]=true;
	for(register int i=2; i<=n; i++)
		dis[i]=infinite;
	do
	{
		head=head==0b11000011010100000?0b1:head+0b1;
		int *u=&q[head];
		exist[*u]=false;
		for(register int i=first[(*u)]; i; i=edge[i].next)
			if(dis[edge[i].to]>dis[*u]+edge[i].dis)
			{
				dis[edge[i].to]=dis[*u]+edge[i].dis;
				if(!exist[edge[i].to])
				{
					exist[edge[i].to]=true;
					tail=tail==0b11000011010100000?0b1:tail+1;
					q[tail]=edge[i].to;
				}
			}
	}
	while(head!=tail);
	printf("%d\n",dis[n]);
}
