#include<cstdio>
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
}
inline void Exgcd(int a,int b,int&d,int&x,int&y)
{
	if(b==0)
	{
		d=a;
		x=1;
		y=0;
	}
	else
	{
		Exgcd(b,a%b,d,x,y);
		int t=x;
		x=y;
		y=t-a/b*y;
	}
}
int n,p[16],c[16],l[16],maxx;
inline bool check(int m)
{
	for(re int i=1,j,d,x,y; i<=n; i++)
		for(j=i+1; j<=n; j++)
		{
			int pp=p[i]-p[j],cc=c[j]-c[i];
			if(pp<0)
			{
				pp=-pp;
				cc=-cc;
			}
			Exgcd(pp,m,d,x,y);
			if(cc%d==0)
			{
				x=(x*(cc/d)%(m/d)+(m/d))%(m/d);
				if(x<=l[i]&&x<=l[j])
					return false;
			}
		}
	return true;
}
int main()
{
	read(n);
	for(re int i=1; i<=n; i++)
	{
		read(c[i]);
		read(p[i]);
		read(l[i]);
		if(maxx<c[i])
			maxx=c[i];
	}
	for(re int i=maxx;; i++)
		if(check(i))
		{
			printf("%d\n",i);
			return 0;
		}
	return 0;
}

