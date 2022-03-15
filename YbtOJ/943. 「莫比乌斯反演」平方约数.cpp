#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
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
inline void clear(T*array,int l,int r,int val)
{
	memset(&array[l],val,sizeof(T)*(r-l+1));
}
using namespace std;
const int N=2e5+5,mod=1<<30;
inline int times(int x,int y)
{
	return (int)((ll)x*y%mod);
}
inline void add(int &x,int y)
{
	x+=y;
	if(x>=mod)
		x-=mod;
}
inline void minu(int &x,int y)
{
	x-=y;
	if(x<0)
		x+=mod;
}
int prime[N],tot,mul[N],s[N],h[N],e[N];
bool vis[N];
inline void getprime(int n)
{
	s[1]=h[1]=1;
	mul[1]=1;
	for(int i=2; i<=n; ++i)
	{
		if(!vis[i])
		{
			prime[++tot]=i;
			mul[i]=-1;
			s[i]=2,h[i]=3,e[i]=1;
		}
		for(int j=1; j<=tot; ++j)
		{
			if(prime[j]*i>n)
				break;
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
			{
				mul[i*prime[j]]=0;
				e[i*prime[j]]=e[i]+1;
				s[i*prime[j]]=s[i]/(e[i]+1)*(e[i*prime[j]]+1);
				h[i*prime[j]]=h[i]/(e[i]*2+1)*(e[i*prime[j]]*2+1);
				break;
			}
			else
			{
				mul[i*prime[j]]=-mul[i];
				e[i*prime[j]]=1;
				s[i*prime[j]]=s[i]*2;
				h[i*prime[j]]=h[i]*3;
			}
		}
	}
}
int block,belong[N];
struct Query
{
	int l,r,id;
	inline bool operator <(const Query &rhs)const
	{
		return (belong[l]==belong[rhs.l]?(belong[l]&1?r<rhs.r:r>rhs.r):l<rhs.l);
	}
} q[N];
int ans1[N],ans2[N];
int ans,answer[N];
int pri[N],cnt;
signed main()
{
	freopen("math.in","r",stdin);
	freopen("math.out","w",stdout);
	getprime(2e5);
//	for(int i=1; i<=20; ++i)
//		printf("%d:%d %d %d\n",i,mul[i],s[i],h[i]);
	int Q;
	read(Q);
	block=(int)(2e5/sqrt(Q));
	for(int i=1; i<=2e5; ++i)
		belong[i]=(i-1)/block+1;
	for(int i=1; i<=Q; ++i)
	{
		read(q[i].l,q[i].r);
		q[i].id=i;
	}
	sort(q+1,q+1+Q);
	int n=0,m=0;
	for(int now=1; now<=Q; ++now)
	{
		while(n<q[now].l)
		{
			++n;
			cnt=0;
			int val=n;
			for(int i=1; prime[i]*prime[i]<=val; ++i)
				if(val%prime[i]==0)
				{
					pri[++cnt]=prime[i];
					while(val%prime[i]==0)
						val/=prime[i];
				}
			if(val>1)
				pri[++cnt]=val;
//			printf("%d %d:",n,cnt);
			for(int S=0; S<(1<<cnt); ++S)
			{
				val=1;
				for(int i=0; i<cnt; ++i)
					if((S>>i)&1)
						val=val*pri[i+1];
//				printf("%d\n",val);
				ans=((ans-mul[val]*times(ans1[val],ans2[val]))%mod+mod)%mod;
				add(ans1[val],times(h[n],s[n/val]));
				ans=((ans+mul[val]*times(ans1[val],ans2[val]))%mod+mod)%mod;
			}
		}
		while(n>q[now].l)
		{
			cnt=0;
			int val=n;
			for(int i=1; prime[i]*prime[i]<=val; ++i)
				if(val%prime[i]==0)
				{
					pri[++cnt]=prime[i];
					while(val%prime[i]==0)
						val/=prime[i];
				}
			if(val>1)
				pri[++cnt]=val;
			for(int S=0; S<(1<<cnt); ++S)
			{
				val=1;
				for(int i=0; i<cnt; ++i)
					if((S>>i)&1)
						val=val*pri[i+1];
				ans=((ans-mul[val]*times(ans1[val],ans2[val]))%mod+mod)%mod;
				minu(ans1[val],times(h[n],s[n/val]));
				ans=((ans+mul[val]*times(ans1[val],ans2[val]))%mod+mod)%mod;
			}
			--n;
		}
		while(m<q[now].r)
		{
			++m;
			cnt=0;
			int val=m;
			for(int i=1; prime[i]*prime[i]<=val; ++i)
				if(val%prime[i]==0)
				{
					pri[++cnt]=prime[i];
					while(val%prime[i]==0)
						val/=prime[i];
				}
			if(val>1)
				pri[++cnt]=val;
			for(int S=0; S<(1<<cnt); ++S)
			{
				val=1;
				for(int i=0; i<cnt; ++i)
					if((S>>i)&1)
						val=val*pri[i+1];
				ans=((ans-mul[val]*times(ans1[val],ans2[val]))%mod+mod)%mod;
				add(ans2[val],times(h[m],s[m/val]));
				ans=((ans+mul[val]*times(ans1[val],ans2[val]))%mod+mod)%mod;
			}
		}
		while(m>q[now].r)
		{
			cnt=0;
			int val=m;
			for(int i=1; prime[i]*prime[i]<=val; ++i)
				if(val%prime[i]==0)
				{
					pri[++cnt]=prime[i];
					while(val%prime[i]==0)
						val/=prime[i];
				}
			if(val>1)
				pri[++cnt]=val;
			for(int S=0; S<(1<<cnt); ++S)
			{
				val=1;
				for(int i=0; i<cnt; ++i)
					if((S>>i)&1)
						val=val*pri[i+1];
				ans=((ans-mul[val]*times(ans1[val],ans2[val]))%mod+mod)%mod;
				minu(ans2[val],times(h[m],s[m/val]));
				ans=((ans+mul[val]*times(ans1[val],ans2[val]))%mod+mod)%mod;
			}
			--m;
		}
		answer[q[now].id]=ans;
	}
	ans=0;
	for(int i=1; i<=10; ++i)
		ans+=mul[i]*ans1[i]*ans2[i];
//	printf("%d\n",ans);
//	for(int i=100000; i<=130000; ++i)
//		printf("%d ",ans1[i]);
//	putchar('\n');
//	for(int i=100000; i<=130000; ++i)
//		printf("%d ",ans2[i]);
//	putchar('\n');
	for(int i=1; i<=Q; ++i)
		printf("%d\n",answer[i]);
	return 0;
}


