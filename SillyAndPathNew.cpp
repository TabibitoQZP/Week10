#include <cstdio>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

#define N 100050
#define LOGN 20

vector<pair<int, int>> node[N];
int depth[N] = {0};
int fa[N][LOGN] = {0};
int diff[N] = {0};
int paths[N] = {0};
int sum[N] = {0};
int ans[N] = {0};

void dfs_d(int rt, int pa, int d)
{
    depth[rt] = d;
    int i, len = node[rt].size();
    for (i = 1; i < LOGN; i++)
    {
        if (fa[rt][i - 1])
            fa[rt][i] = fa[fa[rt][i - 1]][i - 1];
        else
            break;
    }
    for (i = 0; i < len; i++)
    {
        if (node[rt][i].first == pa)
            continue;
        dfs_d(node[rt][i].first, rt, d + 1);
        fa[node[rt][i].first][0] = rt;
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
    k = log(depth[l]) / log(2);
    for (i = k + 1; i >= 0; i--)
    {
        if (fa[l][i] == fa[r][i])
            continue;
        l = fa[l][i];
        r = fa[r][i];
    }
    return fa[l][0];
}

void dfs(int rt, int pa, int p)
{
    sum[rt] = diff[rt];
    int i, len = node[rt].size();
    for (i = 0; i < len; i++)
    {
        if (node[rt][i].first == pa)
            continue;
        dfs(node[rt][i].first, rt, node[rt][i].second);
        sum[rt] += sum[node[rt][i].first];
    }
    ans[p] = sum[rt];
}

int main()
{
    int i, n, tmp0, tmp1, k;
    scanf("%d", &n);
    for (i = 1; i < n; i++)
    {
        scanf("%d%d", &tmp0, &tmp1);
        node[tmp0].push_back(make_pair(tmp1, i));
        node[tmp1].push_back(make_pair(tmp0, i));
    }
    dfs_d(1, 0, 0);
    scanf("%d", &k);
    for (i = 0; i < k; i++)
    {
        scanf("%d%d", &tmp0, &tmp1);
        diff[tmp0]++;
        diff[tmp1]++;
        diff[lca(tmp0, tmp1)] -= 2;
    }
    dfs(1, 0, 0);
    for (i = 1; i < n; i++)
    {
        printf("%d ", ans[i]);
    }
    return 0;
}