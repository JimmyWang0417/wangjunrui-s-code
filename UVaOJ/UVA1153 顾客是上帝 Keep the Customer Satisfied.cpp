#include <cstdio>
#include <algorithm>
#define re register
using namespace std;

template <typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool f=false;
	while(!(s>='0'&&s<='9'))
	{
		if(s=='-')
			f=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+s-'0';
		s=(char)getchar();
	}
	if(f)
		x=(~x)+1;
}

const int N=2e6+5;
int heap[N],heap_size;
inline void push(int val)
{
	heap[++heap_size]=val;
	int now=heap_size,nxt;
	while(now>1)
	{
		nxt=now>>1;
		if(heap[nxt]>=heap[now])
			break;
		std::swap(heap[nxt],heap[now]);
		now=nxt;
	}
}
inline void pop()
{
	heap[1]=heap[heap_size--];
	int now=1,nxt;
	while((nxt=now<<1)<=heap_size)
	{
		if(nxt<heap_size&&heap[nxt+1]>heap[nxt])
			++nxt;
		if(heap[now]>=heap[nxt])
			break;
		std::swap(heap[now],heap[nxt]);
		now=nxt;
	}
}
int ans,T,n,sum;
struct node
{
	int prime,time;
	inline bool operator <(const node &rhs)const
	{
		return time<rhs.time;
	}
} a[N];
int main()
{
	read(T);
	while(T--)
	{
		read(n);
		for(re int i=1; i<=n; ++i)
		{
			read(a[i].prime);
			read(a[i].time);
		}
		sort(a+1,a+1+n);
		for(re int i=1; i<=n; ++i)
		{
			if(sum+a[i].prime<=a[i].time)
			{
				++ans;
				push(a[i].prime);
				sum+=a[i].prime;
			}
			else
			{
				if(heap_size&&heap[1]>a[i].prime)
				{
					sum+=a[i].prime-heap[1];
					pop();
					push(a[i].prime);
				}
			}
		}
		printf("%d\n",ans);
		heap_size=ans=sum=0;
		if(T)
			putchar('\n');
	}
}
