#include <fstream>
#include <cstring>
#include <string>

using namespace std;

ifstream cin1("welcome.out");
ifstream cin2("welcome.ok");

int main()
{
    bool isCorrect = true;

    char ok[102], out[102];

    while(cin2.getline(ok, sizeof(ok)))
    {
        cin1.getline(out, sizeof(out));

        if(strlen(ok) != strlen(out)) {
            isCorrect = false;
            break;
        }

        for(int i = 0; i < (int)strlen(ok); i++)
            if(ok[i] != out[i]) {
                isCorrect = false;
                break;
            }
    }

    string leftOver;
    if(cin1 >> leftOver) {
        isCorrect = false;
    }

    return !isCorrect;
}