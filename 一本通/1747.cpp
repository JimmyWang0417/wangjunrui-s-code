#include<cstdio>
#define re register
#define tmp (stack[top].rightpos-stack[top].leftpos+1)
using namespace std;
template<typename T>
inline void read(T&x)
{
	x=0;
	char s=getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=getchar();
	}
	if(f)
		x=(~x)+1;
}
struct node
{
	int leftpos,rightpos,leftval,rightval;
} stack[100000+10];
int n,ans=0;
int main()
{
	read(n);
	for(re int i=1,top=-1; i<=n; i++)
	{
		top++;
		read(stack[top].rightval);
		stack[top].leftval=stack[top].rightval;
		stack[top].leftpos=stack[top].rightpos=i;
		while(top>=1&&stack[top-1].rightval<stack[top].rightval)
		{
			if(stack[top].leftval>stack[top-1].leftval)
			{
				stack[top].leftpos=stack[top-1].leftpos;
				stack[top].leftval=stack[top-1].leftval;
			}
			stack[top-1]=stack[top];
			top--;
		}
		//printf(" %d\n",tmp);
		if(ans<tmp)
			ans=tmp;
	}
	printf("%d\n",ans==1?0:ans);
	return 0;
}
l
