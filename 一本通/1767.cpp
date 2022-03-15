#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
#define re register
#define ll long long
using namespace std;
namespace IO
{
	template<typename T>
	inline void read(T &x)
	{
		x=0;
		T f=1, ch=getchar();
		while (!isdigit(ch) && ch^'-') ch=getchar();
		if (ch=='-') f=-1, ch=getchar();
		while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
		x*=f;
	}

	char Out[25],*fe=Out;
	inline void flush()
	{
		fwrite(Out,1,fe-Out,stdout);
		fe=Out;
	}
	template<typename T>
	inline void write(T x)
	{
		if (!x) *fe++=48;
		if (x<0) *fe++='-', x=-x;
		T num=0, ch[20];
		while (x) ch[++num]=x%10+48, x/=10;
		while (num) *fe++=ch[num--];
		*fe++='\n';
	}
}
using namespace IO;
const int N=301,M=(1<<8)+10;
const ll INF=1ll<<60ll;
bool a[N];
int w[M],n,K;
ll f[N][N][M],g[2],c[M],ans=-INF;
int main()
{
	read(n);
	//printf("%d\n",n);
	read(K);
	for(re int i=1; i<=n; ++i)
		scanf("%1d",&a[i]);
	for(re int i=0; i<(1<<K); ++i)
	{
		read(c[i]);
		read(w[i]);
	}
	for(re int i=1; i<=n; ++i)
		for(re int j=i; j<=n; ++j)
			for(re int k=0; k<(1<<K); ++k)
				f[i][j][k]=-INF;
	for(re int i=n; i>=1; --i)
		for(re int j=i; j<=n; ++j)
		{
			if(i==j)
			{
				f[i][j][a[i]]=0;
				continue;
			}
			ll len=j-i;
			len%=K-1;
			if(!len)
				len=K-1;
			for(re int mid=j; mid>i; mid-=K-1)
				for(re int k=0; k<(1<<len); ++k)
				{
					f[i][j][k<<1]=max(f[i][j][k<<1],f[i][mid-1][k]+f[mid][j][0]);
					f[i][j][k<<1|1]=max(f[i][j][k<<1|1],f[i][mid-1][k]+f[mid][j][1]);
				}
			if(len==K-1)
			{
				g[0]=g[1]=-INF;
				for(re int k=0; k<(1<<K); ++k)
					g[c[k]]=max(g[c[k]],f[i][j][k]+w[k]);
				f[i][j][0]=g[0];
				f[i][j][1]=g[1];
			}
		}
	for(re int i=0; i<(1<<K); ++i)
		ans=max(ans,f[1][n][i]);
	write(ans);
	flush();
	return 0;
}
