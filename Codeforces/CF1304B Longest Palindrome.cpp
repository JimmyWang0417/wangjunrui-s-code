#include<cstdio>
#include<string>
#include<algorithm>
#include <iostream>
#define re register
using namespace std;
const int N=105,M=55;
int n,m;
bool vis[N];
char str[N][M],rever[N][M];
inline bool check(char *a,char *b)
{
	for(re int i=1; i<=m; ++i)
		if(a[i]!=b[i])
			return false;
	return true;
}
int a[N],b[N],top1,top2;
int main()
{
	ios::sync_with_stdio(false);
	scanf("%d%d",&n,&m);
	for(re int i=1; i<=n; ++i)
	{
		scanf("%s",str[i]+1);
		for(re int j=1; j<=m; ++j)
			rever[i][j]=str[i][m-j+1];
	}
	for(re int i=1; i<=n; ++i)
		for(re int j=i+1; j<=n; ++j)
			if(check(rever[i],str[j]))
			{
				a[++top1]=i;
				vis[i]=true;
				vis[j]=true;
				break;
			}
	for(re int i=1; i<=n; ++i)
		if(!vis[i]&&check(str[i],rever[i]))
			b[++top2]=i;
	printf("%d\n",(top1*2+min(top2,1))*m);
	for(re int i=1; i<=top1; ++i)
		printf("%s",str[a[i]]+1);
	for(re int i=1; i<=min(top2,1); ++i)
		printf("%s",str[b[i]]+1);
	for(re int i=top1; i>=1; --i)
		printf("%s",rever[a[i]]+1);
	putchar('\n'); 
	return 0;
}
