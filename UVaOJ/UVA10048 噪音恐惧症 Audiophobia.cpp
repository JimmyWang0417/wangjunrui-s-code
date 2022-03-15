#include<cstdio>
#include<cstring>
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
int n,m,q,f[110][110],kase;
int main()
{
	while(read(n),read(m),read(q),n||m||q)
	{
		if(kase)
			putchar('\n');
		printf("Case #%d\n",++kase);
		memset(f,0x3f3f3f3f,sizeof(f));
		for(re int i=1,u,v,w; i<=m; i++)
		{
			read(u);
			read(v);
			read(w);
			f[u][v]=f[v][u]=w;
		}
		for(re int k=1; k<=n; k++)
			for(re int i=1; i<=n; i++)
				for(re int j=1; j<=n; j++)
					f[i][j]=min(f[i][j],max(f[i][k],f[k][j]));
		for(re int i=1,x,y; i<=q; i++)
		{
			read(x);
			read(y);
			f[x][y]==0x3f3f3f3f?puts("no path"):printf("%d\n",f[x][y]);
		}
	}
	return 0;
}

