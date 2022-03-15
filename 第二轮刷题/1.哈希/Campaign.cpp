#include<cstdio>
#include<algorithm>
#define re register
#define ll long long
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
const int N=55;
int f[N][N][N][N],a[N][N],b[N][N],n,ans;
int main()
{
	//freopen("matrix.in","r",stdin),freopen("matrix.out","w",stdout);
	read(n);
	for(re int i=1; i<=n; i++)
		for(re int j=1; j<=n; j++)
			read(a[i][j]);
	for(re int i=1; i<=n; i++)
		for(re int j=1; j<=n; j++)
			read(b[i][j]);
	for(re int ax=n; ax>=1; ax--)
		for(re int ay=n; ay>=1; ay--)
			for(re int bx=n; bx>=1; bx--)
				for(re int by=n; by>=1; by--)
					if(a[ax][ay]==b[bx][by])
					{
						f[ax][ay][bx][by]=min(f[ax+1][ay][bx+1][by],min(f[ax+1][ay+1][bx+1][by+1],f[ax][ay+1][bx][by+1]))+1;
						ans=max(ans,f[ax][ay][bx][by]);
					}
	printf("%lld\n",ans);
	return 0;
}
