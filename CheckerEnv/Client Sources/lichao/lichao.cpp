#include <fstream>
#include <map>

using namespace std;

ifstream cin("lichao.in");
ofstream cout("lichao.out");

int T, K, N;
bool special[35];
map < pair < int, int >, bool > win;

bool CanWin(int N, int msk)
{

    if(N <= 0)
        return 0;

    msk = msk & ((1 << N) - 1);

    if(win[ {N, msk}])
        return win[ {N, msk}];

    bool winning = false;
    for(int i = 1; i <= min(N, K); i++)
    {
        if(special[i] == 0)
        {
            bool nxt = CanWin(N - i, msk);
            if(nxt == false)
            {
                winning = true;
                break;
            }
        }
        else
        {
            if(!(msk & (1 << (i - 1))))
            {
                bool nxt = CanWin(N - i, msk ^ (1 << (i - 1)));
                if(nxt == false)
                {
                    winning = true;
                    break;
                }
            }
        }
    }

    return win[ {N, msk}] = winning;
}

int main()
{
    cin >> T >> K;

    for(int i = 1; i <= K; i++)
        cin >> special[i];

    for(int i = 1; i <= T; i++)
    {
        cin >> N;
        cout << CanWin(N, 0) << ' ';
    }

    return 0;
}
