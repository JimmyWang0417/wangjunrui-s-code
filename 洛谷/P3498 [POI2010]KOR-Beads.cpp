#include <map>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define re register
#define ll long long
#define ull unsigned ll
using namespace std;
template <typename T>
inline void read(T &x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(s<'0'||s>'9')
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+(s^'0');
		s=(char)getchar();
	}
	if(flag)
		x=~x+1;
	return;
}
const int N=2e5+5,mod=1e9+7;
vector<int>ansa;
int ans;
ull hash1[N],hash2[N],power[N];
int a[N],n;
inline ull calc1(int l,int r)
{
	return (hash1[r]-hash1[l]*power[r-l]);
}
inline ull calc2(int r,int l)
{
	return (hash2[l]-hash2[r]*power[r-l]);
}
inline void solve(int len)
{
	static int tmp[N];
	int tot=0,res=0;
	for(re int i=len; i<=n; i+=len)
		tmp[++tot]=min(calc1(i-len,i),calc2(i+1,i-len+1));
	stable_sort(tmp+1,tmp+1+tot);
	for(re int i=2; i<=tot; i++)
		if(tmp[i]==tmp[i-1])
			res++;
	if(ans<tot-res)
	{
		ansa.clear();
		ans=tot-res;
		ansa.push_back(len);
	}
	else if(ans==tot-res)
		ansa.push_back(len);
}
int main()
{
	read(n);
	power[0]=1ull;
	for(re int i=1; i<=n; ++i)
		power[i]=power[i-1]*(n+mod);
	for(re int i=1; i<=n; ++i)
		read(a[i]);
	for(re int i=1; i<=n; ++i)
		hash1[i]=hash1[i-1]*(n+mod)+a[i];
	for(re int i=n; i>=1; --i)
		hash2[i]=hash2[i+1]*(n+mod)+a[i];
	for(re int i=1; i<=n; ++i)
	{
		if(n/i<ans)
			break;
		solve(i);
	}
	printf("%d %d\n",ans,ansa.size());
	for(re int i=0; i<ansa.size(); ++i)
		printf("%d ",ansa[i]);
	putchar('\n');
	return 0;
}
