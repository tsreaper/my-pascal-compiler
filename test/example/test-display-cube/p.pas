program test_display_cube;

var
m,n,i,j,k,totx,toty:longint;
s:array[1..100,1..100]of char;
a:array[1..100,1..100]of longint;

procedure work(i,j,k:longint);
var
x,y:longint;

  begin
    x:=i*2-1+(k-1)*3;
    y:=i*2-1+(j-1)*4;
    if x+5>totx then totx:=x+5;
    if y+6>toty then toty:=y+6;
    s[x,y]:='+'; s[x,y+1]:='-'; s[x,y+2]:='-'; s[x,y+3]:='-'; s[x,y+4]:='+';
    s[x+1,y]:='|'; s[x+1,y+1]:=' '; s[x+1,y+2]:=' ';s[x+1,y+3]:=' '; s[x+1,y+4]:='|'; s[x+1,y+5]:='/';
    s[x+2,y]:='|'; s[x+2,y+1]:=' '; s[x+2,y+2]:=' '; s[x+2,y+3]:=' ';s[x+2,y+4]:='|'; s[x+2,y+5]:=' '; s[x+2,y+6]:='+';
    s[x+3,y]:='+'; s[x+3,y+1]:='-'; s[x+3,y+2]:='-'; s[x+3,y+3]:='-'; s[x+3,y+4]:='+'; s[x+3,y+5]:=' ';s[x+3,y+6]:='|';
    s[x+4,y+1]:='/';s[x+4,y+2]:=' '; s[x+4,y+3]:=' ';s[x+4,y+4]:=' '; s[x+4,y+5]:='/'; s[x+4,y+6]:='|';
    s[x+5,y+2]:='+'; s[x+5,y+3]:='-'; s[x+5,y+4]:='-';  s[x+5,y+5]:='-'; s[x+5,y+6]:='+';
  end;
  begin
    readln(m,n);
    for i:=m downto 1 do
      for j:=1 to n do
        begin
          read(a[i,j]);
        end;
    fillchar(s,sizeof(s),'.');
    totx:=0;toty:=0;
    for i:=m downto 1 do
      for j:=1 to n do
        for k:=1 to a[i,j] do work(i,j,k);
    for i:=totx downto 1 do
      begin
        for j:=1 to toty do write(s[i,j]);
        writeln();
      end;
  end.
