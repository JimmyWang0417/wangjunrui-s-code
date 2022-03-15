#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,a[500001];
unsigned long long sum1[500009],sum2[500009],power[500009],mo=1000003,ans=0,ans1=0,l,r,mid,b=97;
int main()
{
	scanf("%d",&n);
	power[0]=1;
	for(int i=1;i<=n;i++)power[i]=b*power[i-1];
	for(int i=1;i<=n;i++)
	{
		char a1;
		cin>>a1;
		if(a1=='1')a[i]=b-1;
		else a[i]=0;
		sum1[i]=(sum1[i-1]*b+a[i]);
	}
	for(int i=n;i>=1;i--)
	sum2[i]=(sum2[i+1]*b+a[i]);
	for(int i=1;i<n;i++)
	{
		if(a[i]+a[i+1]!=b-1)continue;
		int zuo=i,you=i+1;
		ans1=0;
		l=1,r=min(zuo,n-you+1);
		while(l<=r)
		{
			mid=(l+r)/2;
			int zuo1=zuo-mid,you1=you+mid;
			if((sum1[zuo]-sum1[zuo1]*power[mid]+sum2[you]-sum2[you1]*power[mid])==(power[mid]-1))
			{
				l=mid+1;
				if(mid>ans1)ans1=mid;
			}
			else r=mid-1;
		}
		ans+=ans1;
	}
	cout<<ans;
	return 0;
} 
