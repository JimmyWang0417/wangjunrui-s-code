#include<cstdio>
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
priority_queue<pair<int, int>,vector<pair<int, int> >,greater<pair<int, int> > >q;
const int N=100010;
int ans[N],a[N],b[N],n;
int main()
{
	read(n);
	for(re int i=1; i<=n; i++)
		read(a[i]);
	for(re int i=1; i<=n; i++)
	{
		read(b[i]);
		ans[i]=1;
		q.push(make_pair(a[1]+b[i],i));
	}
	for(re int i=1; i<=n; i++)
	{
		printf("%d ",q.top().first);
		q.push(make_pair(a[++ans[q.top().second]]+b[q.top().second],q.top().second));
		q.pop();
	}
	putchar('\n');
	return 0;
}

