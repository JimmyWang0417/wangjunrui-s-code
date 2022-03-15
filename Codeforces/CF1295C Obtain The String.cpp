#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
const int L = 30;

char s[N], t[N];
int exist1[L], exist2[L], temp[L];
int nex[L][N], cnt[L];

void init() {
    memset(temp, 0x3f, sizeof temp);
    memset(exist1, 0, sizeof exist1);
    memset(exist2, 0, sizeof exist2);
    memset(cnt, 0, sizeof cnt);
}

int main() {
    int T, len1, len2, ans;
    scanf("%d", &T);
    while (T--) {
        init();
        scanf("%s%s", s, t);
        len1 = strlen(s), len2 = strlen(t);
        for (int i = 0; i < len1; i++) exist1[s[i] - 'a'] = 1;
        for (int i = 0; i < len2; i++) exist2[t[i] - 'a'] = 1;
        int flag = 0;
        for (int i = 0; i < 26; i++)
            if (!exist1[i] and exist2[i])
                flag = 1;
        if (flag) {
            puts("-1");
            continue;
        }
        ans = 0;
        for (int i = 0; i < len1; i++) {
            int x = s[i] - 'a';
            temp[x] = min(temp[x], i);
            cnt[x]++;
            nex[x][cnt[x]] = i;
        }
        for (int i = 0; i < len2; i++) {
            int x = t[i] - 'a', j = i;
            int now = temp[x], pos;
            while (now < len1 and j + 1 < len2) {
                x = t[j + 1] - 'a';
                pos = upper_bound(nex[x] + 1, nex[x] + cnt[x], now) - nex[x];
                if (pos > cnt[x] or nex[x][pos] <= now)
                    break;
                else
                    j++, now = nex[x][pos];
            }
            i = j, ++ans;
        }
        cout << ans << endl;
    }
    return 0;
}

