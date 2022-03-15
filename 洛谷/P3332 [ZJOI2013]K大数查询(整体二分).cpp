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
inline void clear(T*a,int l,int r,int val)
{
	memset(&a[l],val,sizeof(T)*(r-l+1));
}
const int N=1e5+5;
int n,m;
ll c1[N],c2[N];
inline void update(int pos,int val)
{
	for(re int i=pos; i<=n; i+=lowbit(i))
	{
		c1[i]+=val;
		c2[i]+=(ll)pos*val;
	}
}
inline void update(int l,int r,int val)
{
	update(l,val);
	update(r+1,-val);
}
inline ll query(int pos)
{
	ll res=0;
	for(re int i=pos; i; i-=lowbit(i))
		res+=(pos+1)*c1[i]-c2[i];
	return res;
}
inline ll query(int l,int r)
{
	return query(r)-query(l-1);
}
inline void clear(int pos)
{
	for(re int i=pos; i<=n; i+=lowbit(i))
		if(c1[i]||c2[i])
			c1[i]=c2[i]=0;
		else
			return;
}
inline void clear(int l,int r)
{
	clear(l);
	clear(r+1);
}
struct Queue
{
	int type,l,r,id;
	ll c;
} q[N],q1[N],q2[N];
int ans[N];
inline void solve(int ql,int qr,int l,int r)
{
	if(ql>qr)
		return;
	if(l==r)
	{
		for(re int i=ql; i<=qr; ++i)
			ans[q[i].id]=l;
		return;
	}
	int mid=(l+r)>>1;
	int cnt1=0,cnt2=0;
//	printf("%d %d %d\n",l,r,mid);
	for(re int i=ql; i<=qr; ++i)
	{
		if(q[i].type==1)
		{
			if(q[i].c<=mid)
				q1[++cnt1]=q[i];
			else
			{
				q2[++cnt2]=q[i];
				update(q[i].l,q[i].r,1);
			}
		}
		else if(q[i].type==2)
		{
			ll cnt=query(q[i].l,q[i].r);
			if(q[i].c>cnt)
			{
				q[i].c-=cnt;
				q1[++cnt1]=q[i];
			}
			else
				q2[++cnt2]=q[i];
		}
	}
	for(re int i=1; i<=cnt2; ++i)
		if(q2[i].type==1)
			clear(q2[i].l,q2[i].r);
//	memset(c1,0,sizeof(c1));
//	memset(c2,0,sizeof(c2));
	for(re int i=1; i<=cnt1; ++i)
		q[ql+i-1]=q1[i];
	for(re int i=1; i<=cnt2; ++i)
		q[ql+cnt1+i-1]=q2[i];
	solve(ql,ql+cnt1-1,l,mid),solve(ql+cnt1,qr,mid+1,r);
}
signed main()
{
	read(n,m);
	int tim=0;
	for(re int i=1; i<=m; ++i)
	{
		read(q[i].type,q[i].l,q[i].r,q[i].c);
		if(q[i].type==2)
			q[i].id=++tim;
	}
	solve(1,m,-n,n);
	for(re int i=1; i<=tim; ++i)
		printf("%d\n",ans[i]);
	return 0;
}


