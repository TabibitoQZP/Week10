#include <bits/stdc++.h>

using namespace std;

using ll = long long;

template<typename T>
inline T read() {
    T x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') {
        if (c == '-') f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
        x = x * 10 + (c & 15), c = getchar();
    return x * f;
}

constexpr int N = 5e5 + 117, T = 55;

int nex[N * 36][2], cnt, sz[N * 36];

void insert(ll s) {
    ll tmp[T];
    for (int i = 0; i < T; ++i) {
        tmp[T - i - 1] = s & 1ll;
        s >>= 1ll;
    }
    int p = 0;
    for (int i = 0; i < T; ++i) {
        int c = tmp[i];
        if (!nex[p][c]) {
            nex[p][c] = ++cnt;
        }
        p = nex[p][c];
    }
    ++sz[p];
}

void dfs(int x) {
    for (int i = 0; i < 2; ++i) {
        if (nex[x][i]) {
            dfs(nex[x][i]);
            sz[x] += sz[nex[x][i]];
        }
    }
}

ll find_k(ll s, int k) {
    ll tmp[T], ret = 0;
    for (int i = 0; i < T; ++i) {
        tmp[T - i - 1] = s & 1ll;
        s >>= 1ll;
    }
    int x = 0;
    for (int i = 0; i < T; ++i) {
        if (nex[x][0] == 0) {
            (ret <<= 1ll) |= (1 ^ tmp[i]);
            x = nex[x][1];
        } else if (nex[x][1] == 0) {
            (ret <<= 1ll) |= (0 ^ tmp[i]);
            x = nex[x][0];
        } else {
            if (tmp[i] == 0) {
                if (sz[nex[x][1]] >= k) {
                    x = nex[x][1];
                    (ret <<= 1ll) |= 1ll;
                } else {
                    k -= sz[nex[x][1]];
                    x = nex[x][0];
                    ret <<= 1ll;
                }
            } else {
                if (sz[nex[x][0]] >= k) {
                    x = nex[x][0];
                    (ret <<= 1ll) |= 1ll;
                } else {
                    k -= sz[nex[x][0]];
                    x = nex[x][1];
                    ret <<= 1ll;
                }
            }
        }
    }
    return ret;
}

int main() {
    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; ++i) {
        insert(read<ll>());
    }
    dfs(0);
    ll overall_xor = 0;
    while (m--) {
        int op = read<int>();
        if (op & 1) {
            overall_xor ^= read<ll>();
        } else {
            printf("%lld\n", find_k(overall_xor, read<int>()));
        }
    }
    return 0;
}
