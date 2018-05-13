#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;
#define INF 99999999
const int maxn =250;
const int maxm =250;
const int  oo = 0x7fffffff;
struct list
{
    int x;
    int h;
    bool friend operator <(const list &a,const list &b){
        return a.h<b.h;
    }
}q;
struct push_relablel//最高标号预流推进算法，时间复杂度O(n*n*sqrt（m）)
{
    int res[maxn][maxn];//残留网络
    int h[maxn];//高度
    int ef[maxn];//余流
    int n;//点数
    int max_flow;//最大流
    // queue<int>que;//活动定点队列
    priority_queue<list>que;
    int u,v,p,i;
    int vis[maxn];
    void init(int x){
        n=x;
        memset(h,0,sizeof(h));
        memset(ef,0,sizeof(ef));
        memset(res,0,sizeof(res));
    }
    void add(int u,int v,int w){
        res[u][v]+=w;
    }
    int ans(int s,int t){
        max_flow=0;
        h[s]=n;
        ef[s]=oo;ef[t]=-oo;
        while(!que.empty())que.pop();
        q.x=s;
        q.h=h[s];
        que.push(q);
        while(!que.empty())
        {
            q=que.top();
            que.pop();
            u=q.x;
            for(i=1;i<=n;i++)
            {
                v=i;
                if(res[u][v]<ef[u])p=res[u][v];
                else p=ef[u];
                if(p>0&&(u==s||h[u]==h[v]+1))
                {
                    res[u][v]-=p;res[v][u]+=p;
                    if(v==t)max_flow+=p;
                    ef[u]-=p;ef[v]+=p;
                    if(v!=s&&v!=t)
                    {
                        q.x=v;
                        q.h=h[v];
                        que.push(q);
                    }
                }
            }
            if(u!=s&&u!=t&&ef[u]>0)
            {
                h[u]++;
                q.x=u;
                q.h=h[u];
                que.push(q);
            }
        }
        return max_flow;
    }
}G;
int main()
{
    int m,n,u,v,w;
    while(~scanf("%d%d",&m,&n))
    {
        G.init(n);
        while(m--)
        {
            scanf("%d%d%d",&u,&v,&w);
            G.add(u,v,w);
        }
        cout<<G.ans(1,n)<<endl;
    }
    return 0;
}
