#include<cstdio>
#include<cstring>
using namespace std;
const int N=1e5+2;
int tot;
int ch[N][10];
bool bo[N];
char s[20];
#define r register
inline int wjr_strlen(char *s)
{
	r int len=0;
	while(s[len]!=0)len++;
	return len;
}
inline bool insert(char *s)
{
	int len=wjr_strlen(s),u=1;
	bool flag=false;
	for(r int i=0,c; i<len; i++)
	{
		c=s[i]-'0';
		if(!ch[u][c])
			ch[u][c]=++tot;
		else if(i==len-1)
			flag=true;
		u=ch[u][c];
		if(bo[u])
			flag=true;
	}
	bo[u]=true;
	return flag;
}
int main()
{
	r int t,n;
	r bool ans;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		tot=1;
		memset(ch,0,sizeof(ch));
		memset(bo,false,sizeof(bo));
		ans=false;
		for(r int i=1; i<=n; i++)
		{
			scanf("%s",&s);
			ans=ans||insert(s);
		}
		if(!ans)
			printf("YES\n");
		else
			printf("NO\n");
	}
}

