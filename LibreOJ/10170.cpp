#include<cstdio>
#include<cstring>
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
long long f[11][155][155],ans;
int num[155],s[155],n,K,s0;
inline void pre_pare()
{
	s0=0;
	ans=0;
	memset(f,0,sizeof(f));
	for(re int i=0,k; i<(1<<n); i++)
	{
		if(i&(i<<1))
			continue;
		k=0;
		for(re int j=0; j<n; j++)
			if(i&(1<<j))
				k++;
		s[++s0]=i;
		num[s0]=k;
	}
}
inline void dp()
{
	f[0][1][0]=1;
	for(re int i=1; i<=n; i++)
		for(re int j=1; j<=s0; j++)
			for(re int kk=0; kk<=K; kk++)
				if(kk>=num[j])
					for(re int t=1; t<=s0; t++)
						if(!(s[t]&s[j])&&!(s[t]&(s[j]<<1))&&!(s[t]&(s[j]>>1)))
							f[i][j][kk]+=f[i-1][t][kk-num[j]];
	for(re int i=1; i<=s0; i++)ans+=f[n][i][K];
	printf("%lld\n",ans);
}
int main()
{
	while(scanf("%d%d",&n,&K)==2)
	{
		pre_pare();
		dp();
	}
}

