#include <bits/stdc++.h>
#define lowbit(x) (x&(-x))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
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
template<typename T>
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=1e5+5,mod=1e9+7;
struct Matrix
{
	ll g[26][26];
	Matrix(int val=0)
	{
		memset(g,val,sizeof(g));
	}
	inline Matrix operator *(const Matrix &rhs)const
	{
		Matrix ans=Matrix();
		for(re int i=0; i<26; ++i)
			for(re int j=0; j<26; ++j)
				for(re int k=0; k<26; ++k)
					(ans.g[i][j]+=g[i][k]*rhs.g[k][j]%mod)%=mod;
		return ans;
	}
	inline Matrix operator ^(ll power)const
	{
		Matrix ans=Matrix(),a=(*this);
		for(re int i=0; i<26; ++i)
			ans.g[i][i]=1;
		while(power)
		{
			if(power&1)
				ans=ans*a;
			a=a*a;
			power>>=1;
		}
		return ans;
	}
	inline void print()
	{
		for(re int i=0; i<26; ++i)
		{
			for(re int j=0; j<26; ++j)
				printf(" %lld",g[i][j]);
			putchar('\n');
		}
	}
} a;
char str[N];
signed main()
{
	for(re int i=0; i<26; ++i)
		for(re int j=0; j<26; ++j)
			a.g[i][j]=1;
	ll n;
	read(n);
	scanf("%s",str+1);
	int len=(int)strlen(str+1);
	for(re int i=1; i<len; ++i)
		a.g[str[i]-'a'][str[i+1]-'a']=0;
	a=a^(n-1);
//	a.print();
	ll ans=0;
	for(re int i=0; i<26; ++i)
		for(re int j=0; j<26; ++j)
			(ans+=a.g[i][j])%=mod;
	printf("%lld\n",ans);
	return 0;
}


