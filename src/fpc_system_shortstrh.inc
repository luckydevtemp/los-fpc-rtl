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
  Unit System.pas (fpc_system_shortstrh.inc)
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

  function fpc_shortstr_compare_equal(const StrLeft, StrRight : ShortString) : LongInt;
    register; compilerproc;

  procedure fpc_shortstr_concat(var DestStr : ShortString; const Src1, Src2 : ShortString);
    register; compilerproc;

  procedure fpc_shortstr_concat_multi(var DestStr : ShortString; const SrcArr : array of PShortString);
    register; compilerproc;

  procedure fpc_shortstr_to_shortstr(out Res: ShortString; const SSrc: ShortString);
    register; compilerproc;

  procedure fpc_chararray_to_shortstr(out Res : ShortString;
    const Arr: array of char; ZeroBased : Boolean = true);
    register; compilerproc;

  procedure fpc_pchar_to_shortstr(out Res : ShortString; P : PChar);
    register; compilerproc;

  function fpc_val_sint_shortstr(DestSize : LongInt; const S : ShortString;
    out Error : LongInt) : LongInt; register; compilerproc;
