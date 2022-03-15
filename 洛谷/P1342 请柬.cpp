#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
const int MAXN=1000000+5;
const int inf=2147483647;
int m,n,sx=1,num1,num2;
struct line
{
	int from,to,dis;
} d[MAXN],f[MAXN];
int head1[MAXN],head2[MAXN];
bool inq[MAXN];
int dis[MAXN];
long long ans;
int r()
{
	int f=1,p=0;
	char c=getchar();
	while(c>'9'||c<'0')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		p=p*10+c-'0';
		c=getchar();
	}
	return f*p;
}
void add(int x,int y,int v)
{
	d[++num1].to=y;
	d[num1].from=head1[x];
	head1[x]=num1;
	d[num1].dis=v;
	f[++num2].to=x;
	f[num2].from=head2[y];
	head2[y]=num2;
	f[num2].dis=v;
}
void spfa1()
{
	deque <int> q;
	q.push_front(sx);
	fill(dis+2,dis+n+1,inf);
	while(!q.empty())
	{
		int x=q.front();
		q.pop_front();
		inq[x]=0;
		for(int k=head1[x]; k; k=d[k].from)
		{
			int v=d[k].to,w=d[k].dis;
			if(w+dis[x]<dis[v])
			{
				dis[v]=w+dis[x];
				if(!inq[v])
				{
					if(q.empty()||dis[v]<dis[q.front()]) q.push_front(v);
					else q.push_back(v);
					inq[v]=1;
				}
			}
		}
	}
	for(int i=2; i<=n; i++)
		ans+=dis[i];
}
void spfa2()
{
	deque <int> t;
	t.push_front(sx);
	fill(dis+2,dis+n+1,inf);
	while(!t.empty())
	{
		int x=t.front();
		t.pop_front();
		inq[x]=0;
		for(int k=head2[x]; k; k=f[k].from)
		{
			int v=f[k].to,w=f[k].dis;
			if(w+dis[x]<dis[v])
			{
				dis[v]=w+dis[x];
				if(!inq[v])
				{
					if(t.empty()||dis[v]<dis[t.front()]) t.push_front(v);
					else t.push_back(v);
					inq[v]=1;
				}
			}
		}
	}
	for(int i=2; i<=n; i++)
		ans+=dis[i];
}
int main()
{
	n=r();
	m=r();
	for(int i=1; i<=m; i++)
	{
		int x,y,z;
		x=r();
		y=r();
		z=r();
		add(x,y,z);
	}
	spfa1();
	spfa2();
	printf("%lld",ans);
	return 0;
}
