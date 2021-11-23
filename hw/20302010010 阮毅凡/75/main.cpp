#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1e5 + 117;

vector<pair<int, int> > e[N];

int t, lg2[N], n, dif[N], dep[N], f[N][30], ans[N], sum[N];

void dfs(int x, int fa, int d) {
    dep[x] = d;
    f[x][0] = fa;
    for (int i = 1; i <= t; ++i) {
        f[x][i] = f[f[x][i - 1]][i - 1];
    }
    for (auto v : e[x]) {
        if (v.first != fa) {
            dfs(v.first, x, d + 1);
        }
    }
}

void init() {
    for (int i = 2; i <= n; ++i) {
        lg2[i] = lg2[i >> 1] + 1;
    }
    t = lg2[n] + 1;
    dfs(1, 0, 1);
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    for (int i = t; i >= 0; i--) {
        if (dep[f[a][i]] >= dep[b]) a = f[a][i];
    }
    if (a == b) {
        return a;
    }
    for (int i = t; i >= 0; i--) {
        if (f[a][i] != f[b][i]) {
            a = f[a][i];
            b = f[b][i];
        }
    }
    return f[a][0];
}

void add(int x, int y) {
    ++dif[x], ++dif[y];
    dif[lca(x, y)] -= 2;
}

void dfs2(int x, int fa, int edge) {
    sum[x] = dif[x];
    for (auto v : e[x]) {
        if (v.first != fa) {
            dfs2(v.first, x, v.second);
            sum[x] += sum[v.first];
        }
    }
    ans[edge] = sum[x];
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(make_pair(v, i));
        e[v].push_back(make_pair(u, i));
    }
    init();
    int k;
    cin >> k;
    while (k--) {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }
    dfs2(1, 0, 0);
    for (int i = 1; i < n; ++i) {
        cout << ans[i] << (i == (n - 1) ? '\n' : ' ');
    }
    return 0;
}