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
const int N=2e5+5;
int n,m;
struct Queue
{
	int x,y,k,id;
	bool type;
} q[N*2],q1[N*2],q2[N*2];
int ans[N];
using std::vector;
int c[N];
inline void update(int pos,int val)
{
	for(re int i=pos; i<=n; i+=lowbit(i))
		c[i]+=val;
}
inline int query(int pos)
{
	int res=0;
	for(re int i=pos; i; i-=lowbit(i))
		res+=c[i];
	return res;
}
inline int query(int l,int r)
{
	return query(r)-query(l-1);
}
inline void clear(int pos)
{
	for(re int i=pos; i<=n; i+=lowbit(i))
		if(c[i])
			c[i]=0;
		else
			return;
}
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
//	printf("%d %d:\n",l,r);
	for(re int i=ql; i<=qr; ++i)
	{
//		printf("%d %d %d %d %d\n",q[i].type,q[i].x,q[i].y,q[i].k,q[i].id);
		if(q[i].type)
		{
			int cnt=query(q[i].x,q[i].y);
			if(q[i].k<=cnt)
				q1[++cnt1]=q[i];
			else
			{
				q[i].k-=cnt;
				q2[++cnt2]=q[i];
			}
		}
		else
		{
			if(q[i].y<=mid)
			{
				q1[++cnt1]=q[i];
				update(q[i].x,1);
			}
			else
				q2[++cnt2]=q[i];
		}
	}
	for(re int i=1; i<=cnt1; ++i)
		if(!q1[i].type)
			clear(q1[i].x);
	for(re int i=1; i<=cnt1; ++i)
		q[i+ql-1]=q1[i];
	for(re int i=1; i<=cnt2; ++i)
		q[i+ql+cnt1-1]=q2[i];
	solve(ql,ql+cnt1-1,l,mid),solve(ql+cnt1,qr,mid+1,r);
}
signed main()
{
	read(n,m);
	for(re int i=1; i<=n; ++i)
	{
		read(q[i].y);
		q[i].x=i;
		q[i].type=0;
	}
//	for(auto u:q)
//		printf("%d %d %d %d %d\n",u.type,u.x,u.y,u.k,u.id);
	int cnt=n;
	for(re int i=1; i<=m; ++i)
	{
		++cnt;
		read(q[cnt].x,q[cnt].y,q[cnt].k),q[cnt].type=1;
		q[cnt].id=i;
	}
	solve(1,cnt,-1e9 ,1e9);
	for(re int i=1; i<=m; ++i)
		printf("%d\n",ans[i]);
	return 0;
}


