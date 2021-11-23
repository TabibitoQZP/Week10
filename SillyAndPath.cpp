/*
参考 https://blog.csdn.net/Tekim/article/details/77750093
*/
#include <cstdio>
#include <vector>
#include <cmath>
#include <utility>

#define MAXSIZE 100050
#define LOGMAX 20

using namespace std;

vector<pair<int, int>> node[MAXSIZE];
int x[MAXSIZE];
int y[MAXSIZE];
int road[MAXSIZE];
int depth[MAXSIZE];
int fa[MAXSIZE][LOGMAX];
int dif[MAXSIZE];
int sum[MAXSIZE];
int ans[MAXSIZE];

void dfs_d(int nd, int fa_nd, int d)
{
    depth[nd] = d;
    int i, len = node[nd].size();
    for (i = 1; i < LOGMAX; i++)
    {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    }
    for (i = 0; i < n; i++)
    {
        if (node[nd][i] == fa_nd)
            continue;
        dfs_d(node[nd][i], nd, d + 1);
        fa[nd][0] = fa_nd;
    }
}

int lca(int l, int r)
{
    if (depth[l] < depth[r])
    {
        swap(l, r);
    }
    int i, k = log(depth[r] - depth[l] + 1) / log(2);
    for (i = 0; i <= k + 1; i++)
    {
        if ((1 << i) & (depth[r] - depth[l]))
            r = fa[r][i];
        if (depth[r] == depth[l])
            break;
    }
    if (l == r)
        return l;
    k = log(d[l]) / log(2);
    for (i = k + 1; i >= 0; i--)
    {
        if (fa[l][i] == fa[r][i])
            continue;
        l = fa[l][i];
        r = fa[r][i];
    }
    return fa[l][0];
}

int dfs(int nd, int fa_nd)
{
    int i, len = node[nd].size();
    sum[nd] = dif[nd];
    for (i = 0; i < len; i++)
    {
        dfs(node[nd][i], nd);
        sum[nd] += sum[node[nd][i]];
    }
}

int main()
{
    int i, n, tmp0, tmp1, k, anc; // number of cities, k sillies.
    scanf("%d", &n);
    for (i = 1; i < n; i++)
    {
        scanf("%d%d", &tmp0, &tmp1);
        x[i] = tmp0;
        y[i] = tmp1;
        node[tmp0].push_back(tmp1);
        node[tmp1].push_back(tmp0);
    }
    dfs_d(1, 0, 0);
    for (i = 1; i < n; i++)
    {
        if (depth[x[i]] > depth[y[i]])
        {
            road[x[i]] = i;
        }
        else
        {
            road[y[i]] = i;
        }
    }
    scanf("%d", &k);
    for (i = 0; i < k; i++)
    {
        scanf("%d%d", &tmp0, &tmp1);
        anc = lca(tmp0, tmp1);
        dif[tmp0]++;
        dif[tmp1]++;
        dif[anc] -= 2;
    }
    dfs(1, 0);
    return 0;
}