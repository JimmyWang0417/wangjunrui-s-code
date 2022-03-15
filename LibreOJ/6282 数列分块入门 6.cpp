#include <cmath>
#include <cstdio>
#include <vector>
#define re register
#define ll long long
using namespace std;
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
const int N=1e5+5,M=350;
int num,block,l[M],r[M];
int belong[N];
int n,a[N];
vector<int>p[M];
inline void build()
{
	block=(int)sqrt(n);
	num=n/block;
	if(n%block)
		++num;
	for(re int i=1; i<=num; ++i)
	{
		l[i]=(i-1)*block+1;
		r[i]=i*block;
	}
	r[num]=n;
	for(re int i=1; i<=n; ++i)
	{
		belong[i]=(i-1)/block+1;
		p[belong[i]].push_back(a[i]);
	}
}
inline void insert(int pos,int c)
{
	int cnt=1;
	while(pos>(int)p[cnt].size())
		pos-=(int)p[cnt++].size();
	p[cnt].insert(p[cnt].begin()+pos-1,c);
}
inline int query(int pos)
{
	int cnt=1;
	while(pos>(int)p[cnt].size())
		pos-=(int)p[cnt++].size();
	return p[cnt][pos-1];
}
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	build();
	for(re int i=1; i<=n; ++i)
	{
		int opt,x,y,c;
		read(opt),read(x),read(y),read(c);
		if(opt==0)
			insert(x,y);
		else if(opt==1)
			printf("%d\n",query(y));
	}
	return 0;
}
