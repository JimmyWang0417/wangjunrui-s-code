#include<cstdio>
#include<algorithm>
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
	return;
}
const int mod=1e9+7;
int n,k,x;
long long f[2][2010];
int main()
{
	read(n);
	read(k);
	k--;
	f[0][0]=1;
	for(re int i=1; i<=n; i++)
	{
		read(x);
		fill(&f[i&1][0],&f[i&1][1<<k]+1,0);
		for(re int j=0; j<=1<<k; j++)
		{
			if(x!=2)
				f[i&1][j&1?2:min(j+2,1<<k)]=(f[i&1][j&1?2:min(j+2,1<<k)]+f[i&1^1][j])%mod;
			if(x!=4)
				f[i&1][min(j+1,1<<k)]=(f[i&1][min(j+1,1<<k)]+f[i&1^1][j])%mod;
		}
	}
	printf("%d\n",f[n&1][1<<k]%mod);
	return 0;
}

