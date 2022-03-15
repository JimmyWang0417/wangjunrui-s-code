#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <vector>
#include <cstdio>
#include <bitset>
#include <cstring>
#include <iostream>
#include <algorithm>
#define lowbit(x) (x&(-x))
#define re register
#define ll long long
#define ull unsigned long long
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
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
template<typename T,typename ...T1>
inline void read(T&x,T1&...x1)
{
	read(x);
	read(x1...);
}
const int N=2e5+5;
int a[N];
signed main()
{
	int m,n;
	read(m,n);
	for(re int i=1; i<=m; ++i)
		read(a[i]);
	int pos=0;
	priority_queue<int>q1;
	priority_queue<int,vector<int>,greater<int> >q2;
	for(re int i=1; i<=n; ++i)
	{
		int val;
		read(val);
		while(pos<val)
		{
			q1.push(a[++pos]);
			q2.push(q1.top());
			q1.pop();
		}
		printf("%d\n",q2.top());
		q1.push(q2.top());
		q2.pop();
	}
	return 0;
}


