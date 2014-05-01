@ECHO OFF
REM executa os testes de listaArndt, peca e tabuleiro

cls

del ..\scripts\estatisticasArndt.estat

..\produto\TESTELISTA		/s..\scripts\TesteListaArndt	/l..\produto\TesteListaArndt	/a..\scripts\estatisticasArndt
..\produto\TESTEPECA  		/s..\scripts\Testepeca    	/l..\produto\TestePeca  	/a..\scripts\estatisticasArndt
..\produto\TESTETABULEIRO  	/s..\scripts\Testetabuleiro	/l..\produto\TesteTabuleiro   	/a..\scripts\estatisticasArndt

..\ferramnt\exbestat /e..\scripts\estatisticasArndt
