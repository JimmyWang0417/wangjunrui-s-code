#include<map>
#include<cstdio> 
#define re register
std::map<int,int>mp[100005];
int n,q;
int main()
{
	scanf("%d%d",&n,&q);
	for(re int i=1; i<=q; ++i)
	{
		int opt,l,r,k;
		scanf("%d%d%d",&opt,&l,&r);
		if(opt==1)
		{
			scanf("%d",&k);
			mp[l][r]=k;
		}
		else
			printf("%d\n",mp[l][r]);
	}

}
