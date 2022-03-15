/*https://www.luogu.org/problemnew/show/P1618*/
#include<cstdio>
using namespace std;
int a,b,c,f[10],stack[10],sum;
void DFS(int t)
{
	for(register int i=1; i<=9; i++)
		if(f[i]==0)
		{
			stack[t]=i;
			f[i]=1;
			if(t==9)
			{
				if((stack[1]*100+stack[2]*10+stack[3])/a==(stack[4]*100+stack[5]*10+stack[6])/b&&
				        (stack[4]*100+stack[5]*10+stack[6])/b==(stack[7]*100+stack[8]*10+stack[9])/c&&
				        (stack[1]*100+stack[2]*10+stack[3])%a==0&&(stack[4]*100+stack[5]*10+stack[6])%b==0&&
				        (stack[7]*100+stack[8]*10+stack[9])%c==0)
				{
					printf("%d%d%d %d%d%d %d%d%d\n",stack[1],stack[2],stack[3],stack[4],
					stack[5],stack[6],stack[7],stack[8],stack[9]);
					sum++;
				}
			}
			else
				DFS(t+1);
			f[i]=0;
		}
}
int main()
{
	scanf("%d%d%d",&a,&b,&c);
	DFS(1);
	if(sum==0)
		printf("No!!!");
}
