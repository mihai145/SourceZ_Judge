#include <fstream>

using namespace std;

ifstream cin("welcome.in");
ofstream cout("welcome.out");

int main()
{
    int N;
    cin >> N;

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= i; j++)
            cout << "*";
        cout << "\n";
    }

    return 0;
}