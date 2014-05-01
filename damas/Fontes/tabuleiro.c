
/***************************************************************************
*  $MCI M�dulo de implementa��o: TAB  Tabuleiro 
*
*  Arquivo gerado:              TABULEIRO.c
*  Letras identificadoras:      TAB
*
*  Projeto: damas
*  Arquivo: damas\Fontes\tabuleiro.c    
*
*  Autores: hs - Henrique Santiago
*	    mr - Marcelo Resende
*	    rh - Rafael Haeusler
*  
*  $HA Hist�rico de evolu��o: 
*     Vers�o  Autor    Data     Observa��es
*     1       hs/mr/rh   30/abril/2014    implementa��o parcial do jogo
*  
*  $CRE Cr�ditos
*    Arndt von Staa. Programa AutoTest - Arcabou�o para a automa��o de testes de 
*    programas redigidos em C;
*  
***************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define tabuleiro_OWN   
#include "tabuleiro.h"
#undef tabuleiro_OWN 

#include "lista.h"
#include "peca.h"

/* Define as dimens�es do tabuleiro */
enum {
    TabuleiroAltura = 8,
    TabuleiroLargura = 8,
};

/***********************************************************************
*
*  $TC Tipo de dados: TAB estrutura que referencia uma lista
*  duplamente encadeada que representa as linhas do tabuleiro 
*
*
***********************************************************************/
typedef struct _Tabuleiro {
    LIS_tppLista lista;

} Tabuleiro;


/***** Prot�tipos das fun��es encapsuladas no m�dulo *****/
static void ListaExcluirPeca(void *pDado);

static void ListaExcluirLista(void *pDado); 


/*****  C�digo das fun��es exportadas pelo m�dulo  *****/
/***************************************************************************
*
*  Fun��o: TAB  &Criar tabuleiro
*  ****/

Tabuleiro *TAB_criar()
{
    int x, y;
    Tabuleiro *tabuleiro = (Tabuleiro*)malloc(sizeof(Tabuleiro));
    if(!tabuleiro)
        return NULL;
    tabuleiro->lista = LIS_CriarLista(ListaExcluirLista);
    if(!tabuleiro->lista) {
        free(tabuleiro);
        return NULL;
    }
    for(y = 0; y < TabuleiroAltura; ++y) {
        LIS_tppLista lista = LIS_CriarLista(ListaExcluirPeca);
        if(!lista) {
            TAB_destruir(tabuleiro);
            return NULL;
        }
        if(LIS_InserirElementoAntes(tabuleiro->lista, lista) != LIS_CondRetOK) {
            TAB_destruir(tabuleiro);
            return NULL;
        }
        for(x = 0; x < TabuleiroLargura; ++x){
            if(LIS_InserirElementoAntes(lista, NULL) != LIS_CondRetOK) {
                TAB_destruir(tabuleiro);
                return NULL;
            }
        }
    }

    return tabuleiro;
}/* Fim fun��o: TAB  &Criar tabuleiro */

/***************************************************************************
*
*  Fun��o: TAB  &Destruir tabuleiro
*  ****/

void TAB_destruir(Tabuleiro *tabuleiro)
{
#ifdef _DEBUG
    assert(tabuleiro);
#endif
    LIS_DestruirLista(tabuleiro->lista);
    free(tabuleiro);
}/* Fim fun��o: TAB  &Destruir tabuleiro */


/***************************************************************************
*
*  Fun��o: TAB  &Inicializar tabuleiro para in�cio de uma partida
*  ****/

void TAB_inicializar(Tabuleiro *tabuleiro)
{
    int x, y;
#ifdef _DEBUG
    assert(tabuleiro);
#endif
    LIS_IrInicioLista(tabuleiro->lista);
    for(y = 0; y < TabuleiroAltura; ++y) {
        LIS_tppLista lista = (LIS_tppLista)LIS_ObterValor(tabuleiro->lista);
        LIS_IrInicioLista(lista);
        for(x = 0; x < TabuleiroLargura; ++x) {
            Peca *peca = NULL;
            if(y < 2 && (x + y) % 2 == 1)
                peca = PEC_criar(PecaNormal, 'x');
            else if(y > TabuleiroAltura - 3 && (x + y) % 2 == 1)
                peca = PEC_criar(PecaNormal, 'o');

            LIS_SetarValor(lista, peca);
            LIS_AvancarElementoCorrente(lista, 1);
        }
        LIS_AvancarElementoCorrente(tabuleiro->lista, 1);
    }
}/* Fim fun��o: TAB  &Inicializar tabuleiro para in�cio de uma partida */

