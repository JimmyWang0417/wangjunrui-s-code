#include<cstdio>
#include<algorithm>
#define re register
#define int long long
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
signed main()
{
	int T;
	read(T);
	while(T--)
	{
		int n,m;
		read(n),read(m);
		if(n%m==0)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
