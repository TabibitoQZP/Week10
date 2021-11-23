#include <bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr int N = 1e5 + 117;

priority_queue<pair<ll, int> > pq;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        ll w;
        cin >> w;
        pq.push(make_pair(-w, 0));
    }
    int zeros = (((pq.size() - 1) / (k - 1) + 1) * (k - 1) - (pq.size() - 1)) % (k - 1);
    while (zeros--) {
        pq.push(make_pair(0, 0));
    }
    // while ((pq.size() - 1) % (k - 1) != 0) pq.push(make_pair(0, 0));
    ll ans = 0;
    while (pq.size() >= k) {
        ll sum = 0;
        int h = 0;
        for (int i = 1; i <= k; ++i) {
            pair<ll, int> pp = pq.top();
            pq.pop();
            sum -= pp.first;
            h = max(h, -pp.second);
        }
        ans += sum;
        pq.push(make_pair(-sum, -h - 1));
    }
    cout << ans << endl << -pq.top().second << endl;
    return 0;
}
