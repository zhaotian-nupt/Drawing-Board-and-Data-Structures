#include "data.h"
#include <algorithm>

Data::Data()
{
    pnum=0;
    rootnum=0;
    level=0;
    une_num=0;
    etype=0;
    start=1;
}

void Data::clear()
{
    for(int i=1;i<=pnum;i++)
        E[i].clear();
    pnum=0;
    rootnum=0;
    level=0;
    une_num=0;
    etype=0;
    start=1;
    ifpaint=true;

}

void Data::addedge(int u,int v,int w)
{
    E[u].push_back(Edge(v,w));
}

void Data::addundiredge(int u, int v, int w)
{
    une_num++;
    UndirE[une_num].u=u;
    UndirE[une_num].v=v;
    UndirE[une_num].w=w;
}

int Data::judge()
{
    if(etype==1)
    {
        for(int i=1;i<100;i++)
            par[i]=i;
        bool ok=true;
        for(int i=1;i<=pnum;i++)
        {
            for(int j=0;j<E[i].size();j++)
            {
                if(par[E[i][j].v]!=E[i][j].v)
                {
                    ok=false;
                }
                int now=i;
                int last=i;
                while(par[now]!=now)
                {
                    last=now;
                    now=par[now];
                    if(last==par[now])
                    {
                        ok=false;
                        break;
                    }
                    if(now==E[i][j].v)
                    {
                        ok=false;
                        break;
                    }
                }
                if(ok)
                    par[E[i][j].v]=i;
            }
        }
        if(!ok)
        {
            type=3;
            return 3;
        }
        for(int i=1;i<=pnum;i++)
        {
            callevel(i);
            if(level<p[i].level)
                level=p[i].level;
        }
        rootnum=0;
        for(int i=1;i<=pnum;i++)
        {
            if(par[i]==i)
            {
                root[++rootnum]=i;
                p[i].isroot=true;
            }
        }
        if(rootnum==1)
        {
            type=1;
            return 1;
        }
        else
        {
            type=2;
            return 2;
        }
    }
    else if(etype==2)
    {
        type=3;
        return 3;
    }

}

void Data::callevel(int x)
{
    if(par[x]==x)
        p[x].level=1;
    else
    {
        int now=x;
        int ans=1;
        while(par[now]!=now)
        {
            ans++;
            now=par[now];
        }
        p[x].level=ans;
    }
}

void Data::initxulie()
{
    int cnt=1;
    bool vis[100];
    memset(vis,false,sizeof(vis));
    if(type==1)
    {
        QStack <int> qs;
        qs.push(root[1]);
        xulie1[cnt++]=root[1];
        while(!qs.empty())
        {
            int now=qs.top();
            int i;
            for(i=0;i<E[now].size();i++)
            {
                if(vis[E[now][i].v])continue;
                qs.push(E[now][i].v);
                xulie1[cnt++]=E[now][i].v;
                break;
            }
            if(i==E[now].size())
            {
                vis[now]=true;
                qs.pop();
            }
        }

        memset(vis,false,sizeof(vis));
        qs.clear();
        cnt=1;
        qs.push(root[1]);
        while(!qs.empty())
        {
            int now=qs.top();
            int i;
            for(i=0;i<E[now].size();i++)
            {
                if(vis[E[now][i].v])continue;
                qs.push(E[now][i].v);
                break;
            }
            if(i==E[now].size())
            {
                vis[now]=true;
                xulie2[cnt++]=now;
                qs.pop();
            }
        }
    }

    else if(type==2)
    {
        QStack <int> qs;
        for(int i=1;i<=rootnum;i++)
        {
            qs.push(root[i]);
            xulie1[cnt++]=root[i];
            while(!qs.empty())
            {
                int now=qs.top();
                int j;
                for(j=0;j<E[now].size();j++)
                {
                    if(vis[E[now][j].v])continue;
                    qs.push(E[now][j].v);
                    xulie1[cnt++]=E[now][j].v;
                    break;
                }
                if(j==E[now].size())
                {
                    vis[now]=true;
                    qs.pop();
                }
            }
        }
    }

    else
    {
        QStack <int> qs;
        bool vis[100];
        memset(vis,false,sizeof(vis));
        for(int k=1;k<=pnum;k++)
        {
            if(!vis[k])
            {
                qs.push(k);
                xulie1[cnt++]=k;
                vis[k]=true;
            }
            while(!qs.empty())
            {
                int now=qs.top();
                int i;
                for(i=0;i<E[now].size();i++)
                {
                    if(vis[E[now][i].v])continue;
                    qs.push(E[now][i].v);
                    vis[E[now][i].v]=true;
                    xulie1[cnt++]=E[now][i].v;
                    break;
                }
                if(i==E[now].size())
                {
                    qs.pop();
                }
            }
        }

        QQueue <int> qq;
        memset(vis,false,sizeof(vis));
        qq.clear();
        cnt=1;
        for(int k=1;k<=pnum;k++)
        {
            if(!vis[k])
            {
                qq.push_back(k);
            }
            while(!qq.empty())
            {
                int now=qq.front();
                qq.pop_front();
                if(vis[now])continue;
                vis[now]=true;
                xulie2[cnt++]=now;
                int i;
                for(i=0;i<E[now].size();i++)
                {
                    qq.push_back(E[now][i].v);
                }
            }
        }
    }
}

int mstfind(int x,int F[])
{
    if(F[x]==-1)return x;
    else return F[x]=mstfind(F[x],F);
}

int Data::judgeMST()
{
    if(etype==2)
    {
        int F[100];
        memset(F,-1,sizeof(F));
        qSort(UndirE+1,UndirE+une_num+1);
        int cnt=0;
        int ans=0;
        for(int i=1;i<=une_num;i++)
        {
            int u=UndirE[i].u;
            int v=UndirE[i].v;
            int w=UndirE[i].w;
            int t1=mstfind(u,F);
            int t2=mstfind(v,F);
            if(t1!=t2)
            {
                ans+=w;
                F[t1]=t2;
                cnt++;
            }
            if(cnt==pnum-1)break;
        }
        if(cnt<pnum-1)return -1;
        else return ans;
    }
    else
        return -1;
}

Data graph_data;
