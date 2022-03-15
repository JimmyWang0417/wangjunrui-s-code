#include<cstdio>
#include<cstring>
#define re register
using namespace std;
const int N=101;
int ans,n,m,a[N][N],x;
long long b[N];
bool bo[N],boo;
char s[N];
inline void DFS(int t,int cnt,long long res)
{
	if(cnt+m-t+1<=ans)
		return;
	if(t>m)
	{
		//printf("%d\n",cnt);
		if(cnt>ans)
			ans=cnt;
		return;
	}
	if(((~res)&(1ll<<(t-1)))&&((~b[t])&(1ll<<(t-1))))
		DFS(t+1,cnt+1,res|b[t]);
	DFS(t+1,cnt,res);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(re int i=1; i<=m; i++)
	{
		scanf("%s",s+1);
		int len=strlen(s+1);
		for(re int j=1ll; j<=len; j++)
		{
			scanf("%d",&x);
			a[i][s[j]]=x;
		}
	}
	for(re int i=1; i<=m; i++)
		for(re int j=1; j<=m; j++)
		{
			memset(bo,false,sizeof(bo));
			boo=false;
			for(re char k='A'; k<='Z'; k++)
				if(a[i][k]&&a[j][k]&&a[i][k]!=a[j][k])
				{
					boo=true;
					break;
				}
			if(boo)
			{
				b[i]|=1ll<<(j-1);
				continue;
			}
			for(re char k='A'; k<='Z'; k++)
				if(a[i][k]||a[j][k])
				{
					if(!a[j][k])
						x=a[i][k];
					else
						x=a[j][k];
					if(!bo[x])
						bo[x]=true;
					else
					{
						boo=true;
						break;
					}
				}
			if(boo)
				b[i]|=1ll<<(j-1);
		}
	DFS(1,0,0ll);
	printf("%d\n",ans);
	/*for(re int i=1; i<=m; i++)
		printf("%d ",b[i]);*/
	return 0;
}
