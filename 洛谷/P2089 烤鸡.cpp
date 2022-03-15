/*题目背景
猪猪hanke得到了一只鸡
题目描述
猪猪Hanke特别喜欢吃烤鸡（本是同畜牲，相煎何太急！）Hanke吃鸡很特别，为什么特别呢？因为他有10种配料（芥末、孜然等），每种配料可以放1—3克，任意烤鸡的美味程度为所有配料质量之和
现在，Hanke想要知道，如果给你一个美味程度，请输出这10种配料的所有搭配方案
输入输出格式
输入格式：

一行,n<=5000

输出格式：

第一行，方案总数
第二行至结束，10个数，表示每种配料所放的质量
按字典序排列。
如果没有符合要求的方法，就只要在第一行输出一个“0”

输入输出样例
输入样例#1： 复制
11
输出样例#1： 复制
10
1 1 1 1 1 1 1 1 1 2
1 1 1 1 1 1 1 1 2 1
1 1 1 1 1 1 1 2 1 1
1 1 1 1 1 1 2 1 1 1
1 1 1 1 1 2 1 1 1 1
1 1 1 1 2 1 1 1 1 1
1 1 1 2 1 1 1 1 1 1
1 1 2 1 1 1 1 1 1 1
1 2 1 1 1 1 1 1 1 1
2 1 1 1 1 1 1 1 1 1
说明
枚举*/
#include<cstdio>
using namespace std;
int a[59049][11],temp[11],sum,ans,n;
void DFS(int t)
{
	for(register int i=1; i<=3; i++)
	{
		ans+=i;
		temp[t]=i;
		if(t==10)
		{
			if(ans==n)
			{
				sum++;
				for(register int j=1; j<=10; j++)
					a[sum][j]=temp[j];
			}

		}
		else
			DFS(t+1);
		ans-=i;
	}
}
int main()
{
	scanf("%d",&n);
	DFS(1);
	printf("%d\n",sum);
	for(register int i=1; i<=sum; i++)
	{
		printf("%d",a[i][1]);
		for(register int j=2; j<=10; j++)
			printf(" %d",a[i][j]);
		putchar('\n');
	}

}
