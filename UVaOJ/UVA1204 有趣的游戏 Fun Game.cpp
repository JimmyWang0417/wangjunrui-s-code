#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
#define re register
using namespace std;
const int N=16;
string s[N][2];
int n,overlap[N][N][2][2],d[1<<N][N][2];
struct Item
{
	string s,rev;
	inline bool operator <(const Item&rhs)const
	{
		return s.length()<rhs.s.length();
	}
};
inline int calc_overlap(const string &a,const string &b)
{
	int len1=a.length(),len2=b.length();
	for(re int i=1; i<len1; ++i)
	{
		if(len2+i<=len1)
			continue;
		bool ok=true;
		for(re int j=0; i+j<len1; ++j)
			if(a[i+j]!=b[j])
			{
				ok=false;
				break;
			}
		if(ok)
			return len1-i;
	}
	return 0;
}
inline void init()
{
	Item tmp[N];
	for(re int i=0; i<n; ++i)
	{
		cin>>tmp[i].s;
		tmp[i].rev=tmp[i].s;
		reverse(tmp[i].rev.begin(),tmp[i].rev.end());
	}
	int nextn=0;
	sort(tmp,tmp+n);
	for(re int i=0; i<n; ++i)
	{
		bool ok=true;
		for(re int j=i+1; j<n; ++j)
			if(tmp[j].s.find(tmp[i].s)!=string::npos||tmp[j].rev.find(tmp[i].s)!=string::npos)
			{
				ok=false;
				break;
			}
		if(ok)
		{
			s[nextn][0]=tmp[i].s;
			s[nextn][1]=tmp[i].rev;
			++nextn;
		}
	}
	n=nextn;
	for(re int i=0; i<n; ++i)
		for(re int j=0; j<n; ++j)
			for(re int x=0; x<2; ++x)
				for(re int y=0; y<2; ++y)
					overlap[i][j][x][y]=calc_overlap(s[i][x],s[j][y]);
}
#define update(x,v) if((x)<0||(x)>(v))(x)=(v)
inline void solve()
{
	memset(d,-1,sizeof(d));
	const int full=(1<<n)-1;
	d[1][0][0]=s[0][0].length();
	for(re int S=1; S<full; ++S)
	{
		for(re int i=0; i<n; ++i)
			for(re int x=0; x<2; ++x)
				if(d[S][i][x]>=0)
					for(re int j=1; j<n; ++j)
						if(!(S&(1<<j)))
							for(re int y=0; y<2; ++y)
								update(d[S|(1<<j)][j][y],d[S][i][x]+s[j][y].length()-overlap[i][j][x][y]);
	}
	int ans=-1;
	for(re int i=0; i<n; ++i)
		for(re int x=0; x<2; ++x)
		{
			if(d[full][i][x]<0)
				continue;
			update(ans,d[full][i][x]-overlap[i][0][x][0]);
		}
	if(ans<=1)
		ans=2;
	printf("%d\n",ans);
}
int main()
{
	ios::sync_with_stdio(false);
	while(cin>>n&&n)
	{
		init();
		solve();
	}
	return 0;
}
