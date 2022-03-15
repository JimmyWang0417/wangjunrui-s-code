#include<cstdio>
#include<algorithm>
#define re register
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
const int N=75,W=30*70+5;
int d[2][W][W],n,sum[N];
#define update(x,v) if((x)<0||(x)>(v))(x)=(v);
#define f(x,h) ((x)==0?(h):0)
struct node
{
	int h,w;
	inline bool operator <(const node &rhs)const
	{
		return h>rhs.h||h==rhs.h&&w>rhs.w;
	}
} book[N];
inline void solve()
{
	read(n);
	for(re int i=0; i<n; ++i)
	{
		read(book[i].h);
		read(book[i].w);
	}
	sort(book,book+n);
	for(re int i=1; i<=n; ++i)
		sum[i]=sum[i-1]+book[i-1].w;
	d[0][0][0]=0;
	re int t=0;
	for(re int i=0; i<n; ++i)
	{
		for(re int j=0; j<=sum[i+1]; ++j)
			for(re int k=0; k<=sum[i+1]-j; ++k)
				d[t^1][j][k]=-1;
		for(re int j=0; j<=sum[i]; ++j)
			for(re int k=0; k<=sum[i]-j; ++k)
				if(d[t][j][k]>=0&&k<=j+30&&j<=sum[i-1]-k-j+30)
				{
					update(d[t^1][j][k],d[t][j][k]);
					update(d[t^1][j+book[i].w][k],d[t][j][k]+f(j,book[i].h));
					update(d[t^1][j][k+book[i].w],d[t][j][k]+f(k,book[i].h));
				}
		t^=1;
	}
	int ans=-1;
	for(re int j=1; j<=sum[n]; ++j)
		for(re int k=1; k<=sum[n]-j; ++k)
			if(d[t][j][k]>=0&&k<=j+30&&j<=sum[n]-k-j+30)
			{
				int w=max(max(j,k),sum[n]-k-j),h=book[0].h+d[t][j][k];
				update(ans,w*h);
			}
	printf("%d\n",ans);
}
int main()
{
	int T;
	read(T);
	while(T--)
		solve();
}
