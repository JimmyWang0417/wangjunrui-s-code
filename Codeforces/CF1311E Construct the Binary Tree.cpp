#include<bits/stdc++.h>
using namespace std;
const int N=5005+5;
int t,n,m,l,r,sum[N],dep[N];

bool solve()
{
	fill(dep+1,dep+n+1,1);
	m=n*(n-1)/2-m;
	for(l=2,r=n; l<r; --r)
	{
		while(l<r && ( m-r+l<0 || dep[l]==dep[l-1]*2))l++;
		if(l>=r)break;
		m-=r,dep[r]--;
		m+=l,dep[l]++;
	}
	return m==0;
}

int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		if(!solve()) printf("NO\n");
		else
		{
			printf("YES\n");
			for(int i=1; i<=r; ++i)
				sum[i]=sum[i-1]+dep[i];
			for(int i=2; i<=r; ++i)
			{
				for(int j=0; j<dep[i]; ++j)
					printf("%d ",sum[i-2]+1+j/2);
			}
			printf("\n");
		}
	}
	return 0;
}
