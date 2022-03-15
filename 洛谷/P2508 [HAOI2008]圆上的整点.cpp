#include <cstdio>
signed main()
{
    long long ans = 1;
    int r;
    scanf("%d", &r);
    for (int i = 2; i * i <= r; ++i)
        if (r % i == 0)
        {
            int cnt = 0;
            while (r % i == 0)
            {
                ++cnt;
                r /= i;
            }
            if ((i & 3) == 1)
                ans *= (cnt << 1) | 1;
        }
    if (r != 1 && (r & 3) == 1)
        ans *= 3;
    printf("%lld\n", ans << 2);
    return 0;
}