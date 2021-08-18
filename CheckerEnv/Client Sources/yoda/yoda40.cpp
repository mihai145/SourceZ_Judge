#include <fstream>
#include <queue>

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

    bool operator < (const state other) const {
        return dist > other.dist;
    }
};

int main()
{
    InParser cin("yoda.in");
    int N, M, xi, yi, xf, yf, k;
    cin >> N >> M >> xi >> yi >> xf >> yf >> k;

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cin >> a[i][j];
            dist[i][j] = INF;
        }
    }

    priority_queue<state> pq;
    pq.push({{xi, yi}, 0});

    while(!pq.empty()) {
        pair <int, int> cell = pq.top().cell;
        int curr_dist = pq.top().dist;
        pq.pop();

        if(dist[cell.first][cell.second] != INF) {
            continue;
        }

        dist[cell.first][cell.second] = curr_dist;

        for(int i = 0; i < 4; i++) {
            int nx = cell.first + dx[i];
            int ny = cell.second + dy[i];

            if(1 <= nx && nx <= N && 1 <= ny && ny <= M) {
                if(a[cell.first][cell.second] == a[nx][ny]) {
                    pq.push({{nx, ny}, curr_dist + 1});
                } else {
                    pq.push({{nx, ny}, curr_dist + k});
                }
            }
        }
    }

    cout << dist[xf][yf] << '\n';

    return 0;
}
