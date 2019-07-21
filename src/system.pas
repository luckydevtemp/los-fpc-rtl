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
  Unit System.pas
  --------------------------------------------------------------------------
  Unit principal do compilador, crosscompiler, que substitui a RTL normal.
  --------------------------------------------------------------------------
  Criado em: 29/04/2013
  --------------------------------------------------------------------------
  Compilar: Compilavel FPC
  > fpc system.pas
  ------------------------------------------------------------------------
  Executar: Nao executavel diretamente; Unit.
===========================================================================}

unit System;

{$mode objfpc} // Obrigatorio por usar out-parameters

interface

type
  HResult = LongWord; // Obrigatorio

  // Tamanhos automatizados (maximos da arquitetura)
  SInt = LongInt; // Inteiro com sinal
  UInt = LongWord; // Inteiro sem sinal

  TUIntPtr = UInt; // Equivalente inteiro de ponteiro

  DWord = LongWord;

  PByte = ^Byte;
  PWord = ^Word;
  PDWord = ^DWord;

  PChar = ^Char;
  PShortString = ^ShortString;


const
  MaxByte = $FF;
  MaxShortInt = $7F;

  MaxWord = $FFFF;
  MaxSmallInt = $7FFF;

  MaxLongWord = $FFFFFFFF;
  MaxLongInt = $7FFFFFFF;

  MaxInt = MaxLongInt;
  MaxUInt = MaxLongWord;
  MaxSInt = MaxLongInt;


  {$I FPC_SYSTEM_EXTERNAL.INC}

  {$I FPC_SYSTEM_GENERALH.INC}
  {$I FPC_SYSTEM_INTEGERH.INC}
  {$I FPC_SYSTEM_SHORTSTRH.INC}
  {$I FPC_SYSTEM_PCHARH.INC}


implementation

  {$I FPC_SYSTEM_GENERALF.INC}
  {$I FPC_SYSTEM_ERRORMANAGERF.INC}
  {$I FPC_SYSTEM_SHORTSTRF.INC}

  {$I FPC_SYSTEM_GENERAL.INC}
  {$I FPC_SYSTEM_INTEGER.INC}
  {$I FPC_SYSTEM_SHORTSTR.INC}
  {$I FPC_SYSTEM_PCHAR.INC}
  {$I FPC_SYSTEM_ERRORMANAGER.INC}


end.



