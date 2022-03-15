#include<vector>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define re register
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char str=(char)getchar();
	bool f=false;
	while(!(str>='0'&&str<='9'))
	{
		if(str=='-')
			f=true;
		str=(char)getchar();
	}
	while(str>='0'&&str<='9')
	{
		x=(x<<1)+(x<<3)+str-'0';
		str=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}
const int N=2e4+5,L=5e2+5,base=2,mod1=1e9+7,mod2=1e9+9;
char s[N][L];
int power1[L*L],power2[L*L],
    val1[N][L],val2[N][L],
    pre1[N][L],pre2[N][L];
int id[N],len[N],n;
#define find(i,p) (s[i][(p-1)%len[i]+1])
inline pair<int,int> calc(int i,int l)
{
	int coun=l/len[i],remainder=l%len[i];
	if(!remainder)
		return make_pair(pre1[i][coun],pre2[i][coun]);
	int value1=(1ll*pre1[i][coun]*power1[remainder]+val1[i][remainder])%mod1,
	    value2=(1ll*pre2[i][coun]*power2[remainder]+val2[i][remainder])%mod2;
	return make_pair(value1,value2);
}
#define check(i,j,l) (calc(i,l)==calc(j,l))
inline int get_lcp(int i,int j)
{
	if(len[i]>len[j])
		swap(i,j);
	int l=1,r=len[i]*len[j]/__gcd(len[i],len[j]),res=0;
	while(l<=r)
	{
		int mid=(l+r)>>1;
		if(check(i,j,mid))
		{
			res=mid;
			l=mid+1;
		}
		else
			r=mid-1;
	}
	return res;
}
inline bool cmp(int i,int j)
{
	int t=get_lcp(i,j);
	return find(i,t+1)<find(j,t+1);
}
int main()
{
#define l 500
	//freopen("ans.in", "r", stdin);
	//freopen("ans.out", "w", stdout);
	power1[0]=power2[0]=1ull;
	for(re int i=1; i<=l*l; ++i)
	{
		power1[i]=1ll*power1[i-1]*base%mod1;
		power2[i]=1ll*power2[i-1]*base%mod2;
	}
	//printf("%lld %lld\n",power1[l*l],power2[l*l]);
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		id[i]=i;
		scanf("%s",s[i]+1);
		len[i]=(int)strlen(s[i]+1);
	}
	/*for(re int i=1; i<=n; ++i)
		printf("%d %s %d\n",id[i],s[i]+1,len[i]);*/
	for(re int i=1; i<=n; ++i)
	{
		for(re int j=1; j<=len[i]; ++j)
		{
			val1[i][j]=(1ll*val1[i][j-1]*base+s[i][j]-'0')%mod1;
			val2[i][j]=(1ll*val2[i][j-1]*base+s[i][j]-'0')%mod2;
		}
		for(re int j=1; j<=l; ++j)
		{
			pre1[i][j]=(1ll*pre1[i][j-1]*power1[len[i]]+val1[i][len[i]])%mod1;
			pre2[i][j]=(1ll*pre2[i][j-1]*power2[len[i]]+val2[i][len[i]])%mod2;
		}
	}
	/*for(re int i=1; i<=n; ++i)
		printf("%lld %lld %lld %lld\n",val1[i][len[i]],val2[i][len[i]],pre1[i][l],pre2[i][l]);*/
#undef l
	stable_sort(id+1,id+1+n,cmp);
	/*for(re int i=1; i<=n; ++i)
		printf("%d ",id[i]);
	putchar('\n');*/
	int ans=0;
	for(re int i=1; i<n; ++i)
		ans=max(ans,get_lcp(id[i],id[i+1]));
	printf("%d\n",ans);
	return 0;
}
