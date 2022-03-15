#include<cstdio>
#include<cctype>
#include<cstring>
#define re register
#define ll long long
using namespace std;
const int N=1e7+10,mod=1e9+7;
struct matrix
{
	int n,m,g[5][5];
	inline void init(int _n,int _m)
	{
		memset(g,0,sizeof(g));
		n=_n;
		m=_m;
	}
	inline matrix operator *(const matrix &b)
	{
		matrix res;
		res.init(n,b.m);
		for(re int i=1; i<=res.n; i++)
			for(re int j=1; j<=res.m; j++)
				for(re int k=1; k<=b.n; k++)
					res.g[i][j]=(res.g[i][j]+1ll*g[i][k]*b.g[k][j])%mod;
		return res;
	}
	template<typename T>
	inline matrix operator ^ (T b)
	{
		matrix res,a=(*this);
		res.init(4,4);
		for(re int i=1; i<=4; i++)
			res.g[i][i]=1;
		while(b)
		{
			if(b&1)
				res=res*a;
			a=a*a;
			b>>=1;
		}
		return res;
	}
	inline void print()
	{
		for(re int i=1; i<=n; i++)
		{
			for(re int j=1; j<=m; j++)
				printf("%d ",g[i][j]);
			putchar('\n');
		}
		return;
	}
} a,b,f;
int n;
char s[5010];
int main()
{
	a.init(1,4);
	a.g[1][4]=1;
	b.init(4,4);
	b.g[1][1]=2;
	b.g[2][1]=b.g[2][2]=1;
	b.g[3][2]=2,b.g[3][3]=1;
	b.g[4][3]=b.g[4][4]=1;
	f.init(4,4);
	for(re int i=1; i<=4; i++)
		f.g[i][i]=1;
	scanf("%s",s+1);
	for(re int i=1; s[i]; i++)
		f=(f^10)*(b^((int)s[i]-'0'));
	printf("%d\n",(a*f).g[1][1]);
	return 0;
}

