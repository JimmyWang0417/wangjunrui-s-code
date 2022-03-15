#include<iostream>
#include<cstdio>
#define ll long long
#define re register
using namespace std;
const ll N=1e5+5;
char str[N];
int main()
{
	ios::sync_with_stdio(false);
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n,x;
		scanf("%d%d%s",&n,&x,str);
		int cnt=0,ans=0,maxn=0,minn=0;
		for(re int i=0; i<n; ++i)
		{
			if(str[i]=='0')
				++cnt;
			else cnt--;
			maxn=max(maxn,cnt);
			minn=min(minn,cnt);
		}
		if(cnt==0&&x>=minn&&x<=maxn)
		{
			printf("-1\n");
			continue;
		}
		else if(cnt==0)
		{
			printf("0\n");
			continue;
		}
		int now=0;
		for(re int i=0; i<n; ++i)
		{
			if((x-now)%cnt==0&&(x-now)/cnt>=0)
				ans++;
			if(str[i]=='0')
				now++;
			else
				now--;
		}
		printf("%d\n",ans);
	}
}

