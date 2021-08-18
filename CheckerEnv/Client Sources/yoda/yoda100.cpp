#include <fstream>
#include <deque>

using namespace std;

class InParser {
private:
	FILE *fin;
	char *buff;
	int sp;

	char read_ch() {
		++sp;
		if (sp == 4096) {
			sp = 0;
			fread(buff, 1, 4096, fin);
		}
		return buff[sp];
	}

public:
	InParser(const char* nume) {
		fin = fopen(nume, "r");
		buff = new char[4096]();
		sp = 4095;
	}

	InParser& operator >> (int &n) {
		char c;
		while (!isdigit(c = read_ch()) && c != '-');
		int sgn = 1;
		if (c == '-') {
			n = 0;
			sgn = -1;
		} else {
			n = c - '0';
		}
		while (isdigit(c = read_ch())) {
			n = 10 * n + c - '0';
		}
		n *= sgn;
		return *this;
	}

	InParser& operator >> (long long &n) {
		char c;
		n = 0;
		while (!isdigit(c = read_ch()) && c != '-');
		long long sgn = 1;
		if (c == '-') {
			n = 0;
			sgn = -1;
		} else {
			n = c - '0';
		}
		while (isdigit(c = read_ch())) {
			n = 10 * n + c - '0';
		}
		n *= sgn;
		return *this;
	}
};

ofstream cout("yoda.out");

const int NMAX = 2000;
const int INF = 1e9;

int a[NMAX + 2][NMAX + 2], dist[NMAX + 2][NMAX + 2];
int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};

struct state {
    pair <int, int> cell;
    int dist;

    bool operator < (const state other) {
        return dist < other.dist;
    }
};

int main() {
    InParser cin("yoda.in");

    int N, M, xi, yi, xf, yf, k;
    cin >> N >> M >> xi >> yi >> xf >> yf >> k;

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cin >> a[i][j];
            dist[i][j] = INF;
        }
    }

    deque<state> q1, q2;
    q1.push_back({{xi, yi}, 0});

    while(q1.size() + q2.size() > 0) {
        state current;

        if(q1.size() == 0) {
            current = q2.front();
            q2.pop_front();
        } else if(q2.size() == 0) {
            current = q1.front();
            q1.pop_front();
        } else {
            if(q1.front() < q2.front()) {
                current = q1.front();
                q1.pop_front();
            } else {
                current = q2.front();
                q2.pop_front();
            }
        }

        if(dist[current.cell.first][current.cell.second] != INF) {
            continue;
        }

        dist[current.cell.first][current.cell.second] = current.dist;

        for(int i = 0; i < 4; i++) {
            int nx = current.cell.first + dx[i];
            int ny = current.cell.second + dy[i];

            if(1 <= nx && nx <= N && 1 <= ny && ny <= M) {
                if(a[current.cell.first][current.cell.second] == a[nx][ny]) {
                    q1.push_back({{nx, ny}, current.dist + 1});
                } else {
                    q2.push_back({{nx, ny}, current.dist + k});
                }
            }
        }
    }

    cout << dist[xf][yf];

    return 0;
}
