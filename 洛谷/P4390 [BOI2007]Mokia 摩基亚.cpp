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
const int N=160000*4+10000+5;
int S;
struct node
{
	int x,y,ans,id,tag;
	inline bool operator <(const node&rhs)const
	{
		return x==rhs.x?y<rhs.y:x<rhs.x;
	}
} a[N],b[N];
int c[(int)2e6+5];
inline void update(int pos,int val)
{
	for(re int i=pos; i<=S; i+=lowbit(i))
		c[i]+=val;
}
inline int query(int pos)
{
	int res=0;
	for(re int i=pos; i; i-=lowbit(i))
		res+=c[i];
	return res;
}
inline void clear(int pos)
{
	for(re int i=pos; i<=S; i+=lowbit(i))
		if(c[i])
			c[i]=0;
		else
			return;
}
inline void cdq(int l,int r)
{
	if(l==r)
		return;
	int mid=(l+r)>>1;
	cdq(l,mid),cdq(mid+1,r);
	int i=l,j=mid+1,top=l-1;
	while(j<=r)
	{
		while(i<=mid&&(a[i].x<a[j].x||(a[i].x==a[j].x&&a[i].y<=a[j].y)))
		{
			if(!a[i].id)
				update(a[i].y,a[i].ans);
			b[++top]=a[i];
			++i;
		}
		if(a[j].id)
			a[j].ans+=query(a[j].y);
		b[++top]=a[j];
		++j;
	}
	while(i<=mid)
		b[++top]=a[i++];
	assert(top==r);
	for(i=l; i<=r; ++i)
	{
		a[i]=b[i];
		clear(a[i].y);
	}
//	for(re int i=l; i<=r; ++i)
//		printf("x=%d y=%d id=%d ans=%d\n",a[i].x,a[i].y,a[i].id,a[i].ans);
//	std::sort(a+l,a+r+1);
}
int ans[N];
signed main()
{
	int opt,tim=0,id=0;
	while(1)
	{
		read(opt);
		if(!opt)
		{
			read(S);
			++S;
		}
		else if(opt==1)
		{
			++tim;
			read(a[tim].x,a[tim].y,a[tim].ans);
			++a[tim].x,++a[tim].y;
		}
		else if(opt==2)
		{
			int x1,y1,x2,y2;
			read(x1,y1,x2,y2);
			a[++tim].x=x2+1,a[tim].y=y2+1,a[tim].tag=1,a[tim].id=++id;
			a[++tim].x=x1,a[tim].y=y1,a[tim].tag=1,a[tim].id=id;
			a[++tim].x=x1,a[tim].y=y2+1,a[tim].tag=-1,a[tim].id=id;
			a[++tim].x=x2+1,a[tim].y=y1,a[tim].tag=-1,a[tim].id=id;
		}
		else break;
	}
	cdq(1,tim);
//	for(re int i=1; i<=tim; ++i)
//		printf("x=%d y=%d id=%d ans=%d\n",a[i].x,a[i].y,a[i].id,a[i].ans);
	for(re int i=1; i<=tim; ++i)
		ans[a[i].id]+=a[i].ans*a[i].tag;
	for(re int i=1; i<=id; ++i)
		printf("%d\n",ans[i]);
	return 0;
}

