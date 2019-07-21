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
  Unit System.pas (fpc_system_general.inc)
  --------------------------------------------------------------------------
  Unit principal do compilador, crosscompiler, que substitui a RTL normal.
  --------------------------------------------------------------------------
  Criado em: 21/07/2019
  --------------------------------------------------------------------------
  Compilar: Nao compilavel; Arquivo INC utilizado pela Unit System.
  ------------------------------------------------------------------------
  Executar: Nao executavel diretamente;
===========================================================================}

procedure Move(const Src; var Dest; Count : LongInt); alias : 'FPC_MOVE';
var
  PSrc, PDest, PEnd : PByte;
begin
  if (Count > 0) and (@Src <> @Dest) then
  begin
    if (@Dest < @Src) or ((@Src + Count) < @Dest) then
    begin
      // copia crescente
      PSrc := @Src;
      PDest := @Dest;
      PEnd := PSrc + Count;

      while (PSrc < PEnd) do
      begin
        PDest^ := PSrc^;
        Inc(PSrc);
        Inc(PDest);
      end;

    end
    else
    begin
      // copia decrescente
      PSrc := @Src + Count - 1;
      PDest := @Dest + Count - 1;
      PEnd := @Src;

      while (PSrc >= PEnd) do
      begin
        PDest^ := PSrc^;
        Dec(PSrc);
        Dec(PDest);
      end;
    end;
  end;
end;

function CompareByte(const Buff1, Buff2; Len : LongInt) : LongInt;
var
  PBuff1D, PBuff2D : PDWord;
  PBuff1B, PBuff2B : PByte;
  vBlocks : LongInt;
  vRest : Byte;

begin
  PBuff1D := @Buff1;
  PBuff2D := @Buff2;

  vBlocks := Len div 4;
  vRest := Len mod 4;
  Result := 0;

  while (vBlocks > 0) and (Result = 0) do
  begin
    Result := PBuff1D^ - PBuff2D^;
    Inc(PBuff1D);
    Inc(PBuff2D);
    Dec(vBlocks);
  end;

  PBuff1B := Pointer(PBuff1D);
  PBuff2B := Pointer(PBuff2D);

  while (vRest > 0) and (Result = 0) do
  begin
    Result := PBuff1B^ - PBuff2B^;
    Inc(PBuff1B);
    Inc(PBuff2B);
    Dec(vRest);
  end;

  // 0 = True;
end;

procedure FillChar(var X; Count : LongInt; Value : Char);
begin
  FillByte(X, Count, Byte(Value));
end;

procedure FillByte(var X; Count : LongInt; Value : Byte);
var
  PDestD : PDWord;
  PDestB : PByte;
  vBlocks : LongInt;
  vRest : Byte;
  vTemp : DWord;

begin
  if (Count > 0) then
  begin
    // otimiza para gravar 32 bits (4 Bytes por bloco)
    PDestD := @X;
    vBlocks := Count div 4;
    vRest := Count mod 4;

    if (vBlocks > 0) then
    begin
      vTemp := (Value shl 8) or Value;
      vTemp := (vTemp shl 16) or vTemp;

      repeat
        PDestD^ := vTemp;
        Inc(PDestD);
        Dec(vBlocks);
      until vBlocks = 0;
    end;

    PDestB := Pointer(PDestD);

    // grava o resto
    while (vRest > 0)  do
    begin
      PDestB^ := Value;
      Inc(PDestB);
      Dec(vRest);
    end;
  end;
end;

procedure FillWord(var X; Count : LongInt; Value : Word);
var
  PDestD : PDWord;
  PDestW : PWord;
  vBlocks : LongInt;
  vRest : Byte;
  vTemp : DWord;

begin
  if (Count > 0) then
  begin
    // otimiza para gravar 32 bits (2 words por bloco)
    PDestD := @X;
    vBlocks := Count div 2;
    vRest := Count mod 2;

    if (vBlocks > 0) then
    begin
      vTemp := (Value shl 16) or Value;

      repeat
        PDestD^ := vTemp;
        Inc(PDestD);
        Dec(vBlocks);
      until vBlocks = 0;
    end;

    PDestW := Pointer(PDestD);

    // grava o resto
    while (vRest > 0) do
    begin
      PDestW^ := Value;
      Inc(PDestW);
      Dec(vRest);
    end;
  end;
end;

procedure FillDWord(var X; Count : LongInt; Value : DWord);
var
  PDestD : PDWord;

begin
  if (Count > 0) then
  begin
    PDestD := @X;

    while (Count > 0) do
    begin
      PDestD^ := Value;
      Inc(PDestD);
      Dec(Count);
    end;
  end;
end;

procedure Halt(ErrorNo : LongInt);
begin
  ExitCode := ErrorNo;
  Do_Exit;
end;

procedure Halt; inline;
begin
  Halt(0);
end;

procedure Do_Exit;  alias: 'FPC_DO_EXIT';
begin
  InternalExit;
  System_exit;
end;

procedure InternalExit;
begin
{
  *
  *   Nesta procedure está tudo que deve ser terminado antes de terminar o
  * programa, como flush de arquivos, liberação de memoria e procedimentos de
  * finalização do usuario.
  *
  *   Até o momento nada a se colocado aqui. Mantido por compatibilidade.
  *
}
end;

procedure System_Exit;
begin
  HaltProc(ExitCode);
end;

procedure HaltProc(Error : LongInt);
begin
  SysExit(Error);
end;

function  Pos(const SubStr, SrcStr : ShortString) : Byte;
var
  vLenSub  : Byte;
  vEnd, vSrc : PChar;

begin
  Pos := 0;
  vLenSub := Length(SubStr);

  if (vLenSub > 0) and (vLenSub <= Length(SrcStr)) then
  begin
    vEnd := @SrcStr[Length(SrcStr) - vLenSub + 1];
    vSrc := @SrcStr[1];

    while (vSrc <= vEnd) do
    begin
      if (SubStr[1] = vSrc^) and (CompareByte(SubStr[1], vSrc^, vLenSub) = 0) then
      begin
        Pos := vSrc - @SrcStr[0];
        Exit;
      end;

      Inc(vSrc);
    end;
  end;
end;

function  Pos(C : Char; const Source : ShortString) : Byte;
var
  vEnd, vSrc : PChar;

begin
  Pos := 0;

  vEnd := @Source[Length(Source)];
  vSrc := @Source[1];

  while (vSrc <= vEnd) do
  begin
    if (C = vSrc^) then
    begin
      Pos := vSrc - @Source[0];
      Exit;
    end;

    Inc(vSrc);
  end;
end;
