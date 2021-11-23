#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1e6 + 117;

vector<int> e[N];

int col[N], qq[N];

void dfs(int x) {
    for (auto v : e[x]) {
        dfs(v);
        if (qq[v] > qq[x]) {
            qq[x] = qq[v];
            col[x] = col[v];
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    for (int i = 2; i <= n; ++i) {
        int tmp;
        cin >> tmp;
        e[tmp].push_back(i);
    }
    for (int i = 1; i <= q; ++i) {
        int x, y;
        cin >> x >> y;
        col[x] = y;
        qq[x] = i;
    }
    dfs(1);
    for (int i = 1; i <= n; ++i) {
        cout << col[i] << (i == n ? '\n' : ' ');
    }
    return 0;
}
