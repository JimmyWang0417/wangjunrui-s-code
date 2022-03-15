#include<bits/stdc++.h>
#define ull unsigned long long
ull power[500010],sum[500010],sum1[500010],b=1e9+9,ans;
char s[500001];
using namespace std;
inline int check(int x,int y)
{
	return sum[x+y-1]-sum[x-y-1]*power[y*2]==sum1[x-y]-sum1[x+y]*power[y*2];
}
int main()
{
		freopen("ans.out","r",stdin); 
	freopen("ans.txt","w",stdout); 
	power[0]=1;
	for(int i=1; i<=500000; i++)power[i]=power[i-1]*b;
	int n;
	cin>>n;
	getchar();
	for(int i=1; i<=n; i++)
	{
		s[i]=getchar();
		sum[i]=sum[i-1]*b+s[i]-'0';
	}
	for(int i=n; i>0; i--)
		if(s[i]=='0')
			sum1[i]=sum1[i+1]*b+s[i]-'0'+1;
		else
			sum1[i]=sum1[i+1]*b+s[i]-'0'-1;
	for(int i=2; i<=n; i++)
	{
		if(s[i]!=s[i-1])
		{
			int l=1,r=min(n-i+1,i-1),an;
			while(r>=l)
			{
				int mid=l+r>>1;
				if(check(i,mid))l=mid+1,an=mid;
				else r=mid-1,an=mid-1;
			}
			printf("%d\n",an);
			ans+=an;
		}
	}
	cout<<ans<<endl;
}
