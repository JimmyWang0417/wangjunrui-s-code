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
const int N=1e5*3+5;
int n,m;
struct Queue
{
	int type,x,y,k,id;
} q[N],q1[N],q2[N];
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
int ans[N];
inline void solve(int ql,int qr,int l,int r)
{
	if(ql>qr)
		return;
	if(l==r)
	{
		for(re int i=ql; i<=qr; ++i)
			if(q[i].type==3)
				ans[q[i].id]=l;
		return;
	}
	int mid=(l+r)>>1;
	int cnt1=0,cnt2=0;
//	printf("%d %d %d\n",l,mid,r);
	for(re int i=ql; i<=qr; ++i)
	{
//		printf("%d %d %d %d %d\n",q[i].type,q[i].x,q[i].y,q[i].k,q[i].id);
		if(q[i].type==1)
		{
			if(q[i].y<=mid)
			{
				q1[++cnt1]=q[i];
				update(q[i].x,1);
			}
			else
				q2[++cnt2]=q[i];
		}
		else if(q[i].type==2)
		{
			if(q[i].y<=mid)
			{
				q1[++cnt1]=q[i];
				update(q[i].x,-1);
			}
			else
				q2[++cnt2]=q[i];
		}
		else
		{
			int cnt=query(q[i].x,q[i].y);
//			printf("cnt=%d\n",cnt);
			if(cnt>=q[i].k)
				q1[++cnt1]=q[i];
			else
			{
				q[i].k-=cnt;
				q2[++cnt2]=q[i];
			}
		}
	}
	for(re int i=1; i<=cnt1; ++i)
		if(q1[i].type<=2)
			clear(q1[i].x);
	for(re int i=1; i<=cnt1; ++i)
		q[i+ql-1]=q1[i];
	for(re int i=1; i<=cnt2; ++i)
		q[i+ql+cnt1-1]=q2[i];
//	putchar('\n');
	solve(ql,ql+cnt1-1,l,mid),solve(ql+cnt1,qr,mid+1,r);
}
int a[N];
signed main()
{
	read(n,m);
	int cnt=0;
	for(re int i=1; i<=n; ++i)
	{
		++cnt;
		read(a[i]);
		q[cnt].type=1,q[cnt].x=i,q[cnt].y=a[i];
	}
	int tim=0;
	for(re int i=1; i<=m; ++i)
	{
		char opt[3];
		scanf("%s",opt);
		++cnt;
		if(opt[0]=='Q')
		{
			read(q[cnt].x,q[cnt].y,q[cnt].k);
			q[cnt].type=3,q[cnt].id=++tim;
		}
		else if(opt[0]=='C')
		{
			int pos;
			read(pos);
			q[cnt].type=2,q[cnt].x=pos,q[cnt].y=a[pos];
			++cnt;
			q[cnt].type=1,q[cnt].x=pos,read(q[cnt].y),a[pos]=q[cnt].y;
		}
	}
	solve(1,cnt,0,1e9);
	for(re int i=1; i<=tim; ++i)
		printf("%d\n",ans[i]);
	return 0;
}


