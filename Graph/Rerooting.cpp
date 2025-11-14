void dfs(int ind, int p)
{
  int tmp = 0;
  int s=1;
  for(auto i: adj[ind])
  {
    if(i!=p)
    {
      dfs(i, ind);
      s+=sz[i];
      down[ind] += down[i];
    }
  }
  sz[ind] = s;
  down[ind] += sz[ind];
}
void dfs2(int ind, int p)
{
  if(ind!=p)
  {
    up[ind] += up[p];
    up[ind] += (n-sz[ind]);
  }
  //cout << ind <<  " " << up[ind] << "\n";
  int tmp=0;
  for(auto i: adj[ind])
  {
    if(i!=p)
    {
      up[i] += tmp;
      tmp+=down[i];
    }
  }
  reverse(adj[ind].begin(), adj[ind].end());
  tmp = 0;
  for(auto i: adj[ind])
  {
    if(i!=p)
    {
      up[i]+=tmp;
      tmp+=down[i];
    }
  }
  for(auto i: adj[ind])if(i!=p)dfs2(i, ind);
}
