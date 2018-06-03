program test_bipartite_graph_matching;
var
  point:array[0..2000]of integer;
  cover:array[0..2000]of boolean;
  e:array[0..2000,0..2000]of boolean;
  i,j,k,n,m,ans,a,b:integer;

function dfs(u:integer):boolean;
var v:integer;
begin
  for v:=1 to n+m do
    if (e[u,v])and(cover[v]=false)and(point[u]<>v) then
      begin
        cover[v]:=true;
        if (point[v]=-1)or(dfs(v)) then
          begin
            point[v]:=u;
            dfs:=true;
            exit;
          end;
      end;
  dfs:=false;
end;

begin
  read(n,m,k);
  for i:=1 to k do
    begin
      read(a,b);
      e[a,b+n]:=true;
      e[b+n,a]:=true;
    end;
  for i:=1 to n+m do point[i]:=-1;
  for i:=1 to n do
    begin
      for j:=1 to n+m do cover[j]:=false;
      cover[i]:=true;
      if dfs(i) then ans:=ans+1;
    end;
  writeln(ans);
end.
