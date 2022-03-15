#include<cstdio>
using namespace std;
int n,father[100001],ans[100001];
inline int find(int x)
{
	if(father[x]!=x)return father[x]=find(father[x]);
	return x;
}
int main()
{
	register int m;
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++)
	{
		ans[i]=1;
		father[i]=i;
	}
	while(m--)
	{
		char s[2];
		scanf("%s",s);
		if(s[0]=='M')
		{
			int x,y;
			scanf("%d%d",&x,&y);
			int fx=find(x),fy=find(y);
			if(fx!=fy)
			{
				father[fy]=fx;
				ans[fx]+=ans[fy];
			}
		}
		else
		{
			int x;
			scanf("%d",&x);
			printf("%d\n",ans[find(x)]);
		}
	}
}
