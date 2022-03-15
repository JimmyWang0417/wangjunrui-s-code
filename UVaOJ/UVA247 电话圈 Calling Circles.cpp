#include<map>
#include<string>
#include<cstring>
#include<iostream>
#include<cstdio>
#define re register
using namespace std;
map<string,int>cnt;
string name[1010],name1,name2;
int kase,num,n,m,x,y;
bool dis[1010][1010],flag[1010];
int main()
{
	while(scanf("%d%d",&n,&m)==2&&n+m)
	{
		if(kase!=0)
			putchar('\n');
		cnt.clear();
		memset(dis,false,sizeof(dis));
		memset(flag,false,sizeof(flag));
		num=0;
		printf("Calling circles for data set %d:\n",++kase);
		for(re int i=1; i<=m; i++)
		{
			cin>>name1>>name2;
			if(cnt.count(name1))
				x=cnt[name1];
			else
			{
				cnt[name1]=++num;
				name[num]=name1;
				x=num;
			}
			if(cnt.count(name2))
				y=cnt[name2];
			else
			{
				cnt[name2]=++num;
				name[num]=name2;
				y=num;
			}

			dis[x][y]=true;
		}
		for(re int k=1; k<=n; k++)
			for(re int i=1; i<=n; i++)
				for(re int j=1; j<=n; j++)
					dis[i][j]=dis[i][j]||(dis[i][k]&&dis[k][j]);
		for(re int i=1; i<=n; i++)
		{
			if(flag[i])
				continue;
			flag[i]=true;
			printf("%s",name[i].c_str());
			for(re int j=i+1; j<=n; j++)
			{
				if(flag[j])
					continue;
				if(dis[i][j]&&dis[j][i])
				{
					printf(", %s",name[j].c_str());
					flag[j]=true;
				}
			}
			putchar('\n');
		}
	}
}
