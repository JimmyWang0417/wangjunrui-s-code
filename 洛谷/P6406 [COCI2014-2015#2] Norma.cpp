#include <bits/stdc++.h>
#define int ll
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
const int N=5e5+5;
const int INF=0x7fffffff;
const int mod=1e9;
int n,a[N];
ll sum1[N],size1[N],sum2[N],size2[N],sum3[N],size3[N],sum4[N],size4[N];
ll ans=0;
inline void cdq(int l,int r)
{
	if(l==r)
	{
		(ans+=a[l]*a[l]%mod)%=mod;
		return;
	}
	int mid=(l+r)>>1;
	cdq(l,mid),cdq(mid+1,r);
	sum1[mid]=size1[mid]=sum2[mid]=size2[mid]=sum3[mid]=size3[mid]=sum4[mid]=size4[mid]=0;
	int minn=INF,maxx=~INF;
	for(int i=mid+1; i<=r; ++i)
	{
		minn=min(minn,a[i]),maxx=max(maxx,a[i]);
		sum1[i]=(sum1[i-1]+(i-mid))%mod,size1[i]=(size1[i-1]+1)%mod;
		sum2[i]=(sum2[i-1]+(ll)minn*(i-mid)%mod)%mod,size2[i]=(size2[i-1]+minn)%mod;
		sum3[i]=(sum3[i-1]+(ll)maxx*(i-mid)%mod)%mod,size3[i]=(size3[i-1]+maxx)%mod;
		sum4[i]=(sum4[i-1]+(ll)minn*maxx%mod*(i-mid)%mod)%mod,size4[i]=(size4[i-1]+(ll)minn*maxx%mod)%mod;
	}
	minn=INF,maxx=~INF;
	int j=mid,k=mid;
//	printf("%d %d\n",l,r);
	for(int i=mid; i>=l; --i)
	{
		minn=min(minn,a[i]),maxx=max(maxx,a[i]);
		while(j<r&&minn<=a[j+1])
			++j;
		while(k<r&&maxx>=a[k+1])
			++k;
//		printf("%d %d %d  %d %d\n",i,j,k,minl,maxl);
//		printf("%d\n",(sum3[j])+(size3[j])*(mid-i+1)%mod);
		int u=min(j,k),v=max(j,k);
		if(u>mid)
			(ans+=(sum1[u]+size1[u]*(mid-i+1)%mod)*maxx%mod*minn%mod)%=mod;
		if(u<j)
			(ans+=((sum3[j]-sum3[u])+(size3[j]-size3[u])*(mid-i+1)%mod)*minn%mod)%=mod;
		if(u<k)
			(ans+=((sum2[k]-sum2[u])+(size2[k]-size2[u])*(mid-i+1)%mod)*maxx%mod)%=mod;
		if(v<r)
			(ans+=(sum4[r]-sum4[v])+(size4[r]-size4[v])*(mid-i+1)%mod)%=mod;
	}
}
signed main()
{
	read(n);
	for(int i=1; i<=n; ++i)
		read(a[i]);
	cdq(1,n);
	printf("%lld\n",(ans+mod)%mod);
	return 0;
}

