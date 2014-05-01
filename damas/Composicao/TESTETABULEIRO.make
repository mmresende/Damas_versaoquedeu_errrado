##################################################
###
### Diretivas de MAKE para o construto: TESTETABULEIRO
### Gerado a partir de: TESTETABULEIRO.comp
###
### ----- Arquivo gerado, N�O EDITE!!! -----
###
##################################################

### Nomes globais

NOME            = TESTETABULEIRO


### Nomes de paths

Ph                   = ..\Fontes
Pobj                 = ..\Objetos
Perr                 = ..\Produto
PDEFAULT             = ..\Fontes
Pc                   = ..\Fontes

### Nomes de diret�rios para gera��o

Fh                   = ..\Fontes
Fobj                 = ..\Objetos
Ferr                 = ..\Produto
FDEFAULT             = ..\Fontes
Fc                   = ..\Fontes

### Macros da plataforma


O       =
OD      = /Zi /Od
L       =
LD      = /DEBUG /DEBUGTYPE:CV

!IFDEF PRD
O       = /Ox
!ENDIF

OPT     = /c /J /W4 /nologo
INCLUDE = $(INCLUDE);$(PDEFAULT)


### Regras de gera��o

all : limpa \
   $(Fobj)\testtabuleiro.obj   $(Fobj)\tabuleiro.obj   $(Fobj)\lista.obj \
   $(Fobj)\peca.obj \
   Construto

### Limpar arquivos

limpa :
   CompileBanner /c$(NOME)
   CompileBanner /c$(NOME) >$(Ferr)\$(NOME).err


### Depend�ncias de m�dulos objeto a compilar

$(Fobj)\testtabuleiro.obj :  {$(Pc)}\testtabuleiro.c \
    {$(Ph)}peca.h               {$(Ph)}tabuleiro.h         
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\tabuleiro.obj :  {$(Pc)}\tabuleiro.c \
    {$(Ph)}lista.h              {$(Ph)}peca.h               {$(Ph)}tabuleiro.h         
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\lista.obj :  {$(Pc)}\lista.c \
    {$(Ph)}lista.h             
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err

$(Fobj)\peca.obj :  {$(Pc)}\peca.c \
    {$(Ph)}peca.h              
   cl $(O) $(OPT) /Fo$(Fobj)\ $(Fc)\$(@B).c >> $(Ferr)\$(NOME).err


### Termina��o

Construto : \
   $(Fobj)\testtabuleiro.obj   $(Fobj)\tabuleiro.obj   $(Fobj)\lista.obj \
   $(Fobj)\peca.obj
    cd $(Fobj)
    LINK $(L) @$(NOME).build >> $(Ferr)\$(NOME).err

##################################################
###
### Fim de diretivas MAKE para o construto: TESTETABULEIRO
###
##################################################

