#include <cstdio>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cctype>
#define re register
#define ll long long
using namespace std;
namespace IO
{
	const int SIZE=1<<20;
	char ibuf[SIZE],*iS,*iT;
#define gc() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),iS==iT?EOF:*iS++):*iS++)
	template<typename T>
	inline void read(T & x)
	{
		x=0;
		bool b=false;
		char ch=gc();
		while((ch<'0'&&ch>'9')&&ch^'-')
			ch=gc();
		if(ch=='-')
		{
			b=true;
			ch=gc();
		}
		while(ch>='0'&&ch<='9')
		{
			x=(x<<1)+(x<<3)+(ch^'0');
			ch=gc();
		}
		if(b)
			x=~x+1;
		return;
	}
	inline void readstr(char *s)
	{
		int len=0;
		char ch=(char)gc();
		while(!(ch>='A'&&ch<='Z'||ch>='a'&&ch<='z'))
			ch=(char)gc();
		while(ch>='A'&&ch<='Z'||ch>='a'&&ch<='z')
		{
			s[len++]=ch;
			ch=(char)gc();
		}
	}
#undef gc
	char Out[1<<20],*fe=Out,ch[25];
	int num=0;
	template<typename T>
	inline void write(T x)
	{
		if(!x)
			*fe++='0';
		if(x<0)
		{
			*fe++='-';
			x=-x;
		}
		while(x)
		{
			ch[++num]=x%10+'0';
			x/=10;
		}
		while(num)
			*fe++=ch[num--];
		*fe++='\n';
	}
	inline void flush()
	{
		fwrite(Out,1,fe-Out,stdout);
		fe=Out;
	}
}
using IO::read;
using IO::readstr;
using IO::write;
const int N=1e5+5,mod=917120411;
#define change(x) ((x)-'a')
struct Tree
{
	int l,r,size;
	unsigned int hash;
	int val,key;
} tree[N];
int cnt,root;
#define lc(x) tree[x].l
#define rc(x) tree[x].r
#define size(x) tree[x].size
unsigned int power[N];
inline int newnode(int val)
{
	tree[++cnt].val=val;
	tree[cnt].hash=val;
	tree[cnt].key=rand();
	tree[cnt].size=1;
	lc(cnt)=rc(cnt)=0;
	return cnt;
}
inline void pushup(int now)
{
	size(now)=size(lc(now))+size(rc(now))+1;
	tree[now].hash=(tree[lc(now)].hash+1ull*power[size(lc(now))]*tree[now].val+1ull*power[size(lc(now))+1]*tree[rc(now)].hash)%mod;
}
inline void split(int now,int nowsize,int &x,int &y)
{
	if(!now)
		x=y=0;
	else
	{
		if(nowsize>size(lc(now)))
		{
			x=now;
			split(rc(now),nowsize-size(lc(now))-1,rc(now),y);
		}
		else
		{
			y=now;
			split(lc(now),nowsize,x,lc(now));
		}
		pushup(now);
	}
}
inline int merge(int x,int y)
{
	if(!x||!y)
		return x|y;
	if(tree[x].key>tree[y].key)
	{
		rc(x)=merge(rc(x),y);
		pushup(x);
		return x;
	}
	else
	{
		lc(y)=merge(x,lc(y));
		pushup(y);
		return y;
	}
}
inline ll query(int pos,int len)
{
	int x,y,z;
	split(root,pos-1,x,y);
	split(y,len,y,z);
	ll ans=tree[y].hash;
	root=merge(x,merge(y,z));
	return ans;
}
int q,n;
char str[N];
int sta[N];
inline int build(char *str)
{
	int tp;
	sta[tp=n=1]=newnode(change(str[0]));
	for(re int i=1; str[i]; ++i)
	{
		int last=0,cur=newnode(change(str[i]));
		while(tp&&tree[cur].key>tree[sta[tp]].key)
		{
			last=sta[tp];
			pushup(sta[tp--]);
		}
		lc(cur)=last;
		if(tp)
		{
			rc(sta[tp])=cur;
			pushup(sta[tp]);
		}
		sta[++tp]=cur;
		++n;
	}
	while(tp)
		pushup(sta[tp--]);
	return sta[1];
}
int main()
{
	power[0]=1;
	for(re int i=1; i<=100000; ++i)
		power[i]=1ull*power[i-1]*30%mod;
	srand((unsigned int)time(0));
	readstr(str);
//	printf("%s\n",str);
	root=build(str);
//	print(root);
	read(q);
	while(q--)
	{
		char s[5];
		readstr(s);
		if(s[0]=='R')
		{
			int pos;
			read(pos),readstr(s);
			int x,y,z;
			split(root,pos-1,x,y);
			split(y,1,y,z);
			tree[y].hash=tree[y].val=change(s[0]);
			root=merge(x,merge(y,z));
		}
		else if(s[0]=='I')
		{
			int pos;
			read(pos),readstr(s);
			int x,y;
			split(root,pos,x,y);
			root=merge(merge(x,newnode(change(s[0]))),y);
			++n;
		}
		else if(s[0]=='Q')
		{
			int x,y;
			read(x),read(y);
			int l=0,r=min(n-x,n-y)+1,ans=0;
			while(l<=r)
			{
				int mid=(l+r)>>1;
				if(query(x,mid)==query(y,mid))
				{
					ans=mid;
					l=mid+1;
				}
				else r=mid-1;
			}
			write(ans);
		}
//		print(root);
	}
	IO::flush();
	return 0;
}
