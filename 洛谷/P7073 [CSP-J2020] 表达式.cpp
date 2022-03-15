#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
char str[N];
int n,a[N];
struct node
{
	bool flag;
	int val;
	node(bool _flag=false,int _val=0):flag(_flag),val(_val) {}
} p[N];
int st[N],top;
int lc[N],rc[N];
int id[N];
int fa[N];
int g[N];
inline int calc(int u)
{
	int &val=g[u];
	if(p[u].flag==0)
		val=p[u].val;
	else
	{
		fa[lc[u]]=fa[rc[u]]=u;
		if(p[u].val==0)
			val=!calc(lc[u]);
		else if(p[u].val==1)
			val=calc(lc[u])&calc(rc[u]);
		else if(p[u].val==2)
			val=calc(lc[u])|calc(rc[u]);
	}
//	printf("+%d %d\n",u,val);
	return val;
}
int dp[N][2];
bool vis[N][2];
inline int dfs(int u,int val)
{
//	printf("%d ",u);
	if(vis[u][val])
		return dp[u][val];
	vis[u][val]=true;
	int &ans=dp[u][val];
	if(p[fa[u]].val==0)
		ans=dfs(fa[u],!val);
	else if(p[fa[u]].val==1)
	{
		int other=(u==lc[fa[u]]?rc[fa[u]]:lc[fa[u]]);
		ans=dfs(fa[u],val&g[other]);
	}
	else if(p[fa[u]].val==2)
	{
		int other=(lc[fa[u]]==u?rc[fa[u]]:lc[fa[u]]);
		ans=dfs(fa[u],val|g[other]);
	}
	return ans;
}
bool in[N];
int main()
{
	scanf("%[^\n]%d",str,&n);
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]);
	int cnt=0;
	for(int i=0; str[i]; ++i)
	{
		if(str[i]=='x')
		{
			++i;
			int x=str[i]-'0';
			while(str[i+1]>='0'&&str[i+1]<='9')
				x=x*10+str[++i]-'0';
			p[++cnt]=node(0,a[x]);
			st[++top]=cnt;
			id[x]=cnt;
		}
		else
		{
			if(str[i]=='!')
			{
				++cnt;
				p[cnt]=node(1,0);
				lc[cnt]=st[top];
				in[st[top]]=true;
				--top;
				st[++top]=cnt;
			}
			else if(str[i]=='&')
			{
				++cnt;
				p[cnt]=node(1,1);
				lc[cnt]=st[top];
				in[st[top]]=true;
				--top;
				rc[cnt]=st[top];
				in[st[top]]=true;
				--top;
				st[++top]=cnt;
			}
			else if(str[i]=='|')
			{
				++cnt;
				p[cnt]=node(1,2);
				lc[cnt]=st[top];
				in[st[top]]=true;
				--top;
				rc[cnt]=st[top];
				in[st[top]]=true;
				--top;
				st[++top]=cnt;
			}
		}
	}
	int rt=1;
	for(int i=1; i<=cnt; ++i)
		if(!in[i])
		{
			rt=i;
			break;
		}
	calc(rt);
//	printf("rt=%d\n",rt);
	vis[rt][0]=vis[rt][1]=true;
	dp[rt][1]=1;
	int q;
	scanf("%d",&q);
	while(q--)
	{
		int x;
		scanf("%d",&x);
		printf("%d\n",dfs(id[x],!a[x]));
	}
//	for(int u=1; u<=cnt; ++u)
//		for(int i=head[u]; i; i=edge[i].next)
//			printf("edge=%d %d\n",u,edge[i].to);
//	for(int i=1; i<=cnt; ++i)
//		printf("%d %d\n",p[i].flag,p[i].val);
	return 0;
}
