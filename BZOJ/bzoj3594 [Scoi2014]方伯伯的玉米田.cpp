#include<cstdio>
#include<cstring>
#define re register
#define lowbit(x) ((x)&(-x))
#define max(x,y) ((x)>(y)?(x):(y))
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}
const int N=1e4+5,M=5505;
int n,m,maxx;
int h[N],c[M][505];
inline void update(int x,int yy,int val)
{
	for(; x<=maxx+m; x+=lowbit(x))
		for(re int y=yy; y<=m+1; y+=lowbit(y))
			c[x][y]=max(c[x][y],val);
}
inline int query(int x,int yy)
{
	int res=0;
	for(; x; x-=lowbit(x))
		for(re int y=yy; y; y-=lowbit(y))
			res=max(res,c[x][y]);
	return res;
}
int main()
{
	read(n);
	read(m);
	for(re int i=1; i<=n; ++i)
	{
		read(h[i]);
		maxx=max(maxx,h[i]);
	}
	int ans=0;
	for(re int i=1; i<=n; ++i)
		for(re int j=m; j>=0; --j)
		{
			int x=query(h[i]+j,j+1)+1;
			ans=max(ans,x);
			update(h[i]+j,j+1,x);
		}
	printf("%d\n",ans);
	return 0;
}
