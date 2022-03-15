#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long lol;
int n,top,pd[1000001],l,r,cnt,tot;
lol st[1000001],ans,sum,a[1000001];
bool cmp(lol a,lol b)
{
	return a>b;
}
int main()
{
	int i;
	cin>>n;
	for (i=1; i<=n; i++)
	{
		scanf("%lld",&st[++top]);
		sum+=st[top];
		if (st[top]==0) pd[top]=1;
		tot+=(bool)st[top];
		while (top>2&&(!pd[top])&&(!pd[top-1])&&(!pd[top-2])&&(st[top-1]>=st[top])&&(st[top-1]>=st[top-2]))
		{
			st[top-2]=st[top]+st[top-2]-st[top-1];
			top-=2;
		}
	}
	for (l=1; (!pd[l])&&(!pd[l+1])&&(st[l]>=st[l+1]); l+=2)
		ans+=tot&1?st[l]-st[l+1]:st[l+1]-st[l];
	for (r=top; (!pd[r])&&(!pd[r-1])&&(st[r]>=st[r-1]); r-=2)
		ans+=tot&1?st[r]-st[r-1]:st[r-1]-st[r];
	for (i=l; i<=r; i++)
		if (pd[i]==0) a[++cnt]=st[i];
	sort(a+1,a+cnt+1,cmp);
	for (i=1; i<=cnt; i++)
	{
		if (i&1) ans+=a[i];
		else ans-=a[i];
	}
	cout<<(sum+ans)/2<<' '<<(sum-ans)/2<<endl;
}
