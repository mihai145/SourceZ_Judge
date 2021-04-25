#include <fstream>

using namespace std;

ifstream cin("phigaro.in");
ofstream cout("phigaro.out");

const int VALMAX = 100000;

bool d[VALMAX + 2];
int phi[VALMAX + 2];

void Preproc()
{
    for(int i = 1; i <= VALMAX; i++)
        phi[i] = i;
 
    for(int i = 2; i <= VALMAX; i++)
    {
        if(!d[i])
        {
            for(int j = i; j <= VALMAX; j += i)
                d[j] = 1, phi[j] /= i, phi[j] *= (i - 1);
        }
    }
}

int main()
{
    Preproc();

    int N;
    cin >> N;

    for(int i = 1; i <= N; i++)
        cout << phi[i] << ' ';

    return 0;
}