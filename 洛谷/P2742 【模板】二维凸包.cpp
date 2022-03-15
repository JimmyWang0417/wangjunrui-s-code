#include<cstdio>
#include<cctype>
#include<cmath>
#include<algorithm>
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
const int N=10010;
double xx,yy;
struct node
{
	double x,y;
} stack[N],vex[N];
inline double cross(node a,node b,node c)
{
	return (b.x-a.x)*(c.y-a.y)-(c.x-a.x)*(b.y-a.y);
}
inline bool cmp1(node a,node b)
{
	if(a.y==b.y)
		return a.x<b.x;
	return a.y<b.y;
}
inline double dis(node a,node b)
{
	sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
inline bool cmp2(node a,node b)
{
	if(atan2(a.y-yy,a.x-xx)!=atan2(b.y-yy,b.x-xx))
		return atan2(a.y-yy,a.x-xx)<atan2(b.y-yy,b.x-xx);
	return a.x<b.x;
}
int n;
int main()
{
	read(n);
	for(re int i=0; i<n; ++i)
		scanf("%lf%lf",&vex[i].x,&vex[i].y);
	if(n==1)
	{
		printf("0.00\n");
		return 0;
	}
	if(n==2)
	{
		printf("%.2lf\n",dis(vex[0],vex[1]));
		return 0;
	}
	sort(vex,vex+n,cmp1);
	stack[0]=vex[0];
	xx=vex[0].x;
	yy=vex[0].y;
	sort(vex+1,vex+n,cmp2);
	stack[1]=vex[1];
	re int top=1;
	for(re int i=2; i<n; ++i)
	{
		while(cross(stack[top-1],stack[top],vex[i])<0)
			--top;
		stack[++top]=vex[i];
	}
	re double s=0;
	for(re int i=1; i<=top; i++)
		s+=dis(stack[i-1],stack[i]);
	s+=dis(vex[0],stack[top]);
	printf("%.2lf\n",s);
	return 0;
}
