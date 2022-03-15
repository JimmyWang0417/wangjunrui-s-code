#include<cstdio>
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
template<typename T>
inline void swap(T&a,T&b)
{
	T c=a;
	a=b;
	b=c;
}
const int N=1e6+10;
int n,b,a[N],sum;
struct Heap
{
	int heap[N],heap_size;
	inline void put(const int &x)
	{
		int now,next;
		heap[now=++heap_size]=x;
		while(now>1)
		{
			next=now>>1;
			if(heap[next]<=heap[now])
				break;
			swap(heap[next],heap[now]);
			now=next;
		}
		return;
	}
	inline int get()
	{
		int res=heap[1];
		heap[1]=heap[heap_size--];
		int now=1,next;
		while(now<<1<=heap_size)
		{
			next=now<<1;
			if(next<heap_size&&heap[next]>heap[next+1])
				next++;
			if(heap[next]>=heap[now])
				break;
			swap(heap[now],heap[next]);
			now=next;
		}
		return res;
	}
} s;
int main()
{
	read(n);
	read(b);
	for(re int i=1; i<=n; i++)
	{
		read(a[i]);
		s.put(a[i]);
	}
	s.put(b);
	while(1)
	{
		s.put(s.get()+1);
		int res=s.get();
		if(s.heap[1]<=++sum)
		{
			printf("%d\n",sum);
			return 0;
		}
		s.put(res);
	}
	return 0;
}

