#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
const int N=3e6+10;
int n,sum,a[N],dis[N];
priority_queue<int>q;
int t[4];
int main()
{
	read(n);
	for(re int i=1; i<=n; i++)
		read(a[i]);
	for(re int i=1; i<=n; i++)
		dis[a[i]]++;
	for(re int i=1; i<=n; i++)
		if(dis[i]!=0)
			q.push(dis[i]);
	sum=0;
	while(!q.empty())
	{
		for(re int i=1; i<=3; i++)
		{
			if(q.empty())
			{
				printf("%d\n",sum);
				return 0;
			}
			t[i]=q.top();
			q.pop();
		}
		sum++;
		for(re int i=1; i<=3; i++)
			if(--t[i]!=0)
				q.push(t[i]);
		//printf("%d %d\n",sum,q.size());
	}
	printf("%d\n",sum);
	return 0;
}

