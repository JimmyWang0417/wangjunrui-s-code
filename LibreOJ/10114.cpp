#include<cstdio>
#define re register
using namespace std;
inline int read()
{
	char s=getchar();
	bool f=false;
	int x=0;
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
	return f?-x:x;
}
const int N=15e3+10,M=32e3+10;
struct node
{
	int x,y;
} p[N];
int c[M-1],ans[M-1],n;
inline int lowbit(int x)
{
	return x&(-x);
}
inline void update(int x,int y)
{
	for(; x<=M; x+=lowbit(x))
		c[x]+=y;
}
inline int sum(int x)
{
	int answer=0;
	for(; x; x-=lowbit(x))
		answer+=c[x];
	return answer;
}
int main()
{
	n=read();
	for(re int i=1; i<=n; i++)
	{
		p[i].x=read();
		p[i].y=read();
	}
	for(re int i=1; i<=n; i++)
	{
		ans[sum(p[i].x+1)]++;
		update(p[i].x+1,1);
	}
	for(re int i=0; i<n; i++)
		printf("%d\n",ans[i]);
	return 0;
}
