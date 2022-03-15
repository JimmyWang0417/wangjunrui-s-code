#include<cstdio>
#include<iostream>
#include<cstring>
#define re register
#define ll long long
#define int ll
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
	return;
}
const int N=2e5+5;
int n;
char str[N];
inline void work()
{
	scanf("%s",str+1);
	n=strlen(str+1);
	str[0]='R';
	int r=n+1,maxx=1;
	for(re int l=n; l>=0; --l)
		if(str[l]=='R')
		{
			maxx=max(r-l,maxx);
			r=l;
		}
	printf("%d\n",maxx);
}
signed main()
{
	int T;
	read(T);
	while(T--)
		work();
	return 0;
}

