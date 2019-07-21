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
  Unit System.pas (fpc_system_integer.inc)
  --------------------------------------------------------------------------
  Unit principal do compilador, crosscompiler, que substitui a RTL normal.
  --------------------------------------------------------------------------
  Criado em: 21/07/2019
  --------------------------------------------------------------------------
  Compilar: Nao compilavel; Arquivo INC utilizado pela Unit System.
  ------------------------------------------------------------------------
  Executar: Nao executavel diretamente;
===========================================================================}

function fpc_mul_qword(V1, V2 : QWord; CheckOverflow : Longbool) : QWord; compilerproc;
  alias: 'FPC_MUL_QWORD';
var
  ResultOld, BitPos : QWord;
  V1Over : Boolean;
  B : Byte;

begin
  Result := 0;
  BitPos := 1;
  V1Over := False;

  for B := 0 to 63 do
  begin
    // Testa cada posicao de V2
    if ((V2 and BitPos) <> 0) then
    begin
      ResultOld := Result;
      Result := Result + V1;

      if CheckOverflow and
        (V1Over or
          ((V1 <> 0) and (ResultOld <> 0) and
            ((Result < V1) or (Result < ResultOld))
          )
        )
      then
        HandleErrorFrame(215, get_frame);
    end;

    // Testa bit 63 = 1
    V1Over := V1Over or ((V1 and (1 shl 63)) <> 0);

    V1 := V1 shl 1;
    BitPos := BitPos shl 1;
  end;
end;


function fpc_mul_int64(V1, V2 : Int64; CheckOverflow : Longbool) : Int64; compilerproc;
  alias: 'FPC_MUL_INT64';
var
  Negative : Boolean;
  Q1, Q2, Q3 : QWord;

begin
  if (V1 < 0) then
  begin
    Negative := True;
    Q1 := QWord(-V1);
  end
  else
  begin
    Negative := False;
    Q1 := QWord(V1);
  end;

  if (V2 < 0) then
  begin
    Negative := not Negative;
    Q2 := QWord(-V2);
  end
  else
    Q2 := QWord(V2);

  // Q1 * Q2 como mulqword
  Q3 := Q1 * Q2;

  if CheckOverflow and (Q1 <> 0) and (Q2 <> 0) and
    ((Q1 > Q3) or
     (Q2 > Q3) or
     ((Q3 shr 63) <> 0) and ((Q3 <> (1 shl 63)) or not Negative)
    )
  then
    HandleErrorFrame(215, get_frame);

  if Negative then
    fpc_mul_int64 := -Q3
  else
    fpc_mul_int64 := Q3;
end;
