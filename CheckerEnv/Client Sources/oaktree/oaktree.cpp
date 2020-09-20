#include <fstream>
#include <vector>

using namespace std;

ifstream cin("oaktree.in");
ofstream cout("oaktree.out");

const int MOD = 1e9 + 7;

long long N;
int T;

struct Matrix
{

    int n, m;
    int a[5][5];

    Matrix(int nn, int mm, vector <int> vals)
    {
        for(int i = 0; i < 5; i++)
            for(int j = 0; j < 5; j++)
                a[i][j] = 0;

        n = nn, m = mm;

        int k = 0;
        for(int i = 1; i <= nn; i++)
            for(int j = 1; j <= mm; j++)
                a[i][j] = vals[k++];
    }

    Matrix(int nn, int mm)
    {
        for(int i = 0; i < 5; i++)
            for(int j = 0; j < 5; j++)
                a[i][j] = 0;

        n = nn, m = mm;
    }

    Matrix operator * (const Matrix other) const
    {
        Matrix ans(n, other.m);

        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= other.m; j++)
            {
                long long f = 0;

                for(int k = 1; k <= m; k++)
                    f += 1LL * a[i][k] * other.a[k][j];

                ans.a[i][j] = f % MOD;
            }

        return ans;
    }
};

Matrix lgPut(Matrix base, long long exp)
{
    vector <int> I;
    I.push_back(1), I.push_back(0), I.push_back(0), I.push_back(0), I.push_back(1), I.push_back(0), I.push_back(0), I.push_back(0), I.push_back(1);
    Matrix ans(3, 3, I), aux = base;

    for(long long i = 1LL; i <= exp; i <<= 1)
    {
        if(i & exp)
            ans = ans * aux;

        aux = aux * aux;
    }

    return ans;
}

int main()
{
    cin >> N >> T;

    if(N == 1)
    {
        cout << 1 << '\n';
        return 0;
    }

    if(N == 2)
    {
        if(T == 2) cout << 1 << '\n';
        else cout << 2 << '\n';
        return 0;
    }

    if(T == 1)
    {
        cout << N % MOD << '\n';
        return 0;
    }

    vector <int> a;
    a.push_back(1), a.push_back(1), a.push_back(2);
    Matrix A(1, 3, a);

    vector <int> z;
    z.push_back(0), z.push_back(1), z.push_back(1), z.push_back(1), z.push_back(1), z.push_back(1), z.push_back(0), z.push_back(0), z.push_back(1);
    Matrix Z(3, 3, z);

    Z = lgPut(Z, N - 2);
    A = A * Z;

    if(T == 2)
        cout << A.a[1][2] << '\n';
    else
        cout << A.a[1][3] << '\n';

    return 0;
}
