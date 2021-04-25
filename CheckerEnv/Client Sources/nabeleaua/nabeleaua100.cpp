#include<fstream>
#include<vector>
#define MOD 666013
using namespace std;
ifstream f("nabeleaua.in");
ofstream g("nabeleaua.out");
vector<int>a[100002];
bool viz[100002];
long long sol[62][62],b[62][62],c[62][62],nabeleaua[62][62];
int p;

void inmultire_matrice(long long a[62][62],long long b[62][62])
{
    long long i,j,k,s;
    for(i=0;i<=p;i++)
    for(j=0;j<=p;j++)
    {
        s=0;
        for(k=0;k<=p;k++)
            s+=a[i][k]*b[k][j];
        c[i][j]=s%MOD;
    }
    for(i=0;i<=p;i++)
    for(j=0;j<=p;j++)
        a[i][j]=c[i][j];
}

void pow_log(long long k)
{
    while(k>0)
    {
        if(k%2==1)
            inmultire_matrice(nabeleaua,b);
        inmultire_matrice(b,b);
        k/=2;
    }
}

void dfs(int x)
{
    int i,l=a[x].size();
    viz[x]=1;
    for(i=0;i<l;i++)
    if(viz[a[x][i]]==0)
        dfs(a[x][i]);
}

int main()
{
    int c,n,m,i,x,y,t,j,iubite=0;
    long long k;
    f>>c;
    if(c==1)
    {
        f>>n>>m;
        for(i=1;i<=m;i++)
        {
            f>>x>>y;
            a[x].push_back(y);
            a[y].push_back(x);
        }
        for(i=1;i<=n;i++)
        if(viz[i]==0)
            dfs(i),iubite++;
        g<<iubite;
    }
    else
    {
        f>>k>>p>>t;
        for(i=0;i<=p;i++)
            nabeleaua[i][i]=1;
        for(i=1;i<=t;i++)
        {
            f>>x>>y;
            b[x][y]=1;
            b[y][x]=1;
        }
        for(i=1;i<=p;i++)
            sol[1][i]=1;
        for(i=0;i<=p;i++)
            b[i][0]=1;
        for(i=1;i<=p;i++)
        for(j=1;j<=p;j++)
            b[i][j]=1-b[i][j];
        pow_log(k);
        inmultire_matrice(sol,nabeleaua);
        g<<sol[1][0];
    }
    return 0;
}
