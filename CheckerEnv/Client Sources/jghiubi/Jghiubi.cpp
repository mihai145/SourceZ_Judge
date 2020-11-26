#include <fstream>

using namespace std;

ifstream cin("jghiubi.in");
ofstream cout("jghiubi.out");

const int NMAX = 700;
const int MOD = 1e9 + 7;

int N, A, B, C;
char s[NMAX + 2];
int spa[NMAX + 2], spb[NMAX + 2], spc[NMAX + 2], spx[NMAX + 2];

int comb[NMAX + 2][NMAX + 2];

void PrecComb()
{

    comb[0][0] = 1;

    for(int i = 1; i <= N; i++)
    {
        comb[i][0] = comb[i][i] = 1;

        for(int j = 1; j < i; j++)
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MOD;
    }
}

int Comb(int n, int k)
{
    if(k > n)
        return 0;

    if(n < 1)
        return 0;

    return comb[n][k];
}

int main()
{
    cin >> N >> A >> B >> C >> (s + 1);

    PrecComb();

    /*
    for(int i = 1; i <= 10; i++) {
        for(int j = 0; j <= i; j++)
            cout << comb[i][j] << "     ";
        cout << '\n';
    }
    */

    for(int i = 1; i <= N; i++)
    {
        if(s[i] == 'a') spa[i] = 1;
        else if(s[i] == 'b') spb[i] = 1;
        else if(s[i] == 'c') spc[i] = 1;
        else spx[i] = 1;

        spa[i] += spa[i - 1];
        spb[i] += spb[i - 1];
        spc[i] += spc[i - 1];
        spx[i] += spx[i - 1];
    }

    long long sol = 0;

    if(B == 1)
    {
        for(int i = 1; i <= N; i++)
            if(s[i] == 'b' || s[i] == '*')
            {
                int nrLeft = spa[i - 1] + spx[i - 1];
                int lf = Comb(nrLeft, A);

                int nrRight = spc[N] - spc[i] + spx[N] - spx[i];
                int rg = Comb(nrRight, C);

                sol = (sol + (1LL * lf * rg) % MOD) % MOD;
            }
    }
    else
    {
        for(int i = 1; i <= N; i++)
            for(int j = i + 1; j <= N; j++)
                if((s[i] == 'b' || s[i] == '*') && (s[j] == 'b' || s[j] == '*'))
                {
                    int nrLeft = spa[i - 1] + spx[i - 1];
                    int lf = Comb(nrLeft, A);

                    int nrRight = spc[N] - spc[j] + spx[N] - spx[j];
                    int rg = Comb(nrRight, C);

                    int nrMiddle = spb[j] - spb[i] + spx[j] - spx[i];
                    int md = Comb(nrMiddle, B - 2);

                    int add = (1LL * lf * rg) % MOD;
                    add = (1LL * add * md) % MOD;

                    sol = (sol + add) % MOD;
                }
    }

    cout << sol << '\n';

    return 0;
}
