#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#define ll long long
#define re register
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
}
const int N = 2e5 + 10;
int a[N], b[N], ans[N];
string s;
int cnt1,cnt2,cnt;
signed main()
{
	ios::sync_with_stdio(false);
	cin >> s;
	int len=s.length();
	for(re int i=0 ; i<= len - 1; ++i)
	{
		if (s[i] == '(')
			a[++ cnt1] = i;
		else
			b[++ cnt2] = i;
	}
	sort(b + 1, b + cnt2 + 1, greater<int>());
	for(re int i=1; i<= min(cnt1 , cnt2); ++i)
	{
		if (a[i] < b[i])
			ans[ ++cnt] = a[i], ans[ ++cnt] = b[i];
	}
	if (cnt == 0)
		cout << 0 << '\n';
	else
	{
		cout << 1 << '\n';
		sort(ans + 1, ans + cnt + 1);
		cout << cnt << '\n';
		for(re int i=1 ; i<= cnt;++i)
		cout << ans[i] + 1 << " ";
		cout << '\n';
	}
	return 0;
}
