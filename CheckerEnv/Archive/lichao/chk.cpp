#include <fstream>

using namespace std;

ifstream cin1("lichao.out");
ifstream cin2("lichao.ok");

int main()
{
    long long x, y;
    bool correct = true;

    while(cin1 >> x && cin2 >> y) {
        if(x != y) {
            correct = false;
            break;
        }
    }

    if(cin1 >> x || cin2 >> y)
        correct = false;

    return !correct;
}