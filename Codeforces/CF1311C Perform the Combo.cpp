#include<iostream>
#include <algorithm>
#include <cstring>
#include<cstdio>
#define re register
using namespace std;
const int N=2e5+5;
struct node
{
	int cnt[26];
	inline void clear()
	{
		memset(cnt,0,sizeof(cnt));
	}
	inline void operator += (const node &rhs)
	{
		for(re int i=0; i<26; ++i)
			cnt[i]+=rhs.cnt[i];
	}
} a[N],ans;
char str[N];
inline void work()
{
	int n,m;
	scanf("%d%d%s",&n,&m,str+1);
	for(re int i=1; i<=n; ++i)
	{
		a[i]=a[i-1];
		++a[i].cnt[str[i]-'a'];
	}
	ans=a[n];
	while(m--)
	{
		int p;
		scanf("%d",&p);
		ans+=a[p];
	}
	for(re int i=0; i<26; ++i)
		printf("%d ",ans.cnt[i]);
	putchar('\n');
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
		work();
	return 0;
}
