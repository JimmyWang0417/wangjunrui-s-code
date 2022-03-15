#include<map>
#include<cstdio>
#include<vector>
#define re register
using namespace std;
const int N=8,M=105,maxstate=15000;
const double INF=1e18;
double c,price[N][M],dp[M][maxstate];
int m,n,kk,opt[M][maxstate],pre[M][maxstate],buy_next[maxstate][N],sell_next[maxstate][N],s[N],k[N];
char name[N][10];
vector<vector<int> >states;
map<vector<int>,int>ID;
inline void dfs(int stock,vector<int>&lots,int totlot)
{
	if(stock==n)
	{
		ID[lots]=states.size();
		states.push_back(lots);
	}
	else
		for(re int i=0; i<=k[stock]&&totlot+i<=kk; ++i)
		{
			lots[stock]=i;
			dfs(stock+1,lots,totlot+i);
		}
}
inline void init()
{
	vector<int>lots(n);
	states.clear();
	ID.clear();
	dfs(0,lots,0);
	for(re int s=0; s<states.size(); ++s)
	{
		int totlot=0;
		for(re int i=0; i<n; ++i)
			totlot+=states[s][i];
		for(re int i=0; i<n; ++i)
		{
			buy_next[s][i]=sell_next[s][i]=-1;
			if(states[s][i]<k[i]&&totlot<kk)
			{
				vector<int>newstate=states[s];
				++newstate[i];
				buy_next[s][i]=ID[newstate];
			}
			if(states[s][i]>0)
			{
				vector<int>newstate=states[s];
				--newstate[i];
				sell_next[s][i]=ID[newstate];
			}
		}
	}
}
inline void update(int day,int s,int s2,double v,int o)
{
	if(v>dp[day+1][s2])
	{
		dp[day+1][s2]=v;
		opt[day+1][s2]=o;
		pre[day+1][s2]=s;
	}
}
inline double DP()
{
	for(re int day=0; day<=m; ++day)
		for(re int s=0; s<states.size(); ++s)
			dp[day][s]=-INF;
	dp[0][0]=c;
	for(re int day=0; day<m; ++day)
		for(re int s=0; s<states.size(); ++s)
		{
			double v=dp[day][s];
			if(v<-1)
				continue;
			update(day,s,s,v,0);
			for(re int i=0; i<n; ++i)
			{
				if(buy_next[s][i]>=0&&v>=price[i][day]-1e-3)
					update(day,s,buy_next[s][i],v-price[i][day],i+1);
				if(sell_next[s][i]>=0)
					update(day,s,sell_next[s][i],v+price[i][day],-i-1);
			}
		}
	return dp[m][0];
}
inline void print_ans(int day,int s)
{
	if(day==0)
		return;
	print_ans(day-1,pre[day][s]);
	if(opt[day][s]==0)
		printf("HOLD\n");
	else if(opt[day][s]>0)
		printf("BUY %s\n",name[opt[day][s]-1]);
	else printf("SELL %s\n",name[-opt[day][s]-1]);
}
int main()
{
	re int kase=0;
	while(scanf("%lf%d%d%d",&c,&m,&n,&kk)!=EOF)
	{
		if(kase++>0)
			putchar('\n');
		for(re int i=0; i<n; ++i)
		{
			scanf("%s%d%d",name[i],&s[i],&k[i]);
			for(re int j=0; j<m; ++j)
			{
				scanf("%lf",&price[i][j]);
				price[i][j]*=s[i];
			}
		}
		init();
		double ans=DP();
		printf("%.2lf\n",ans);
		print_ans(m,0); 
	}
}
