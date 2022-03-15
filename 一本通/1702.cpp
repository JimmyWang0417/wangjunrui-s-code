#include<cstdio>
#include<algorithm>
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
struct node
{
	int x,y,v;
} q[1010];
int x[1010],y[N],n,m,u,d,l,r,k,tot,ch[N*32][2],num,root[N],sum[N*32],Q;
inline void insert(int x,int&t,const int&v)
{
	re int y;
	t=y=++tot;
	bool c;
	for(re int i=30; i>=0; i--)
	{
		c=(v>>i)&1;
		ch[y][0]=ch[x][0];
		ch[y][1]=ch[x][1];
		y=ch[y][c]=++tot;
		x=ch[x][c];
		sum[y]=sum[x]+1;
	}
	return;
}
inline int query(int k)
{
	re int ans=0,size;
	for(re int i=30; i>=0; i--)
	{
		size=0;
		for(re int j=1; j<=num; j++)
		{
			int t=(q[j].v>>i)&1;
			size+=sum[ch[q[j].y][t^1]]-sum[ch[q[j].x][t^1]];
		}
		if(size>=k)
		{
			ans|=1<<i;
			for(re int j=1; j<=num; j++)
			{
				int t=(q[j].v>>i)&1;
				q[j].x=ch[q[j].x][t^1];
				q[j].y=ch[q[j].y]bb[t^1];
			}
		}
		else
		{
			k-=size;
			for(re int j=1; j<=num; j++)
			{
				int t=(q[j].v>>i)&1;
				q[j].x=ch[q[j].x][t];
				q[j].y=ch[q[j].y][t];
			}
		}
	}
	return ans;
}
int main()
{
	read(n);
	read(m);
	for(re int i=1; i<=n; i++)
		read(x[i]);
	for(re int i=1; i<=m; i++)
	{
		read(y[i]);
		insert(root[i-1],root[i],y[i]);
	}
	/*for(re int i=1; i<=n; i++)
		printf("%d\n",root[i]);*/
	read(Q);
	while(Q--)
	{
		read(u);
		read(d);
		read(l);
		read(r);
		read(k);
		num=0;
		for(re int i=u; i<=d; i++)
			q[++num]= node{root[l-1],root[r],x[i]};
		printf("%d\n",query(k));
	}
	return 0;
}

