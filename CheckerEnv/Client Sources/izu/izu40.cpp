#include <fstream>
#include <vector>

using namespace std;

ifstream cin("izu.in");
ofstream cout("izu.out");

bool is_ok(int mask, int n)
{
    vector <int> ans;
    ans.push_back(0);

    for(int i = 0; i < n; i++) {
        ans.push_back((mask & (1 << i)) > 0);
    }

    for(int i = 1; i <= n - 2; i++) {
        for(int sz = 1; i + 3 * sz - 1 <= n; sz++) {
            bool all_equal = true;
            for(int f = 1; f <= sz; f++) {
                if(ans[i + f - 1] != ans[i + f - 1 + sz] || ans[i + f - 1] != ans[i + f - 1 + 2 * sz]) {
                    all_equal = false;
                    break;
                }
            }

            if(all_equal == true) {
                return false;
            }
        }
    }

    return true;
}

void print_mask(int mask, int n)
{
    for(int i = 0; i < n; i++) {
        cout << ((mask & (1 << i)) > 0) << ' ';
    }
}

int main()
{
    int N;
    cin >> N;

    for(int mask = 0; mask < (1 << N); mask++) {
        if(is_ok(mask, N)) {
            print_mask(mask, N);
            return 0;
        }
    }

    return 0;
}
