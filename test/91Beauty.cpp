#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

int main()
{
    int i, j, m, n, tmpInt; //m rows, n cols.
    scanf("%d%d", &m, &n);
    vector<vector<pair<int, int>>> mat;
    vector<pair<int, int>> tmpRow;
    for (i = 0; i < m; i++)
    {
        tmpRow.clear();
        for (j = 0; j < n; j++)
        {
            scanf("%d", &tmpInt);
            tmpRow.push_back(make_pair(tmpInt, i));
        }
        sort(tmpRow.begin(), tmpRow.end());
        mat.push_back(tmpRow);
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
    vector<int> p(m, 1);
    int heapMax = -1;
    for (i = 0; i < m; i++)
    {
        heap.push(mat[i][0]);
        if (mat[i][0].first > heapMax)
        {
            heapMax = mat[i][0].first;
        }
    }
    int ans = heapMax - heap.top().first;
    pair<int, int> tmpPair;
    while (true)
    {
        tmpPair = heap.top();
        if (p[tmpPair.second] < n)
        {
            heap.pop();
            if (heapMax < mat[tmpPair.second][p[tmpPair.second]].first)
            {
                heapMax = mat[tmpPair.second][p[tmpPair.second]].first;
            }
            heap.push(mat[tmpPair.second][p[tmpPair.second]]);
            if (ans > heapMax - heap.top().first)
            {
                ans = heapMax - heap.top().first;
            }
            p[tmpPair.second]++;
        }
        else
        {
            break;
        }
    }
    printf("%d", ans);
    return 0;
}