@ECHO  OFF
REM  Gera, Compila e testa os m�dulos lista, peca e tabuleiro

if exist TestaTudo.bat goto faz
rem >>> esta' no diretorio ilegal
goto sai

:faz

Cls

Call  Limpa
Call  Geratudo
Call  Compilatudo
Call  TestaTudo

:sai