/***************************************************************************
*
*  Fun��o: TAB  &Imprimir estado atual de um tabuleiro
*  ****/
void TAB_imprimir(Tabuleiro *tabuleiro)
{
    int x, y;
#ifdef _DEBUG
    assert(tabuleiro);
#endif

    LIS_IrFinalLista(tabuleiro->lista);
    for(y = TabuleiroAltura - 1; y >= 0; --y) {
        LIS_tppLista lista;
        printf("%d|", y+1);

        lista = (LIS_tppLista)LIS_ObterValor(tabuleiro->lista);
        LIS_IrInicioLista(lista);
        for(x = 0; x < TabuleiroLargura; ++x) {
            Peca *peca = LIS_ObterValor(lista);
            if(peca)
                PEC_imprimir(peca);
            else
                printf(" |");

            LIS_AvancarElementoCorrente(lista, 1);
        }
        printf("\n");
        LIS_AvancarElementoCorrente(tabuleiro->lista, -1);
    }
    printf(" |A|B|C|D|E|F|G|H|\n");
}/* Fim fun��o: TAB  &Imprimir estado atual de um tabuleiro */


/***************************************************************************
*
*  Fun��o: TAB  &Obter valor de uma pe�a no tabuleiro
*  ****/

Peca *TAB_obterCasa(Tabuleiro *tabuleiro, int linha, char coluna)
{
    LIS_tppLista lista;
#ifdef _DEBUG
    assert(tabuleiro);
#endif

    --linha;
    coluna = tolower(coluna) - 'a';

    if(LIS_IrIndice(tabuleiro->lista, linha) != LIS_CondRetOK)
        return NULL;
    lista = (LIS_tppLista)LIS_ObterValor(tabuleiro->lista);
    if(!lista)
        return NULL;
    if(LIS_IrIndice(lista, coluna) != LIS_CondRetOK)
        return NULL;

    return LIS_ObterValor(lista);
}/* Fim fun��o: TAB  &Obter valor de uma pe�a no tabuleiro */

/***************************************************************************
*
*  Fun��o: TAB  &Setar valor de uma pe�a no tabuleiro
*  ****/

void TAB_setarCasa(Tabuleiro *tabuleiro, int linha, char coluna, Peca *peca)
{
    LIS_tppLista lista;
    Peca *antiga;
#ifdef _DEBUG
    assert(tabuleiro);
#endif

    --linha;
    coluna = tolower(coluna) - 'a';

    if(LIS_IrIndice(tabuleiro->lista, linha) != LIS_CondRetOK)
        return;
    lista = (LIS_tppLista)LIS_ObterValor(tabuleiro->lista);
    if(!lista)
        return;
    if(LIS_IrIndice(lista, coluna) != LIS_CondRetOK)
        return;

    antiga = LIS_ObterValor(lista);
    if(antiga)
        ListaExcluirPeca(antiga);

    LIS_SetarValor(lista, peca);
}/* Fim fun��o: TAB  &Setar valor de uma pe�a no tabuleiro */

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/   

/***************************************************************************
*
*  $FC Fun��o: TAB  -Excluir elemento de uma lista
*
*  $ED Descri��o da fun��o
*
*      Atrav�s da fun��o (PEC_destruir(Peca *peca)) provida pelo
*      m�dulo PEC (pe�a), est� fun��o elimina uma pe�a do tabuleiro
*      
*  $EP Par�metros 
*
*      $P void *pDado - um ponteiro para um tipo void (qualquer).
*      
*
*  $FV Valor retornado 
*
*        N�o possui valor de retorno, simplesmente elimina (free())
*        uma pe�a do tabuleiro.
*
*  ****/
void ListaExcluirPeca(void *pDado)                           
{                                                             
    Peca *peca = (Peca*)pDado;
    PEC_destruir(peca);
}/* Fim fun��o: TAB  -Excluir elemento de uma lista */

/***************************************************************************
*
*  $FC Fun��o: TAB  -Excluir uma lista
*
*  $ED Descri��o da fun��o
*
*      Atrav�s da fun��o (LIS_DestruirLista(LIS_tppLista lista))
*      provida pelo m�dulo LIS (lista), est� fun��o elimina linha do
*      tabuleiro.
*      
*  $EP Par�metros 
*
*      $P void *pDado - um ponteiro para um tipo void (qualquer).
*      
*
*  $FV Valor retornado 
*
*        N�o possui valor de retorno, simplesmente elimina (free())
*        uma linha do tabuleiro.
*
*  ****/
void ListaExcluirLista(void *pDado)                         
{
    LIS_tppLista lista = (LIS_tppLista)pDado;
    LIS_DestruirLista(lista);
}/* Fim fun��o: TAB  -Excluindo uma lista */ 

/********** Fim do m�dulo de implementa��o: TAB  Tabuleiro **********/
