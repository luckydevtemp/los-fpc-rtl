{===========================================================================
  Este arquivo pertence ao Projeto do Sistema Operacional LuckyOS (LOS).
  --------------------------------------------------------------------------
  Copyright (C) 2013 - Luciano L. Goncalez
  --------------------------------------------------------------------------
  eMail : dev.lucianogoncalez@gmail.com
  Home  : http://lucky-labs.blogspot.com.br
============================================================================
  Este programa e software livre; voce pode redistribui-lo e/ou modifica-lo
  sob os termos da Licenca Publica Geral GNU, conforme publicada pela Free
  Software Foundation; na versao 2 da Licenca.

  Este programa e distribuido na expectativa de ser util, mas SEM QUALQUER
  GARANTIA; sem mesmo a garantia implicita de COMERCIALIZACAO ou de
  ADEQUACAO A QUALQUER PROPOSITO EM PARTICULAR. Consulte a Licenca Publica
  Geral GNU para obter mais detalhes.

  Voce deve ter recebido uma copia da Licenca Publica Geral GNU junto com
  este programa; se nao, escreva para a Free Software Foundation, Inc., 59
  Temple Place, Suite 330, Boston, MA 02111-1307, USA. Ou acesse o site do
  GNU e obtenha sua licenca: http://www.gnu.org/
============================================================================
  Unit System.pas (fpc_system_shortstr.inc)
  --------------------------------------------------------------------------
  Unit principal do compilador, crosscompiler, que substitui a RTL normal.
  --------------------------------------------------------------------------
  Criado em: 21/07/2019
  --------------------------------------------------------------------------
  Compilar: Nao compilavel; Arquivo INC utilizado pela Unit System.
  ------------------------------------------------------------------------
  Executar: Nao executavel diretamente;
===========================================================================}

procedure fpc_shortstr_assign(Len : LongInt; SSrc, SDest : Pointer);
  register; compilerproc;
  alias : 'FPC_SHORTSTR_ASSIGN';

var
  LenSrc : Byte;

begin
  LenSrc := Length(PShortString(SSrc)^);

  if (LenSrc < Len) then
    Len := LenSrc;

  Move(SSrc^, SDest^, Len + 1);

  if (LenSrc > Len) then
    PChar(SDest)^ := Char(Len);
end;

function fpc_shortstr_compare_equal(const StrLeft, StrRight : ShortString) : LongInt;
  register; compilerproc;
  alias:'FPC_SHORTSTR_COMPARE_EQUAL';

begin
  Result := LongInt(StrLeft[0]) - LongInt(StrRight[0]);

  if (Result = 0) then
    Result := CompareByte(StrLeft[1], StrRight[1], LongInt(StrLeft[0]));

  // 0 := True;
end;

procedure fpc_shortstr_concat(var DestStr : ShortString; const Src1, Src2 : ShortString);
  register; compilerproc;
  alias : 'FPC_SHORTSTR_CONCAT';

var
  LenSrc1, LenSrc2, LenDest : LongInt;

begin
  LenSrc1 := Length(Src1);
  LenSrc2 := Length(Src2);
  LenDest := High(DestStr);

  if ((LenSrc1 + LenSrc2) > LenDest) then
    LenSrc2 := LenDest - LenSrc1;

  if (@DestStr = @Src1) then
    // Somente adiciona
    Move(Src2[1], DestStr[LenSrc1 + 1], LenSrc2)
  else
    if (@DestStr = @Src2) then
    begin
      // Copia para cima e adiciona
      Move(DestStr[1], DestStr[LenSrc1 + 1], LenSrc2);
      Move(Src1[1], DestStr[1], LenSrc1);
    end
    else
    begin
      Move(Src1[1], DestStr[1], LenSrc1);
      Move(Src2[1], DestStr[LenSrc1 + 1], LenSrc2);
    end;

  DestStr[0] := Char(LenSrc1 + LenSrc2);
end;

procedure fpc_shortstr_concat_multi(var DestStr : ShortString; const SrcArr : array of PShortString);
  register; compilerproc;
  alias : 'FPC_SHORTSTR_CONCAT_MULTI';

var
  TempStr : ShortString;
  I : LongInt;

begin
  if (High(SrcArr) = 0) then
    DestStr := ''
  else
  begin
    TempStr := '';

    for I := Low(SrcArr) to High(SrcArr) do
    begin
      if (Length(TempStr) >= High(DestStr)) then
        Break;

      TempStr := TempStr + SrcArr[I]^;
    end;

    DestStr := TempStr;
  end;
end;

procedure fpc_shortstr_to_shortstr(out Res: ShortString; const SSrc: ShortString);
  register; compilerproc;
  alias : 'FPC_SHORTSTR_TO_SHORTSTR';

var
  LenSrc : SmallInt;

