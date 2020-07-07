#include <bits/stdc++.h>
#define MOD 666013

using namespace std;

ifstream fin("nabeleaua.in");
ofstream fout("nabeleaua.out");

int dp[100005][70];
vector <int> v[100005];
bool viz[100005];
bool perechi[65][65];

void dfs(int node)
{
    viz[node] = 1;

    for(int i = 0; i < v[node].size(); i++)
        if(viz[v[node][i]] == 0)
            dfs(v[node][i]);
}


void rezolva1()
{
    int n, m;

    fin >> n >> m;

    for(int i = 1; i <= m; i++)
    {
        int x, y;

        fin >> x >> y;

        v[x].push_back(y);
        v[y].push_back(x);
    }

    int ans = 0;

    for(int i = 1; i <= n; i++)
        if(viz[i] == false)
            {
                dfs(i);
                ans++;
            }

    fout << ans;
}

void rezolva2()
{
    int k, t, p;

    fin >> k >> p >> t;

    for(int i = 1; i <= t; i++)
    {
        int x, y;

        fin >> x >> y;

        perechi[x][y] = true;
        perechi[y][x] = true;
    }

    for(int i = 1; i <= p; i++)
        dp[1][i] = 1;

    for(int i = 2; i <= k; i++)
    {
        for(int j = 1; j <= p; j++)
        {
            for(int it = 1; it <= p; it++)
                if(perechi[j][it] == false)
                    {
                        dp[i][j] += dp[i-1][it];
                        dp[i][j] %= MOD;
                    }
        }
    }

    int ans = 0;

    for(int i = 1; i <= k; i++)
        for(int j = 1; j <= p; j++)
        {
            ans += dp[i][j];
            ans %= MOD;
        }

    fout << ans;
}

int main()
{
    int p;

    fin >> p;

    if(p == 1)
        rezolva1();
    else
        rezolva2();
}

