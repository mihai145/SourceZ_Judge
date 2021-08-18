#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

ifstream cin1("izu.out");
ifstream cin2("izu.ok");

int main()
{
    vector<int> ans;
    ans.push_back(0);

    int N; cin2 >> N;

    int x;
    while(cin1 >> x) {
        if(x != 0 && x != 1) {
            return 1;
        }
        ans.push_back(x);
    }

    if((int)ans.size() != N + 1) {
        return 1;
    }

    for(int i = 1; i <= N - 2; i++) {
        for(int sz = 1; i + 3 * sz - 1 <= N; sz++) {
            bool all_equal = true;
            for(int f = 1; f <= sz; f++) {
                if(ans[i + f - 1] != ans[i + f - 1 + sz] || ans[i + f - 1] != ans[i + f - 1 + 2 * sz]) {
                    all_equal = false;
                    break;
                }
            }

            if(all_equal == true) {
                return 1;
            }
        }
    }

    return 0;
}