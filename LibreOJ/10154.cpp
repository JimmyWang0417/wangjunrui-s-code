#include<cstdio>
#include<vector>
#include<cstring>
#define re register
using namespace std;
vector<int>son[310];
int f[310][310],s[310],n,m,x;
inline int max(int a,int b)
{
	return a>b?a:b;
}
inline int read()
{
	char s=getchar();
	bool f=false;
	int x=0;
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
	return f?-x:x;
}
inline void dp(int x)
{
	f[x][0]=0;
	for(re int i=0,*y; i<son[x].size(); i++)
	{
		y=&son[x][i];
		dp(*y);
		for(re int t=m; t>=0; t--)
			for(re int j=t; j>=0; j--)
				f[x][t]=max(f[x][t],f[x][t-j]+f[*y][j]);
	}
	if(x!=0)
		for(re int t=m; t>0; t--)
			f[x][t]=f[x][t-1]+s[x];
}
int main()
{
	n=read();
	m=read();
	for(re int i=1;i<=n;i++)
	{
		x=read();
		s[i]=read();
		son[x].push_back(i);
	}
	memset(f,-1,sizeof(f));
	dp(0);
	printf("%d\n",f[0][m]);
	return 0;
}

