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
const int N=3e5+5;
ll X[N],Y[N];
int n,m,t[N];
ll f[N],g[N],h[N],L[N],R[N],sum[N];
int q[N],top;
inline bool check(int i,int j,int k)
{
	return (X[j]-X[i])*(Y[k]-Y[i])>=(X[k]-X[i])*(Y[j]-Y[i]);
}
inline void solve(ll *dp)
{
	dp[0]=0;
	X[0]=0;
	Y[0]=0;
	q[top=1]=0;
	for(int i=1; i<=n; ++i)
	{
		while(top>1&&Y[q[top]]-X[q[top]]*2*i<=Y[q[top-1]]-X[q[top-1]]*2*i)
			--top;
//		printf("%d\n",Y[q[top]]-X[q[top]]*2*i-sum[i]+(ll)i*i+i);
		dp[i]=max(dp[i-1],Y[q[top]]-X[q[top]]*2*i-sum[i]+(ll)i*i+i);
		X[i]=i;
		Y[i]=dp[i]+(ll)i*i-i+sum[i];
		while(top>1&&check(q[top-1],q[top],i))
			--top;
		q[++top]=i;
	}
}
inline void solve(int l,int r)
{
	if(l==r)
	{
		h[l]=max(h[l],f[l-1]+g[l+1]+2-t[l]);
		return;
	}
	int mid=(l+r)>>1;
	X[l-1]=l-1;
	Y[l-1]=f[l-1]+(ll)(l-1)*(l-1)-(l-1)+sum[l-1];
	q[top=1]=l-1;
	for(int i=l; i<mid; ++i)
	{
		X[i]=i;
		Y[i]=f[i]+(ll)i*i-i+sum[i];
		while(top>1&&check(q[top-1],q[top],i))
			--top;
		q[++top]=i;
	}
	for(int i=mid+1; i<=r; ++i)
	{
		while(top>1&&Y[q[top]]-X[q[top]]*2*i<=Y[q[top-1]]-X[q[top-1]]*2*i)
			--top;
		R[i]=Y[q[top]]-X[q[top]]*2*i-sum[i]+(ll)i*i+i;
	}
	for(int i=l; i<=mid; ++i)
		if(i!=l+r-i)
			swap(t[i],t[l+r-i]);
	if((r-l+1)&1)
		--mid;
	for(int i=l; i<=r; ++i)
		sum[i]=sum[i-1]+t[i];
	X[l-1]=l-1;
	Y[l-1]=g[r+1]+(ll)(l-1)*(l-1)-(l-1)+sum[l-1];
	q[top=1]=l-1;
	for(int i=l; i<mid; ++i)
	{
		X[i]=i;
		Y[i]=g[l+r-i]+(ll)i*i-i+sum[i];
		while(top>1&&check(q[top-1],q[top],i))
			--top;
		q[++top]=i;
	}
	for(int i=mid+1; i<=r; ++i)
	{
		while(top>1&&Y[q[top]]-X[q[top]]*2*i<=Y[q[top-1]]-X[q[top-1]]*2*i)
			--top;
		L[l+r-i]=Y[q[top]]-X[q[top]]*2*i-sum[i]+(ll)i*i+i;
	}
	for(int i=l; i<=mid; ++i)
		if(i!=l+r-i)
			swap(t[i],t[l+r-i]);
	mid=(l+r)>>1;
	for(int i=l; i<mid; ++i)
		L[i]+=f[i-1];
	for(int i=mid+1; i<=r; ++i)
		R[i]+=g[i+1];
	for(int i=l; i<=r; ++i)
		sum[i]=sum[i-1]+t[i];
	for(int i=l+1; i<=mid; ++i)
		L[i]=max(L[i],L[i-1]);
	for(int i=r-1; i>mid; --i)
		R[i]=max(R[i],R[i+1]);
	for(int i=l; i<=mid; ++i)
		h[i]=max(h[i],L[i]);
	for(int i=mid+1; i<=r; ++i)
		h[i]=max(h[i],R[i]);
	solve(l,mid);
	solve(mid+1,r);
}
signed main()
{
	freopen("score.in","r",stdin),freopen("score.out","w",stdout);
	read(n);
	for(int i=1; i<=n; ++i)
	{
		read(t[i]);
		t[i]=t[i]<<1;
	}
	for(int i=1; i<=n; ++i)
		sum[i]=sum[i-1]+t[i];
	solve(f);
	reverse(t+1,t+1+n);
	for(int i=1; i<=n; ++i)
		sum[i]=sum[i-1]+t[i];
	solve(g);
	reverse(t+1,t+1+n);
	reverse(g+1,g+1+n);
	clear(h,1,n,~0x3f);
	for(int i=1; i<=n; ++i)
		sum[i]=sum[i-1]+t[i];
//	for(int i=1; i<=n; ++i)
//		printf(" %lld %lld\n",f[i],g[i]);
	solve(1,n);
//	for(int i=1; i<=n; ++i)
//		printf("%lld %lld\n",h[i],t[i]);
	read(m);
	while(m--)
	{
		int p,x;
		read(p,x);
		x<<=1;
		printf("%lld\n",max(f[p-1]+g[p+1],h[p]+t[p]-x)/2);
	}
	return 0;
}

