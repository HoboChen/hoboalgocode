#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>
using namespace std;

const int maxn =1110;
const int maxm =220000;
const int oo = 1<<29;

int cnt, head[maxn], dis[maxn];
int cur[maxn], pre[maxn], gap[maxn], aug[maxn];

struct node {
    int u, v, w, next;
}edge[maxm];

void init()
{
    cnt = 0;
    memset(head,-1,sizeof(head));
}
void add(int u, int v, int w, int rw = 0)
{
    edge[cnt].u = u;
    edge[cnt].v = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
    edge[cnt].u = v;
    edge[cnt].v = u;
    edge[cnt].w = rw;
    edge[cnt].next = head[v];
    head[v] = cnt++;
}

int sap(int s, int e, int n)
{
    int max_flow = 0, u = s;
    int mindis;
    for(int i = 0; i <= n; i++)
    {
        cur[i] = head[i];
        dis[i] = 0;
        gap[i] = 0;
    }
    aug[s] = oo;
    pre[s] = -1;
    gap[0] = n;
    while(dis[s]<n)
    {
        bool flag = false;
        if(u==e)
        {
            max_flow += aug[e];
            for(int v = pre[e]; v != -1; v = pre[v])
            {
                int id = cur[v];
                edge[id].w -= aug[e];
                edge[id^1].w += aug[e];
                aug[v] -= aug[e];
                if(edge[id].w==0) u = v;
            }
        }
        for(int id = cur[u]; id != -1; id = edge[id].next)
        {
            int v = edge[id].v;
            if(edge[id].w>0 && dis[u]==dis[v]+1)
            {
                flag = true;
                pre[v] = u;
                cur[u] = id;
                aug[v] = std::min(aug[u], edge[id].w);
                u = v;
                break;
            }
        }
        if(flag==false)
        {
            if(--gap[dis[u]]==0) break;
            mindis = n;
            cur[u] = head[u];
            for(int id = head[u]; id != -1; id = edge[id].next)
            {
                int v = edge[id].v;
                if(edge[id].w>0 && dis[v]<mindis)
                {
                    mindis = dis[v];
                    cur[u] = id;
                }
            }
            dis[u] = mindis+1;
            ++gap[dis[u]];
            if(u!=s) u = pre[u];
        }
    }
    return max_flow;
}

int main()
{
    int m,n,u,v,w;
    while(~scanf("%d%d",&m,&n))
    {
        init();
        while(m--)
        {
            scanf("%d%d%d",&u,&v,&w);
            add(u,v,w);
        }
        cout<<sap(1,n,n)<<endl;
    }
    return 0;
}
