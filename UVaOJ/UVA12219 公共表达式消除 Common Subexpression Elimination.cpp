#include<cstdio>
#include<iostream>
#include<map>
#include<string>
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
	return;
}
const int N=1e5+10;
int T,kase,cnt,d[N];
char s[N*5],*p;
struct node
{
	string s;
	int x,l,r;
	inline bool operator < (const node &a)const
	{
		if(l!=a.l)
			return l<a.l;
		if(r!=a.r)
			return r<a.r;
		return x<a.x;
	}
} point[N];
map<node,int>ID;
inline int work()
{
	int id=cnt++;
	node &u=point[id];
	u.l=u.r=-1;
	u.s="";
	u.x=0;
	while(isalpha(*p))
	{
		u.x=u.x*27+(*p)-'a'+1;
		u.s.push_back(*p);
		p++;
	}
	if(*p=='(')
	{
		p++;
		u.l=work();
		p++;
		u.r=work();
		p++;
	}
	if(ID.count(u))
	{
		cnt--;
		return ID[u];
	}
	return ID[u]=id;
}
inline void print(int u)
{
	if(d[u]==kase)
		printf("%d",u+1);
	else
	{
		d[u]=kase;
		printf("%s",point[u].s.c_str());
		if(point[u].l!=-1)
		{
			putchar('(');
			print(point[u].l);
			putchar(',');
			print(point[u].r);
			putchar(')');
		}
	}
}
int main()
{
	read(T);
	for(kase=1;kase<=T;++kase)
	{
		ID.clear();
		cnt=0;
		scanf("%s",s);
		p=s;
		print(work());
		putchar('\n');
	}
}

