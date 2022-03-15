#include<cstdio>
#include<queue>
#include<map>
#define re register
using namespace std;
const int N=1010;
int t,kase,n,x,u;
char cmd[10];
int main()
{
	while(scanf("%d",&t)!=EOF&&t)
	{
		printf("Scenario #%d\n",++kase);
		queue<int>q,q2[N];
		map<int,int>team;
		for(re int i=0; i<t; i++)
		{
			scanf("%d",&n);
			while(n--)
			{
				scanf("%d",&x);
				team[x]=i;
			}
		}
		while(1)
		{
			scanf("%s",cmd);
			if(cmd[0]=='S')
				break;
			else if(cmd[0]=='D')
			{
				u=q.front();
				printf("%d\n",q2[u].front());
				q2[u].pop();
				if(q2[u].empty())
					q.pop();
			}
			else if(cmd[0]=='E')
			{
				scanf("%d",&x);
				u=team[x];
				if(q2[u].empty())
					q.push(u);
				q2[u].push(x);
			}
		}
		putchar('\n');
	}
	return 0;
}
