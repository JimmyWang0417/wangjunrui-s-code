#include <cstdio>
#include <iostream>
#include <algorithm>
#define ll long long
#define re register

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
#define int ll
int u,v,cnt[70];
bool vis[70];
inline int work()
{
	int u , v;
	read(u),read(v);
	if(u == v && v == 0) return cout << 0 << '\n' , 0;
	if(u == v) return cout << 1 << '\n' << u << '\n' , 0;
	if(u > v || (v - u) % 2) return cout << -1 << '\n' , 0;
	int a = (v - u) / 2 , b = (v + u) / 2;
	if(a + b == v && (a ^ b) == u) return cout << 2 << '\n' << a << " " << b << '\n' , 0;
	int c = (v - u) / 2;
	cout << 3 << '\n' << c << " " << c << " " << u << '\n';
	return 0;

}
signed main()
{
	work();
	return 0;
}

