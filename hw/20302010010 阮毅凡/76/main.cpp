#include <bits/stdc++.h>

using namespace std;

constexpr int N = 200309;

int a[N], dfn[N], la[N];

vector<int> e[N];

int cnt = 0;

void dfs(int x) {
    dfn[x] = ++cnt;
    a[cnt] = x;
    for (auto v : e[x]) {
        dfs(v);
    }
    la[x] = cnt;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    for (int i = 2; i <= n; ++i) {
        int fa;
        cin >> fa;
        e[fa].push_back(i);
    }
    dfs(1);
    while (q--) {
        int u, v;
        cin >> u >> v;
        if (dfn[u] + v - 1 > la[u]) {
            cout << "-1\n";
        } else {
            cout << a[dfn[u] + v - 1] << '\n';
        }
    }
    return 0;
}
