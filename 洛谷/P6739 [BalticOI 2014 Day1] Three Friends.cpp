#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 6;
const int b = 27;
unsigned long long power[N], sum[N], ans;
char str[N];
int n, mid, answer;
int main()
{
    scanf("%d%s", &n, str);
    if (n % 2 == 0)
    {
        printf("NOT POSSIBLE\n");
        return 0;
    }
    power[0] = 1;
    for (int i = 1; i <= 2000001; i++)
        power[i] = power[i - 1] * b;
    for (int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] * b + str[i - 1] - 'A' + 1;
    mid = n >> 1;
    for (int i = 1; i <= mid; i++)
    {
        unsigned long long s1 = sum[n] - sum[i] * power[n - i] + sum[i - 1] * power[n - i],
                           s2 = ((sum[n] - sum[mid + 1] * power[mid]) * (1 + power[mid]));
        if (s2 == s1)
        {
            if (answer == 0)
            {
                answer = i;
                ans = s1;
            }
            else if (ans != s1)
            {
                printf("NOT UNIQUE\n");
                return 0;
            }
        }
    }
    for (int i = mid + 1; i <= n; i++)
    {
        unsigned long long s1 = sum[n] - sum[i] * power[n - i] + sum[i - 1] * power[n - i],
                           s2 = sum[mid] * (1 + power[mid]);
        if (s2 == s1)
        {
            if (answer == 0)
            {
                answer = i;
                ans = s1;
            }
            else if (ans != s1)
            {
                printf("NOT UNIQUE\n");
                return 0;
            }
        }
    }

    if (answer == 0)
    {
        printf("NOT POSSIBLE\n");
        return 0;
    }
    int t = 1;
    while (mid--)
    {
        if (t == answer)
            t++;
        printf("%c", str[t - 1]);
        t++;
    }
}