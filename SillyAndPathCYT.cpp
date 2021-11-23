#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int n, k;
vector<int> a[100050];
int val[100050];
int fa[100050][18];
int depth[100050];
int x[100050];
int y[100050];
int r[100050];
int pro[100050];
int ans[100050];

inline bool scan_d(int &ret)
{
    char c;
    int sgn;
    if (c = getchar(), c == EOF)
        return 0; // EOF
    while (c != '-' && (c < '0' || c > '9'))
        c = getchar();
    sgn = (c == '-') ? -1 : 1;
    ret = (c == '-') ? 0 : (c - '0');
    while (c = getchar(), c >= '0' && c <= '9')
        ret = ret * 10 + (c - '0');
    ret *= sgn;
    return 1;
}

void dfs(int x)
{
    for (int i = 1; i <= 17; ++i)
    {
        if (fa[x][i - 1])
            fa[x][i] = fa[fa[x][i - 1]][i - 1];
        else
            break;
    }
    for (int i = 0; i < a[x].size(); ++i)
    {
        int nxt = a[x][i];
        if (nxt == fa[x][0])
            continue;
        fa[nxt][0] = x;
        depth[nxt] = depth[x] + 1;
        dfs(nxt);
    }
}

int dfs_for_ans(int x, int pa)
{
    if (a[x].size() == 1 && a[x][0] == pa)
    {
        ans[r[x]] += pro[x];
        return pro[x];
    }
    for (int i = 0; i < a[x].size(); ++i)
    {
        int nxt = a[x][i];
        if (nxt == pa)
            continue;
        pro[x] += dfs_for_ans(nxt, x);
    }
    ans[r[x]] += pro[x];
    return pro[x];
}

int LCA(int p, int q)
{
    if (depth[p] < depth[q])
        swap(p, q);
    int del = depth[p] - depth[q];
    for (int i = 0; i <= (int)log2(del); i++)
    {
        if ((1 << i) & del)
            p = fa[p][i];
    }
    if (p == q)
        return p;
    else
    {
        for (int i = 16; i >= 0; --i)
        {
            if (fa[p][i] != fa[q][i])
            {
                p = fa[p][i];
                q = fa[q][i];
            }
        }
        return fa[p][0];
    }
}

int main()
{
    scan_d(n);
    for (int i = 0; i < n - 1; ++i)
    {
        scan_d(x[i]);
        scan_d(y[i]);
        a[x[i]].push_back(y[i]);
        a[y[i]].push_back(x[i]);
        val[i] = i;
    }
    dfs(1);
    for (int i = 0; i < n - 1; ++i)
    {
        if (depth[x[i]] > depth[y[i]])
        {
            r[x[i]] = val[i];
        }
        else
        {
            r[y[i]] = val[i];
        }
    }
    scan_d(k);
    for (int i = 0; i < k; ++i)
    {
        int p, q;
        scan_d(p);
        scan_d(q);
        int lca = LCA(p, q);
        pro[p]++;
        pro[q]++;
        pro[lca] -= 2;
    }
    dfs_for_ans(1, 0);
    for (int i = 0; i < n - 1; ++i)
    {
        printf("%d ", ans[i]);
    }
    return 0;
}