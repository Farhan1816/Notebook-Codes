void dfs1(int ind, int parent,int &tim)
{
    visited[ind]=true;
    time_in[ind]=tim;
    low[ind]=tim;
    tim++;  
    for(auto i: adj[ind])
    {
        if(i==parent)continue;
        if(!visited[i])
        {
            dfs1(i, ind, tim);
            low[ind]=min(low[ind], low[i]);
            if(low[i]>time_in[ind])bridges.insert({ind, i});
        }
        else
        {
            low[ind]=min(low[ind], time_in[i]);
        }
    }
}
