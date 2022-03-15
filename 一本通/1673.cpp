

#include<cstdio>
#include<algorithm>
#define re register
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
const int N=1e6+10;
int n,h,v;
long long m,ans=-1e18,sum,cost;
struct node
{
	int h,v;
} x,temp_node;
#define make_node(x,y) (temp_node.h=x,temp_node.v=y)
struct Heap
{
	int heap_size;
	node heap[N];
	inline void push(node&x)
	{
		heap[++heap_size]=x;
		int now=heap_size,nxt;
		while(now>1)
		{
			nxt=now>>1;
			if(heap[nxt].v<=heap[now].v)
				break;
			swap(heap[nxt],heap[now]);
			now=nxt;
		}
	}
	inline void pop()
	{
		heap[1]=heap[heap_size--];
		int now=1,nxt;
		while(now<<1<=heap_size)
		{
			nxt=now<<1;
			if(nxt<heap_size&&heap[nxt].v>heap[nxt+1].v)
				nxt++;
			if(heap[nxt].v>=heap[now].v)
				break;
			swap(heap[nxt],heap[now]);
			now=nxt;
		}
	}
	inline node top()
	{
		return heap[1];
	}
} q;
long long sum_h,sum_v,res;
int main()
{
	read(n);
	read(m);
	m++;
	for(re int i=1; i<=n; i++)
	{
		read(h);
		read(v);
		m--;
		if(!m)
			break;
		res+=v;
		if(h>1)
		{
			make_node(h-1,v);
			q.push(temp_node);
			sum_h+=temp_node.h;
			sum_v+=1ll*temp_node.h*temp_node.v;
			while(q.heap_size&&sum_h-q.top().h>=m)
			{
				sum_h-=q.top().h;
				sum_v-=1ll*q.top().h*q.heap[1].v;
				q.pop();
			}
			ans=max(ans,sum_h<m?sum_v+res:res+sum_v+1ll*(m-sum_h)*q.heap[1].v);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
