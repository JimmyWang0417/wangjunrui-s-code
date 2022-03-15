#include<cstdio>
#include<cstring>
using namespace std;
bool bo[1000005];
int ch[1000005][30],n,m,tot=1;
char str[1000005];
bool kk[1000005];
inline void insert(char*s)
{
	register int u=1,len=strlen(s+1);
	for(register int i=1; i<=len; ++i)
	{
		int c=s[i]-'a';
		if(!ch[u][c])
			ch[u][c]=++tot;
		u=ch[u][c];
	}
	bo[u]=true;
}
inline void find(char*s)
{
	register int ans,now=1,len=strlen(s+1);
	memset(kk,0,sizeof kk);
	kk[0]=1;
	for(register int i=0,k; i<=len; ++i)
	{
		if(kk[i])
		{
			ans=i;
			for(k=i+1,now=1; k<=len; ++k)
			{
				int c=s[k]-'a';
				now=ch[now][c];
				if(!now)
					break;
				if(bo[now])
					kk[k]=1;
			}
		}
	}
	printf("%d\n",ans);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(register int i=1; i<=n; ++i)
	{
		scanf("%s",str+1);
		insert(str);
	}
	for(register int i=1; i<=m; ++i)
	{
		scanf("%s",str+1);
		find(str);
	}
	return 0;
}
