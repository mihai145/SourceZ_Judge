#include <bits/stdc++.h>
using namespace std;

ifstream fin("codeforces.in");
ofstream fout("codeforces.out");

struct elem
{
    int rat, zi;
    double panta;
}vlad[1000005];
elem mari[1000005], slope[1000005];

inline bool cmp(const elem &a, const elem &b)
{
    if(a.panta == b.panta)
        if(mari[a.zi].zi == mari[b.zi].zi)
            return mari[a.rat].zi < mari[b.rat].zi;
        else
            return mari[a.zi].zi < mari[b.zi].zi;

    return a.panta < b.panta;
}



void rezolva1()
{
    int n, m;

    fin >> n;

    int maxm = 0, maxv = 0;

    for(int i = 1; i <= n; i++)
        {
            fin >> mari[i].rat >> mari[i].zi;
            maxm = max(mari[i].rat, maxm);
        }

    fin >> m;

    for(int i = 1; i <= m; i++)
        {
            fin >> vlad[i].rat >> vlad[i].zi;
            maxv = max(vlad[i].rat, maxv);
        }

    if(maxm < maxv)
        fout << "vladutz_piele" << '\n';
    else
        if(maxm > maxv)
        fout << "AlexMari" << '\n';
    else
        fout << "egalitate" << '\n';

    maxm = 0, maxv = 0;

    for(int i = 2; i <= n; i++)
        maxm = max(maxm, mari[i].rat - mari[i - 1].rat);

    for(int i = 2; i <= m; i++)
        maxv = max(maxv, vlad[i].rat - vlad[i - 1].rat);

    if(maxm < maxv)
        fout << "vladutz_piele" << '\n';
    else
        if(maxm > maxv)
        fout << "AlexMari" << '\n';
    else
        fout << "egalitate" << '\n';

    maxv = maxm = 0;

    for(int i = 2; i <= n; i++)
    {
        if(mari[i].zi > vlad[m].zi || mari[i].zi < vlad[1].zi)
            continue;

        int st = 1, dr = m, mij = (st + dr) / 2, poz;

        while(st <= dr)
        {
            if(vlad[mij].zi == mari[i].zi)
                {
                    poz = mij;
                    break;
                }

            if(vlad[mij].zi < mari[i].zi)
                {
                    st = mij + 1;
                    poz = st;
                }
            else
                dr = mij - 1;

            mij =(st + dr) / 2;
        }

        if(poz == 1)
            continue;

        if(vlad[poz].zi == mari[i].zi)
        {
        if(vlad[poz].rat - vlad[poz - 1].rat > mari[i].rat - mari[i - 1].rat)
            maxv++;
        if(vlad[poz].rat - vlad[poz - 1].rat < mari[i].rat - mari[i - 1].rat)
            maxm++;
        }
    }

    if(maxm < maxv)
        fout << "vladutz_piele" << '\n';
    else
        if(maxm > maxv)
        fout << "AlexMari" << '\n';
    else
        fout << "egalitate" << '\n';

}

void rezolva2()
{
    int n, m, t;

    fin >> n;

    for(int i = 1; i <= n; i++)
        fin >> mari[i].rat >> mari[i].zi;

    fin >> m;

    for(int i = 1; i <= m; i++)
        fin >> vlad[i].rat >> vlad[i].zi;

    int k = 0;

    for(int i = 1; i <= n; i++)
        for(int j = i + 1; j <= n; j++)
            {
                slope[++k].panta = (double)(mari[j].rat - mari[i].rat) / (double)(mari[j].zi - mari[i].zi);
                slope[k].rat = i;
                slope[k].zi = j;
            }

    sort(slope + 1, slope + k + 1, cmp);

    fin >> t;

    for(int i = 1; i <= t; i++)
    {
        int op;

        fin >> op;

        if(op == 1)
        {
            int x, y;

            fin >> x >> y;

            double pan = (double) (vlad[y].rat - vlad[x].rat) / (double)(vlad[y].zi - vlad[x].zi);

            int ans = 0;

            for(int j = 1; j <= k; j++)
                if(slope[j].panta >= pan)
                    break;
            else
                if(mari[slope[j].zi].zi <= vlad[y].zi)
                    ans++;

            fout << ans << '\n';
        }
        else
        {
            int x, y, kk, j;

            fin >> x >> y >> kk;

            double pan = (double) (vlad[y].rat - vlad[x].rat) / (double)(vlad[y].zi - vlad[x].zi);

            int pas = 0;

            for(j = 1; j <= k; j++)
                if(mari[slope[j].zi].zi <= vlad[y].zi)
                    {
                        pas++;
                        if(pas == kk)
                            break;
                    }

            if(pas == kk && slope[j].panta < pan)
                fout << slope[j].rat << " " << slope[j].zi << '\n';
            else
                fout << -1 << '\n';
        }
    }

}

int main()
{
    int p;

    fin >> p;

    if(p == 1)
        rezolva1();
    else
        rezolva2();
    return 0;
}
