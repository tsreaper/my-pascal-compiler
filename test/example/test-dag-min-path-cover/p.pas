var can:array[0..100,0..100] of boolean;
    vis:array[0..300] of boolean;
    link,fa:Array[0..300] of longint;
    n,m,tot,ans:longint;

  procedure init;
  var i,a,b:longint;
  begin
    readln(n,m);
    fillchar(can,sizeof(can),false);
    for i:=1 to m do
    begin
      readln(a,b);
      can[a,b]:=true;
    end;
  end;

  function find(now:longint):boolean;
  var i:longint;
  begin
    for i:=1 to n do
      if (can[now,i])and(vis[i]=false) then
      begin
        vis[i]:=true;
        if (link[i]=0) or (find(link[i])) then
        begin
          link[i]:=now;
          fa[now]:=i;
          exit(true);
        end;
      end;
    exit(false);
  end;

  procedure main;
  var i:longint;
  begin
    ans:=0;
    fillchar(link,sizeof(link),0);
    fillchar(fa,sizeof(fa),0);
    for i:=1 to n do
    begin
      fillchar(vis,sizeof(vis),false);
      if find(i) then inc(ans);
    end;
    writeln(n-ans);
  end;

begin
  init();
  main();
end.
