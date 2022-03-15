#include<cstdio>
#include<cstring>
#include<iostream>
#include<map>
#include<algorithm>
#include<string>
using namespace std;
typedef long long ll;
int n,m,idx,id[10010][11];
char ch;
bool flag;
string str;
map<string,int>mp;
map<ll,int>exist;
int main()
{
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		mp.clear();
		idx=0;
		getchar();
		for(int i=1; i<=n; i++)
			for(int j=1; j<=m; j++)
			{
				str.clear();
				while(1)
				{
					ch=getchar();
					if(ch==','||ch=='\n'||ch=='\r'||ch==EOF)
						break;
					str.push_back(ch);
				}
				if(mp.count(str))id[i][j]=mp[str];
				else id[i][j]=mp[str]=++idx;
			}
		idx++;
		flag=false;
		for(int i=1; i<=m; i++)
			for(int j=1; j<i; j++)
			{
				exist.clear();
				for(int k=1; k<=n&&!flag; k++)
					if(exist.count((ll)id[k][i]*idx+id[k][j]))
					{
						printf("NO\n");
						printf("%d %d\n%d %d\n",exist[(ll)id[k][i]*idx+id[k][j]],k,j,i);
						flag=true;
					}
					else
						exist[(ll)id[k][i]*idx+id[k][j]]=k;
				if(flag)
					break;
			}
		if(!flag)
			printf("YES\n");
	}
	return 0;
}
