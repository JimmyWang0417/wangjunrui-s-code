#include<cstdio>
#include<cstring>
#include<algorithm>
#define re register
const int N=1e6+10;
char str[N];
int ch[N*60][2],tot=1;
inline int insert()
{
	int res=0;
	for(re int i=1,u=1; i<=1000; ++i)
	{
		int c=str[i]-'0';
		if(!ch[u][c])
		{
			if(!res)
				res=i-1;
			ch[u][c]=++tot;
		}
		u=ch[u][c];
	}
	return res;
}
int n,ans;
int main()
{
	scanf("%d",&n);
	int ans=0;
	for(re int i=1; i<=n; ++i)
	{
		scanf("%s",str+1);
		int len=strlen(str+1);
		for(re int j=len+1; j<=1000; ++j)
			str[j]=str[j-len];
		ans=std::max(ans,insert());
	}
	printf("%d\n",ans);
}
