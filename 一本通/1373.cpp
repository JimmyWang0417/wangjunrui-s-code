#include<cstdio>
using namespace std;
int T,heap_size,max,sum,n,sub[100],time[100],a[100];
struct node
{
	int date,i;
} heap[100],temp;
inline void swap(node &a,node &b)
{
	node c=a;
	a=b;
	b=c;
}
inline void put(node d)
{
	register int now,next;
	heap[++heap_size]=d;
	now=heap_size;
	while(now>1)
	{
		next=now>>1;
		if(heap[next].date>=heap[now].date)
			break;
		swap(heap[next],heap[now]);
		now=next;
	}
}
inline node get()
{
	register int now=1,next;
	node res=heap[1];
	heap[1]=heap[heap_size--];
	while(now<<1<=heap_size)
	{
		next=now<<1;
		if(next<heap_size&&heap[next].date<heap[next+1].date)
			next++;
		if(heap[now].date>=heap[next].date)
			break;
		swap(heap[now],heap[next]);
		now=next;
	}
	return res;
}
int main()
{
	scanf("%d",&n);
	for(register int i=1; i<=n; i++)
		scanf("%d",&a[i]);
	for(register int i=1; i<=n; i++)
		scanf("%d",&sub[i]);
	for(register int i=2; i<=n; i++)
		scanf("%d",&time[i]);
	scanf("%d",&T);
	for(register int n1=1; n1<=n; n1++)
	{
		T-=time[n1];
		heap_size=sum=0;
		for(register int i=1; i<=n1; i++)
		{
			temp.date=a[i];
			temp.i=i;
			put(temp);
		}
		//printf("%d\n",T);
		for(register int i=1; i<=T; i++)
		{
			temp=get();
			if(temp.date<=0)temp.date=0;
			//printf("%d %d\n",temp.date,temp.i);
			sum+=temp.date;
			temp.date-=sub[temp.i];
			put(temp);
		}
		if(sum>max)
			max=sum;
	}
	printf("%d\n",max==0?-1:max);
	return 0;
}
