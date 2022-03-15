#include<cstdio>
#include<map>
#include<algorithm>
#include<iostream>
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
const int N = 5e3 + 10;
char s[N];
#define rep(i,a,b) for(re int i=a;i<=b;++i)
#define per(i,a,b) for(re int i=a;i>=b;--i)
signed main()
{
	int T;
	read(T);
	while (T--)
	{
		int n;
		read(n), scanf("%s",s+1);
		string t;
		int p = 1;
		rep(i , 1 , n)
		t += 'z';
		rep(k , 1 , n)
		{
			string ch;
			rep(i , k , n)
			ch += s[i];
			if ((n - k + 1) % 2 == 0)
				rep(i , 1 , k - 1)
				ch += s[i];
			else
				per(i , k - 1 , 1)
				ch += s[i];
			if (ch < t)
				p = k, t = ch;
		}
		cout << t << endl<< p << endl;
	}
	return 0;
}
