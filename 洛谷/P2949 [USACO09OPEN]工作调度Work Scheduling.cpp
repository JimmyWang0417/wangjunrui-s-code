#include <cstdio>
#include <algorithm>
#define re register
#define ll long long
using namespace std;
template <typename T>
inline void read(T&x)
{
	x=0;
	char s=(char)getchar();
	bool flag=false;
	while(s<'0'||s>'9')
	{
		if(s=='-')
			flag=true;
		s=(char)getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=(x<<1)+(x<<3)+(s^'0');
		s=(char)getchar();
	}
	if(flag)
		x=~x+1;
}
const int N=1e6+5;
int n;
struct node
{
	int d,p;
	inline bool operator <(const node &rhs)const
	{
		return d<rhs.d;
	}
} a[N];
class heap
{
	public:
		int heap[N],heap_size;
		inline void push(int val)
		{
			heap[++heap_size]=val;
			int nxt,now=heap_size;
			while(now>1)
			{
				nxt=now>>1;
				if(heap[nxt]<=heap[now])
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
				if(nxt<heap_size&&heap[nxt+1]<heap[nxt])
					++nxt;
				if(heap[now]<=heap[nxt])
					break;
				swap(heap[nxt],heap[now]);
				now=nxt;
			}
		}
} h;
ll ans;
int main()
{
	read(n);
	for(re int i=1; i<=n; ++i)
	{
		read(a[i].d);
		read(a[i].p);
	}
	sort(a+1,a+1+n);
	for(re int i=1; i<=n; ++i)
	{
		if(h.heap_size<a[i].d)
		{
			h.push(a[i].p);
			ans+=a[i].p;
		}
		else
		{
			if(h.heap[1]<a[i].p)
			{
				ans+=a[i].p-h.heap[1];
				h.pop();
				h.push(a[i].p);
			}
		}
//		printf("%lld %d\n",ans,h.heap_size);
	}
	printf("%lld\n",ans);
	return 0;
}
