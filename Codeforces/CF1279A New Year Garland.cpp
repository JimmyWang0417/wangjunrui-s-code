#include<cstdio>
#include<algorithm>
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
int r,g,b,T;
int main()
{
	read(T);
	while(T--)
	{
		read(r);
		read(g);
		read(b);
		if(g>r)
			swap(g,r);
		if(b>r)
			swap(b,r);
		if(g+b<r-1)
			printf("No\n");
		else
			printf("Yes\n");
	}
}

