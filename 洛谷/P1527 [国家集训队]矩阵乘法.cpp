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
const int N=505;
int n,m,c[N][N];
inline void update(int x,int y,int val)
{
	for(re int i=x; i<=n; i+=lowbit(i))
		for(re int j=y; j<=n; j+=lowbit(j))
			c[i][j]+=val;
}
inline int query(int x,int y)
{
	int res=0;
	for(re int i=x; i; i-=lowbit(i))
		for(re int j=y; j; j-=lowbit(j))
			res+=c[i][j];
	return res;
}
inline int query(int x1,int y1,int x2,int y2)
{
	return query(x2,y2)-query(x1-1,y2)-query(x2,y1-1)+query(x1-1,y1-1);
}
inline void clear(int x,int y)
{
	for(re int i=x; i<=n; i+=lowbit(i))
		for(re int j=y; j<=n; j+=lowbit(j))
			if(c[i][j])
				c[i][j]=0;
			else
				break;
}
struct node
{
	int type,x1,y1,x2,y2,k,id;
} q[500*500+60000+5],q1[500*500+60000+5],q2[500*500+60000+5];
int ans[60000+5];
inline void solve(int ql,int qr,int l,int r)
{
	if(ql>qr)
		return;
	if(l==r)
	{
		for(re int i=ql; i<=qr; ++i)
			if(q[i].type==2)
				ans[q[i].id]=l;
		return;
	}
	int mid=(l+r)>>1,cnt1=0,cnt2=0;
//	printf("%d %d %d:\n",l,mid,r);
	for(re int i=ql; i<=qr; ++i)
	{
//		printf("%d %d %d %d %d %d %d\n",q[i].type,q[i].x1,q[i].y1,q[i].x2,q[i].y2,q[i].k,q[i].id);
		if(q[i].type==1)
		{
			if(q[i].k<=mid)
			{
				update(q[i].x1,q[i].y1,1);
				q1[++cnt1]=q[i];
			}
			else
				q2[++cnt2]=q[i];
		}
		else if(q[i].type==2)
		{
			int cnt=query(q[i].x1,q[i].y1,q[i].x2,q[i].y2);
//			printf(" %d\n",cnt);
			if(cnt>=q[i].k)
				q1[++cnt1]=q[i];
			else
			{
				q[i].k-=cnt;
				q2[++cnt2]=q[i];
			}
		}
	}
//	memset(c,0,sizeof(c));
	for(re int i=1; i<=cnt1; ++i)
		if(q1[i].type==1)
			clear(q1[i].x1,q1[i].y1);
	for(re int i=1; i<=cnt1; ++i)
		q[ql+i-1]=q1[i];
	for(re int i=1; i<=cnt2; ++i)
		q[ql+cnt1+i-1]=q2[i];
	solve(ql,ql+cnt1-1,l,mid),solve(ql+cnt1,qr,mid+1,r);
}
signed main()
{
	read(n,m);
	int cnt=0;
	for(re int i=1; i<=n; ++i)
		for(re int j=1; j<=n; ++j)
		{
			++cnt;
			q[cnt].type=1;
			q[cnt].x1=i;
			q[cnt].y1=j;
			read(q[cnt].k);
		}
	for(re int i=1; i<=m; ++i)
	{
		++cnt;
		q[cnt].type=2;
		read(q[cnt].x1,q[cnt].y1,q[cnt].x2,q[cnt].y2,q[cnt].k);
		q[cnt].id=i;
	}
	solve(1,cnt,0,1e9);
	for(re int i=1; i<=m; ++i)
		printf("%d\n",ans[i]);
	return 0;
}


