#include<cstdio>
#include<algorithm>
#define re register
using namespace std;

template<typename T>
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
	return;
}
const int N=15e4+5;
struct heap
{
	int heap[N],heap_size;
	int n;
	inline void push(int val)
	{
		heap[++heap_size]=val;
		int nxt,now=heap_size;
		while(now>1)
		{
			nxt=now>>1;
			if(heap[nxt]>=heap[now])
				break;
			swap(heap[nxt],heap[now]);
			now=nxt;
		}
	}
	inline void pop()
	{
		heap[1]=heap[heap_size--];
		int nxt,now=1;
		while((now<<1)<=heap_size)
		{
			nxt=now<<1;
			if(nxt<heap_size&&heap[nxt+1]>heap[nxt])
				++nxt;
			if(heap[now]>=heap[nxt])
				break;
			swap(heap[nxt],heap[now]);
			now=nxt;
		}
	}

} h;
int n;
int sum,ans;
struct node
{
	int l1,l2;
	inline bool operator < (const node &rhs)const
	{
		return l2<rhs.l2;
	}
} a[N];
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i].l1);
		read(a[i].l2);
	}
	sort(a+1,a+1+n);
	for(re int i=1; i<=n; ++i)
	{
		if(sum+a[i].l1<=a[i].l2)
		{
			++ans;
			sum+=a[i].l1;
			h.push(a[i].l1);
		}
		else
		{
			if(h.heap_size&&h.heap[1]>a[i].l1)
			{
				sum+=a[i].l1-h.heap[1];
				h.pop();
				h.push(a[i].l1);
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
