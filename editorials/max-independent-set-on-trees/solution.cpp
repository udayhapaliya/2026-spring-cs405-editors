#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;

vector<int> adj[MAXN];
long long dp[MAXN][2];
int n;

void dfs(int u, int parent) {
    dp[u][0] = 0;   // exclude u
    dp[u][1] = 1;   // include u

    for (int v : adj[u]) {
        if (v == parent) continue;

        dfs(v, u);

        dp[u][1] += dp[v][0];
        dp[u][0] += max(dp[v][0], dp[v][1]);
    }
}

int main() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);
    cout << max(dp[1][0], dp[1][1]) << "\n";

    return 0;
}
