#include<iostream>
#include<stdlib.h>
#include<cmath>
#include<ctime>
#include<cstdio>
#define cold 0.996
#define temperature 100000
#define re register
#define time 4
#define INF 999999
using namespace std ;
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
struct spot
{
	int x;
	int y;
	int weight;
};
spot map[1001];
int n;
double t;
double tmpx,tmpy,tmpw;
double ansx,ansy,anse;
inline double energy (double x,double y)
{
	double e=0 ;
	for(re int i=1 ; i<=n ; i++)
	{
		tmpx=x-map[i].x;
		tmpy=y-map[i].y;
		tmpw=map[i].weight;
		e+=sqrt(tmpx*tmpx+tmpy*tmpy)*tmpw;
	}
	return e;
}
inline void colddown()
{
	t=temperature ;
	while(t>9e-18)
	{
		double nowx=ansx+((rand()<<1)-RAND_MAX )*t;
		double nowy=ansy+((rand()<<1)-RAND_MAX )*t;
		double nowe=energy(nowx,nowy) ;
		double de=nowe-anse ;
		if(de<0)
		{
			ansx=nowx;
			ansy=nowy;
			anse=nowe;
		}
		else
		{
			if(exp(-de/t)*RAND_MAX>rand())
			{
				ansx=nowx;
				ansy=nowy;
			}
		}
		t*=cold;
	}
}
inline void solve()
{
	for(re int i=1; i<=time; i++)
		colddown();
}
int main ()
{
	srand(rand()) ;
	read(n);
	for(re int i=1; i<=n; i++)
	{
		read(map[i].x);
		read(map[i].y);
		read(map[i].weight);
		ansx += map[i].x ;
		ansy += map[i].y ;
	}
	ansx/=n;
	ansy/=n;
	anse=energy(ansx,ansy) ;
	solve();
	printf("%.3lf %.3lf",ansx,ansy) ;
	return 0 ;
}
