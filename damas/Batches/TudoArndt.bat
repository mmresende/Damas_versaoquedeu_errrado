@ECHO  OFF
REM  Gera, Compila e testa os m�dulos listaInt, peca e tabuleiro

if exist TestaTudoInt.bat goto faz
rem >>> esta' no diretorio ilegal
goto sai

:faz

Cls

Call  Limpatudo
Call  Geratudo
Call  Compilatudo
Call  TestaTudoArndt

:sai