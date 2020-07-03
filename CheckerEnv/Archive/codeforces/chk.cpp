#include <fstream>
#include <string>

using namespace std;

ifstream cin1("codeforces.out");
ifstream cin2("codeforces.ok");

int main()
{
    string x, y;
    bool correct = true;

    while (cin1 >> x && cin2 >> y)
    {
        if ((x.compare(y)) != 0)
        {
            correct = false;
            break;
        }
    }

    if (cin1 >> x || cin2 >> y)
        correct = false;

    return !correct;
}
