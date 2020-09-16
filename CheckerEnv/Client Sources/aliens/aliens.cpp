#include <fstream>
#include <vector>

using namespace std;

//ifstream cin("aliens.in");
//ofstream cout("aliens.out");

ifstream cin("aliens.in");
ofstream cout("aliens.out");

const int NMAX = 100000;

int N, Q;
int ans;

int dad[NMAX + 2], rnk[NMAX + 2], dim[NMAX + 2];

int Root(int node)
{
    if(node == dad[node])
        return node;

    return dad[node] = Root(dad[node]);
}

void Join(int p, int q)
{
    p = Root(p);
    q = Root(q);

    if(p != q)
    {
        if(rnk[p] > rnk[q])
        {
            dad[q] = p;
            dim[p] += dim[q];
            ans = max(ans, dim[p]);
        }
        else if(rnk[p] < rnk[q])
        {
            dad[p] = q;
            dim[q] += dim[p];
            ans = max(ans, dim[q]);
        }
        else
        {
            rnk[p]++;
            dad[q] = p;
            dim[p] += dim[q];
            ans = max(ans, dim[p]);
        }
    }
}

int main()
{
    cin >> N >> Q;

    for(int i = 1; i <= N; i++)
    {
        dad[i] = i;
        rnk[i] = dim[i] = 0;
    }

    for(int i = 1; i <= Q; i++)
    {
        int t;
        cin >> t;

        if(t == 1)
        {
            int K;
            vector <int> problems;

            cin >> K;
            for(int j = 1; j <= K; j++)
            {
                int x;
                cin >> x;
                problems.push_back(x);
            }

            for(int i = 1; i < K; i++)
                Join(problems[0], problems[1]);

            dim[Root(problems[0])]++;
            ans = max(ans, dim[Root(problems[0])]);
        }
        else
            cout << ans << '\n';
    }

    return 0;
}
