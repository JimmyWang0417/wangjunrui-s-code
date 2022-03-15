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
const int N=1e5+5,mod=19961993,limit=1e5;
const int prime[]= {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281};
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
inline int quickpow(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1)
			res=times(res,a);
		a=times(a,a);
		b>>=1;
	}
	return res;
}
struct node
{
	int a[65];
	node(int val=1)
	{
		memset(a,0,sizeof(a));
		for(int i=0; i<60; ++i)
			if(val%prime[i]==0)
			{
				int &cnt=a[i];
				while(val%prime[i]==0)
				{
					val/=prime[i];
					++cnt;
				}
			}
	}
	inline void operator +=(const node &rhs)
	{
		for(int i=0; i<60; ++i)
			a[i]+=rhs.a[i];
	}
	inline void operator -=(const node &rhs)
	{
		for(int i=0; i<60; ++i)
			a[i]-=rhs.a[i];
	}
	inline node operator +(const node &rhs)const
	{
		node res;
		for(int i=0; i<60; ++i)
			res.a[i]=a[i]+rhs.a[i];
		return res;
	}
	inline node operator -(const node &rhs)const
	{
		node res;
		for(int i=0; i<60; ++i)
			res.a[i]=a[i]-rhs.a[i];
		return res;
	}
	inline int calc()
	{
		int res=1;
		for(int i=0; i<60; ++i)
			if(a[i])
				res=times(res,times(quickpow(prime[i],a[i]-1),prime[i]-1));
		return res;
	}
	inline void print()
	{
		for(int i=0; i<60; ++i)
			printf("%d ",a[i]);
		putchar('\n');
	}
} a[N],c[N];
inline void updateadd(int pos,node val)
{
	for(int i=pos; i<=limit; i+=lowbit(i))
		c[i]+=val;
}
inline void updatemul(int pos,node val)
{
	for(int i=pos; i<=limit; i+=lowbit(i))
		c[i]-=val;
}
inline node query(int pos)
{
	node res;
	for(int i=pos; i; i-=lowbit(i))
		res+=c[i];
	return res;
}
signed main()
{
//	(a[1]+a[2]+a[3]+a[4]+a[5]+a[6]).print();
//	cout<<(a[1]+a[2]+a[3]+a[4]+a[5]+a[6]).calc()<<endl;
//	cout<<(a[1]+a[2]+a[3]+a[4]+a[5]+a[6]).a[1]<<endl;
//	cout<<quickpow(prime[1],(a[1]+a[2]+a[3]+a[4]+a[5]+a[6]).a[1])<<endl;
	for(int i=1; i<=1e5; ++i)
	{
		updateadd(i,a[i]=node(3));
	}
	int T;
	read(T);
	while(T--)
	{
		int opt;
		read(opt);
		if(opt==0)
		{
			int l,r;
			read(l,r);
//			query(r);
//			query(l-1);
//			(query(r)-query(l-1)).print();
			printf("%d\n",(query(r)-query(l-1)).calc());
		}
		else if(opt==1)
		{
			int pos,val;
			read(pos,val);
			updatemul(pos,a[pos]);
			updateadd(pos,a[pos]=node(val));
		}
	}
	return 0;
}


