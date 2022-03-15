#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<ctime>
#define re register
using namespace std;
const int INF=2147483647,N=1e5+10;
int cnt,rt;
int size[N],val[N],num[N],rk[N],son[N][2];
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
inline void pushup(int p)
{
	size[p]=size[son[p][0]]+size[son[p][1]]+num[p];
}
inline void rotate(int &p,int d)
{
	int k=son[p][d^1];
	son[p][d^1]=son[k][d];
	son[k][d]=p;
	pushup(k);
	pushup(p);
	p=k;
}
inline void ins(int &p,int x)
{
	if(!p)
	{
		p=++cnt;
		size[p]=num[p]=1;
		val[p]=x;
		rk[p]=rand();
		return;
	}
	if(val[p]==x)
	{
		++num[p];
		++size[p];
		return;
	}
	int d=(x>val[p]);
	ins(son[p][d],x);
	if(rk[p]<rk[son[p][d]])
		rotate(p,d^1);
	pushup(p);
}
inline void del(int &p,int x)
{
	if(!p)
		return;
	if(x<val[p])
		del(son[p][0],x);
	else if(x>val[p])
		del(son[p][1],x);
	else
	{
		if(!son[p][0]&&!son[p][1])
		{
			--num[p];
			--size[p];
			if(num[p]==0)
				p=0;
		}
		else if(son[p][0]&&!son[p][1])
		{
			rotate(p,1);
			del(son[p][1],x);
		}
		else if(!son[p][0]&&son[p][1])
		{
			rotate(p,0);
			del(son[p][0],x);
		}
		else if(son[p][0]&&son[p][1])
		{
			int d=(rk[son[p][0]]>rk[son[p][1]]);
			rotate(p,d);
			del(son[p][d],x);
		}
	}
	pushup(p);
}
inline int getrank(int p,int x)
{
	if(!p)
		return 0;
	if(val[p]==x)
		return size[son[p][0]]+1;
	if(val[p]>x)
		return getrank(son[p][0],x);
	if(val[p]<x)
		return size[son[p][0]]+num[p]+getrank(son[p][1],x);
}
inline int find(int p,int x)
{
	if(!p)
		return 0;
	if(size[son[p][0]]>=x)
		return find(son[p][0],x);
	if(size[son[p][0]]+num[p]<x)
		return find(son[p][1],x-size[son[p][0]]-num[p]);
	return val[p];
}
inline int pre(int p,int x)
{
	if(!p)
		return -INF;
	if(val[p]>=x)
		return pre(son[p][0],x);
	return max(val[p],pre(son[p][1],x));
}
inline int suc(int p,int x)
{
	if(!p)
		return INF;
	if(val[p]<=x)
		return suc(son[p][1],x);
	return min(val[p],suc(son[p][0],x));
}
int main()
{
	srand((unsigned long long)time(0));
	srand(rand());
	srand(rand());
	re int n,opt,x;
	read(n);
	while(n--)
	{
		read(opt),read(x);
		switch(opt)
		{
			case 1:
				ins(rt,x);
				break;
			case 2:
				del(rt,x);
				break;
			case 3:
				printf("%d\n",getrank(rt,x));
				break;
			case 4:
				printf("%d\n",find(rt,x));
				break;
			case 5:
				printf("%d\n",pre(rt,x));
				break;
			case 6:
				printf("%d\n",suc(rt,x));
				break;
		}
	}
}
