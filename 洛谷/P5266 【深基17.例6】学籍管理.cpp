#include<iostream>
#include<cstdio>
#include<map>
#include<string>
#define re register
std::map<std::string,int>mp;
int n,cnt;
int main()
{
	scanf("%d",&n);
	for(re int i=1; i<=n; ++i)
	{
		std::string s;
		int opt,score;
		std::cin>>opt;
		if(opt==1)
		{
			std::cin>>s>>score;
			if(!mp[s])
				++cnt;
			mp[s]=score;
			printf("OK\n");
		}
		else if(opt==2)
		{
			std::cin>>s;
			if(mp[s])
				printf("%d\n",mp[s]);
			else
				printf("Not found\n");
		}
		else if(opt==3)
		{
			std::cin>>s;
			if(mp[s])
			{
				--cnt;
				mp[s]=0;
				printf("Deleted successfully\n");
			}
			else
				printf("Not found\n");
		}
		else if(opt==4)
			printf("%d\n",cnt);
	}
}
