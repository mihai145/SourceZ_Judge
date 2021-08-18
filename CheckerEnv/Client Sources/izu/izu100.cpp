#include <fstream>
#include <vector>

using namespace std;

ifstream cin("izu.in");
ofstream cout("izu.out");

int main() {
    int N; cin >> N;

    vector<int> ans;
    ans.push_back(0);

    while(ans.size() < N) {
        vector <int> aux;
        for(int el : ans) {
            aux.push_back(1 - el);
        }
        for(int el : aux) {
            ans.push_back(el);
        }
    }

    for(int i = 0; i < N; i++) {
        cout << ans[i] << ' ';
    }

    return 0;
}
