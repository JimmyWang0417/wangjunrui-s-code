#include <cstdio>
#define lowbit(x) (x&(-x)) 
#define re register
#define ll long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
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
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
const int N=2048+5;
int n,m;
ll c[4][N][N];
inline void update(int x,int y,int val)
{
	for(re int i=x; i<=n; i+=lowbit(i))
		for(re int j=y; j<=m; j+=lowbit(j))
		{
			c[0][i][j]+=val;
			c[1][i][j]+=x*val;
			c[2][i][j]+=y*val;
			c[3][i][j]+=x*y*val;
		}
}
inline ll query(int x,int y)
{
	ll res=0;
	for(re int i=x; i; i-=lowbit(i))
		for(re int j=y; j; j-=lowbit(j))
			res+=c[0][i][j]*(x+1)*(y+1)-c[1][i][j]*(y+1)-c[2][i][j]*(x+1)+c[3][i][j];
	return res;
}
signed main()
{
	read(n,m);
	int opt;
	while(scanf("%d",&opt)!=EOF)
	{
		if(opt==1)
		{
			int x1,y1,x2,y2,val;
			read(x1,y1,x2,y2,val);
			update(x1,y1,val);
			update(x2+1,y1,-val);
			update(x1,y2+1,-val);
			update(x2+1,y2+1,val);
		}
		else
		{
			int x1,y1,x2,y2;
			read(x1,y1,x2,y2);
			ll ans=query(x2,y2)-query(x1-1,y2)-query(x2,y1-1)+query(x1-1,y1-1);
			printf("%lld\n",ans);
		}
	}
	return 0;
}

