#include <cstdio>
#include <algorithm>
using namespace std;
unsigned array[5000005];

void randomize(unsigned a,unsigned b,unsigned mod)
{
	for( int i=0 ; i<5000000 ; i++ )
	{
		a = 31014 * (a & 65535) + (a >> 16);
		b = 17508 * (b & 65535) + (b >> 16);
		array[i] = ((a << 16) + b) % mod;
	}
}
unsigned a,b,mod;
unsigned k;
int main()
{
	scanf("%u%u%u%u",&a,&b,&mod,&k);
	randomize(a,b,mod);
	nth_element(array,array+k-1,array+5000000);
	printf("%u\n",array[k-1]);
	return 0;
}
