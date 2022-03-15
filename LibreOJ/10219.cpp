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
struct node
{
	int n,m,g[110][110];
} a,b,c;
inline void matrix_multiple(node *a,node *b,node *c)
{
	c->n=a->n;
	c->m=b->m;
	for(re int i=1; i<=c->n; i++)
		for(re int j=1; j<=c->m; j++)
			for(re int k=1; k<=a->m; k++)
				c->g[i][j]+=a->g[i][k]*b->g[k][j];
}
int main()
{
	read(a.n);
	read(a.m);
	b.n=a.m;
	for(re int i=1; i<=a.n; i++)
		for(re int j=1; j<=b.n; j++)
			read(a.g[i][j]);
	read(b.m);
	for(re int i=1; i<=b.n; i++)
		for(re int j=1; j<=b.m; j++)
			read(b.g[i][j]);
	matrix_multiple(&a,&b,&c);
	for(re int i=1; i<=c.n; i++)
	{
		for(re int j=1; j<c.m; j++)
			printf("%d ",c.g[i][j]);
		printf("%d\n",c.g[i][c.m]);
	}
	return 0;
}

