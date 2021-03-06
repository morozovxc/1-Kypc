uses crt;
var
    a, x, n5,ss5: integer;
    d: char;

procedure perevod;
    label to2, to8;
    var
      mas: array [1..100] of byte;
      b, c, i: integer;
      h: char;
    begin
      ClrScr;
      writeln('Выбор действия:');
      writeln('(1) 10 в 2');
      writeln('(2) 10 в 8');
      write('Действие: ');
      readln(h);
      case h of
        '1': goto to2;
        '2': goto to8;
      else
        ClrScr;
        writeln('[Ошибка] Данного действия нет');
        exit
      end;
    to2:
      begin
        ClrScr;
        write('Число в десятичной: ');
        readln(b);
        write('Число в двоичной: ');
        c := 0;
        repeat
          c := c + 1;
          mas[c] := b mod 2;
          b := b div 2;
        until b = 0;
        for i := c downto 1 do write(mas[i],' ');
        writeln;
        exit
      end;
    to8:
      begin
        ClrScr;
        write('Число в десятичной: ');
        readln(b);
        write('Число в восьмеричной: ');
        c := 0;
        repeat
          c := c + 1;
          mas[c] := b mod 8;
          b := b div 8;
        until b = 0;
        for i := c downto 1 do write(mas[i]);
        writeln;
        exit
      end;
    end;

procedure fibonachi;
    var r, v, i, k, s: integer;
    begin
      ClrScr;
      write('Введите количество цифр: ');
      readln(k);
      write('Вывод: ');
      r := 0;
      write(r, ' ');
      v := 1;
      write(v, ' ');
      for i := 3 to k do begin
        write(r + v, ' ');
        s := v;
        v := r + v;
        r := s;
      end;
      writeln;
      exit
    end;

function perevodik(n,ss:integer): string;
    const sim:string[16]='0123456789ABCDEF';
    var rec:string;
    begin
      ClrScr;
      write('Введите число для перевода: ');
      readln(n);
      write('Введите систему счисления: ');
      readln(ss);
      repeat
        rec:=sim[(n mod ss+1)]+rec;
        n:=n div ss;
      until n=0;
      perevodik:=rec;
      write(rec);
      writeln;
    end;

begin
  d := 'y';
  while d <> 'n' do begin
    ClrScr;
    writeln('Выбор действия:');
    writeln('(1) Перевод [2,8]');
    writeln('(2) Числа Фибоначи');
    writeln('(3) Переводы [1-16]');
    write('Действие: ');
    Readln(x);
    case x of
      1: perevod;
      2: fibonachi;
      3: perevodik(n5,ss5);
      0: exit;
      else writeln('[Ошибка] Данного действия нет');
    end;
    write('Желаете продолжить? [Space + Enter / n]: ');
    readln(d);
  end;
end.