begin
  LenSrc := Length(SSrc);

  { Da "Warning: unreachable code" porque High(Res) sempre da 255, o limite do byte,
  * e o compilador otimiza if LenSrc > 255 then -> if false then, eliminando o codigo}

  if LenSrc > High(Res) then
    LenSrc := High(Res);

  Move(SSrc[0], Res[0], LenSrc + 1);
  Res[0] := Char(LenSrc);
end;

procedure fpc_chararray_to_shortstr(out Res : ShortString;
  const Arr: array of char; ZeroBased : Boolean = true);
  register; compilerproc;
  alias:'FPC_CHARARRAY_TO_SHORTSTR';

var
  Len : LongInt;
  I : LongInt;

begin
  Len := High(Arr) + 1;

  if (Len > High(Res)) then
    Len := High(Res)
  else
    if (Len < 0) then
      Len := 0;

  if ZeroBased then
    for I := 0 to (Len - 1) do
      if (Arr[I] = #0) then
      begin
        Len := I;
        Break;
      end;

  Move(Arr[0], Res[1], Len);
  Res[0] := Char(Len);
end;

procedure fpc_pchar_to_shortstr(out Res : ShortString; P : PChar); register; compilerproc;
  alias : 'FPC_PCHAR_TO_SHORTSTR';

var
  vLen : LongInt;
  vTemp : ShortString;

begin
  vLen := StrLen(P);

  if (vLen > High(Res)) then
    vLen := High(Res);

  if (vLen > 0) then
    Move(P^, vTemp[1], vLen);

  vTemp[0] := Char(vLen);
  Res := vTemp;
end;

function fpc_val_sint_shortstr(DestSize : LongInt; const S : ShortString;
  out Error : LongInt) : LongInt; register; compilerproc;
  alias : 'FPC_VAL_SINT_SHORTSTR';
  // Essa definicao ehhh pura gambiarra, ahhh pessoal do fpc :/

var
  vPos, vLen : SmallInt;
  vNeg : Boolean;
  vBase, vDig : Byte;
  vTemp, vPrev, vNew : LongWord;

begin
  fpc_val_sint_shortstr := 0;
  Error := 1;

  vLen := Length(S);
  vPos := InitVal(S, vNeg, vBase);

  if (vPos > vLen) then
    Exit;

  if (S[vPos] = #0) then
  begin
    if (vPos > 1) and (S[vPos - 1] = '0') then
      Error := 0;

    Exit;
  end;

  vTemp := 0;

  while (vPos <= vLen) do
  begin
    case S[vPos] of
      '0'..'9' : vDig := Ord(S[vPos]) - Ord('0');
      'A'..'F' : vDig := Ord(S[vPos]) - Ord('A') + 10;
      'a'..'f' : vDig := Ord(S[vPos]) - Ord('a') + 10;
      #0 : Break;
    else
      vDig := 16;
    end;

    vPrev := vTemp;
    vTemp := vTemp * vBase;
    vNew := vTemp + vDig;

    if (vDig >= vBase) or (vTemp < vPrev) or (vNew < vPrev) then
      Exit;

    vTemp := vNew;
    Inc(vPos);
  end;

  if vNeg then
    fpc_val_sint_shortstr := LongInt(0 - vTemp)
  else
    fpc_val_sint_shortstr := LongInt(vTemp);

  if (vNeg and (fpc_val_sint_shortstr > 0)) or
     (not vNeg and (fpc_val_sint_shortstr < 0)) then
  begin
    fpc_val_sint_shortstr := 0;
    Exit;
  end;

  case DestSize of
    1 : fpc_val_sint_shortstr := ShortInt(fpc_val_sint_shortstr);
    2 : fpc_val_sint_shortstr := SmallInt(fpc_val_sint_shortstr);
  end;

  Error := 0;
end;


function InitVal(const S : ShortString; out Negative : Boolean; out Base : Byte) : LongInt;
var
  vPos, vLen : SmallInt;

begin
  vPos := 1;
  vLen := Length(S);
  Negative := False;
  Base := 10;

  if (vLen = 0) then
  begin
    InitVal := 1;
    Exit
  end;

  while (vPos <= vLen) and (S[vPos] in [' ', #9]) do
    Inc(vPos);

  case s[vPos] of
    '-' :
      begin
        Negative := True;
        Inc(vPos);
      end;

    '+' : Inc(vPos);
  end;

  if (vPos <= vLen) then
    case S[vPos] of
      '$', 'X', 'x' :
        begin
          Base := 16;
          Inc(vPos);
        end;

      '%' :
        begin
          Base := 2;
          Inc(vPos);
        end;

      '&' :
        begin
          Base := 8;
          Inc(vPos);
        end;

      '0' :
        if (vPos < vLen) and (S[vPos + 1] in ['x', 'X']) then
        begin
          Base := 16;
          Inc(vPos, 2);
        end;
    end;

  while (vPos < vLen) and (S[vPos] = '0') do
    Inc(vPos);

  InitVal := vPos;
end;
