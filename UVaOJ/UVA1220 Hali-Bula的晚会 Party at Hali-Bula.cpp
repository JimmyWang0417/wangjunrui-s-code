#include<iostream>
#include<string>
#include<vector>
#include<cstdio>
#include<map>
#define re register
#define ll long long
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
const int N=205;
int n,dp[N][2],cnt;
bool f[N][2];
char ans[2][10]= {"No","Yes"};
map<string,int>mp;
vector<vector<int> >son;
inline int insert(string &s)
{
	if(mp[s]==0)
		mp[s]=++cnt;
	return mp[s];
}
inline void DP(int u)
{
	f[u][1]=f[u][0]=1;
	dp[u][1]=1;
	dp[u][0]=0;
	if(son[u].empty())
		return;
	for(re int i=0; i<son[u].size(); ++i)
	{
		int &v=son[u][i];
		DP(v);
		dp[u][1]+=dp[v][0];
		f[u][1]=f[u][1]&&f[v][0];
		if(dp[v][0]==dp[v][1])
		{
			dp[u][0]+=dp[v][0];
			f[u][0]=false;
		}
		else if(dp[v][0]>dp[v][1])
		{
			dp[u][0]+=dp[v][0];
			f[u][0]=f[u][0]&&f[v][0];
		}
		else if(dp[v][0]<dp[v][1])
		{
			dp[u][0]+=dp[v][1];
			f[u][0]=f[u][0]&&f[v][1];
		}
	}
}
int main()
{
	//freopen("ans.in","r",stdin);
	//freopen("ans.out","w",stdout);
	ios::sync_with_stdio(false);
	while(cin>>n&&n)
	{
		for(re int i=0; i<=n; ++i)
			son.push_back(vector<int>());
		cnt=0;
		string s1,s2;
		cin>>s1;
		insert(s1);
		for(re int i=1; i<n; ++i)
		{
			cin>>s1>>s2;
			son[insert(s2)].push_back(insert(s1));
		}
		DP(1);
		printf("%d ",max(dp[1][0],dp[1][1]));
		if(dp[1][0]==dp[1][1])
			puts(ans[0]);
		else
			puts(ans[dp[1][0]>dp[1][1]?f[1][0]:f[1][1]]);
		mp.clear();
		son.clear();
	}
	return 0;
}
