#include<fstream>
#include<algorithm>
using namespace std;
ifstream f("codeforces.in");
ofstream g("codeforces.out");

struct elem
{
    int r,z;
};
elem v[4000002],w[4000002];
struct Query
{
    int q,x,y,k,index;
};
Query q[3000002];

inline bool cmp(const Query &a,const Query &b)
{
    return a.y<b.y;
}

struct evolutie
{
    long long r1,z1,r2,z2;
    int x,y;
    bool t;
};
evolutie e[4000002];

inline bool comp(const evolutie &a,const evolutie &b)
{
    return (a.r2-a.r1)*(b.z2-b.z1)<(b.r2-b.r1)*(a.z2-a.z1);
}

int N,aib[4000002],s[2002][2002][2];
pair<int,int>sol[3000002];
vector<pair<int,int>>c[4000002];

int query(int poz)
{
    int SOL=0,i;
    for(i=poz;i>=1;i-=i&-i)
        SOL+=aib[i];
    return SOL;
}

void update(int poz,int add)
{
    int i;
    for(i=poz;i<=N;i+=i&-i)
        aib[i]+=add;
}

int rez(int S)
{
    int st=1,dr=N,mij,x;
    while(st<=dr)
    {
        mij=(st+dr)/2;
        x=query(mij);
        if(x<S)
            st=mij+1;
        else
            dr=mij-1;
    }
    if(query(dr+1)>=S)
        return dr+1;
    return -1;
}

int main()
{
    int p,n,m,t,i,maxim=0,k=0,j,l,z;

    f>>p;
    f>>n;
    for(i=1;i<=n;i++)
        f>>v[i].r>>v[i].z;
    f>>m;
    for(i=1;i<=m;i++)
        f>>w[i].r>>w[i].z;
    if(p==1)
    {
        for(i=1;i<=n;i++)
        if(v[i].r>maxim)
            maxim=v[i].r,k=1;
        for(i=1;i<=m;i++)
        if(w[i].r>maxim)
            maxim=w[i].r,k=2;
        else
        if(w[i].r==maxim&&k==1)
            k=3;
        if(k==1)
            g<<"AlexMari";
        else
        if(k==2)
            g<<"vladutz_piele";
        else
            g<<"egalitate";
        g<<'\n';
        maxim=0;
        k=0;
        for(i=2;i<=n;i++)
        if(v[i].r-v[i-1].r>maxim)
            maxim=v[i].r-v[i-1].r,k=1;
        for(i=2;i<=m;i++)
        if(w[i].r-w[i-1].r>maxim)
            maxim=w[i].r-w[i-1].r,k=2;
        else
        if(w[i].r-w[i-1].r==maxim&&k==1)
            k=3;
        if(k==1)
            g<<"AlexMari";
        else
        if(k==2)
            g<<"vladutz_piele";
        else
            g<<"egalitate";
        g<<'\n';
        k=0;
        i=2;
        j=2;
        while(i<=n&&j<=m)
        {
            if(v[i].z<w[j].z)
                i++;
            else
            if(w[j].z<v[i].z)
                j++;
            else
            {
                if(v[i].r-v[i-1].r>w[j].r-w[j-1].r)
                    k++;
                else
                if(v[i].r-v[i-1].r<w[j].r-w[j-1].r)
                    k--;
                i++;
                j++;
            }
        }
        if(k>0)
            g<<"AlexMari";
        else
        if(k<0)
            g<<"vladutz_piele";
        else
            g<<"egalitate";
    }
    else
    {
        f>>t;
        for(i=1;i<=t;i++)
        {
            f>>q[i].q>>q[i].x>>q[i].y;
            if(q[i].q==2)
                f>>q[i].k;
            q[i].index=i;
        }
        sort(q+1,q+t+1,cmp);
        for(i=1;i<n;i++)
        for(j=i+1;j<=n;j++)
            e[++k]={v[i].r,v[i].z,v[j].r,v[j].z,i,j,0};
        for(i=1;i<m;i++)
        for(j=i+1;j<=m;j++)
            e[++k]={w[i].r,w[i].z,w[j].r,w[j].z,i,j,1};
        sort(e+1,e+k+1,comp);
        N=0;
        for(i=1;i<=k;i++)
        {
            N++;
            while(i<k&&(e[i].r2-e[i].r1)*(e[i+1].z2-e[i+1].z1)==(e[i+1].r2-e[i+1].r1)*(e[i].z2-e[i].z1))
            {
                s[e[i].x][e[i].y][e[i].t]=N;
                i++;
            }
            s[e[i].x][e[i].y][e[i].t]=N;
        }
        j=1;
        for(i=1;i<=t;i++)
        {
            while(j < n && v[j+1].z<=w[q[i].y].z)
            {
                j++;
                for(l=1;l<=j-1;l++)
                    update(s[l][j][0],1),c[s[l][j][0]].push_back({l,j});
            }
            if(q[i].k==0)
                sol[q[i].index].first=query(s[q[i].x][q[i].y][1]-1);
            else
            {
                z=rez(q[i].k);
                if(z>=s[q[i].x][q[i].y][1])
                    z=-1;
                if(z==-1)
                    sol[q[i].index].first=-1;
                else
                    sol[q[i].index]=c[z][q[i].k-query(z-1)-1];
            }
        }
        for(i=1;i<=t;i++)
        if(sol[i].second==0)
            g<<sol[i].first<<'\n';
        else
            g<<sol[i].first<<" "<<sol[i].second<<'\n';
    }
    return 0;
}
