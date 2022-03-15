#include<cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
int a[4];
int main()
{
	int t;
	ios::sync_with_stdio(false);
	cin>>t;
	while(t --)
	{
		cin>>a[1]>>a[2]>>a[3];
		int ans = 0 ;
		for(int i = 1 ; i <= 3 ; i ++)
			if(a[i] >= 1)  a[i] -- , ans ++ ;
		sort(a + 1 , a + 4) ;
		if(a[3] >= 1 && a[2] >= 1)  ans ++ , a[2] -- , a[3] -- ;
		if(a[2] >= 1 && a[1] >= 1)  ans ++ , a[2] -- , a[1] -- ;
		if(a[3] >= 1 && a[1] >= 1)  ans ++ , a[1] -- , a[3] -- ;
		if(a[3] >= 1 && a[2] >= 1
		        && a[1] >= 1)  ans ++ ;
		printf("%d\n" , ans) ;
	}
}
