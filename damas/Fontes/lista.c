
/***************************************************************************
*  $MCI M�dulo de implementa��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.c
*  Letras identificadoras:      LIS
*  
*  Projeto: damas
*  Arquivo: damas\Fontes\lista.c   
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
*		 programas redigidos em C; m�dulo Lista Duplamente Encadeada
***************************************************************************/

#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <malloc.h>
#include <assert.h>

#define LISTA_OWN
#include "lista.h"
#undef LISTA_OWN


/***********************************************************************
*
*  $TC Tipo de dados: LIS Elemento da lista
*
*
***********************************************************************/

typedef struct tagElemLista {
    void *pValor;
		/* Ponteiro para o valor contido no elemento */
    struct tagElemLista *pAnt;
		/* Ponteiro para o elemento antecessor */
    struct tagElemLista *pProx;
		/* Ponteiro para o elemento sucessor */
} tpElemLista;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Descritor da cabe�a de lista
*
*
***********************************************************************/

typedef struct LIS_tagLista {
    tpElemLista *pOrigemLista;
		/* Ponteiro para a origem da lista */
    tpElemLista *pFimLista;
		/* Ponteiro para o final da lista */
    tpElemLista *pElemCorr;
		/* Ponteiro para o elemento corrente da lista */
    int numElem;
		/* N�mero de elementos da lista */
    void (*ExcluirValor)(void *pValor);
		/* Ponteiro para a fun��o de destrui��o do valor contido em um elemento */
} LIS_tpLista;

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

static void LiberarElemento(LIS_tppLista pLista, tpElemLista *pElem);
static tpElemLista * CriarElemento(LIS_tppLista pLista, void *pValor);
static void LimparCabeca(LIS_tppLista pLista);

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: LIS  &Criar lista
*  ****/

LIS_tppLista LIS_CriarLista(void (*ExcluirValor)(void *pDado))
{
    LIS_tpLista *pLista = NULL;
    pLista = (LIS_tpLista*)malloc(sizeof(LIS_tpLista));
    if(pLista == NULL)
        return NULL;

    LimparCabeca(pLista);
    pLista->ExcluirValor = ExcluirValor;
    return pLista;
} /* Fim fun��o: LIS  &Criar lista */

/***************************************************************************
*
*  Fun��o: LIS  &Destruir lista
*  ****/

void LIS_DestruirLista(LIS_tppLista pLista)
{
#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    LIS_EsvaziarLista(pLista);
    free(pLista);
} /* Fim fun��o: LIS  &Destruir lista */

/***************************************************************************
*
*  Fun��o: LIS  &Esvaziar lista
*  ****/

void LIS_EsvaziarLista(LIS_tppLista pLista)
{
    tpElemLista *pElem;
    tpElemLista *pProx;

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    pElem = pLista->pOrigemLista;
    while(pElem != NULL) {
        pProx = pElem->pProx;
        LiberarElemento(pLista , pElem);
        pElem = pProx;
    }

    LimparCabeca(pLista);
}  /* Fim fun��o: LIS  &Esvaziar lista */

/***************************************************************************
*
*  Fun��o: LIS  &Inserir elemento antes
*  ****/

LIS_tpCondRet LIS_InserirElementoAntes(LIS_tppLista pLista, void *pValor)
{
    tpElemLista *pElem;

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    pElem = CriarElemento(pLista , pValor);
    if(pElem == NULL)
        return LIS_CondRetFaltouMemoria;

    if(pLista->pElemCorr == NULL) {
        pLista->pOrigemLista = pElem;
        pLista->pFimLista = pElem;
    }
    else {
        if(pLista->pElemCorr->pAnt != NULL) {
            pElem->pAnt = pLista->pElemCorr->pAnt;
            pLista->pElemCorr->pAnt->pProx = pElem;
        }
        else
            pLista->pOrigemLista = pElem;

        pElem->pProx = pLista->pElemCorr;
        pLista->pElemCorr->pAnt = pElem;
    }

    pLista->pElemCorr = pElem;
    return LIS_CondRetOK;
} /* Fim fun��o: LIS  &Inserir elemento antes */

/***************************************************************************
*
*  Fun��o: LIS  &Inserir elemento ap�s
*  ****/

LIS_tpCondRet LIS_InserirElementoApos(LIS_tppLista pLista , void *pValor)
{
    tpElemLista * pElem;

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    pElem = CriarElemento(pLista , pValor);
    if(pElem == NULL)
        return LIS_CondRetFaltouMemoria;
    if(pLista->pElemCorr == NULL) {
        pLista->pOrigemLista = pElem;
        pLista->pFimLista = pElem;
    }
    else {
        if(pLista->pElemCorr->pProx != NULL) {
            pElem->pProx = pLista->pElemCorr->pProx;
            pLista->pElemCorr->pProx->pAnt = pElem;
        } else
            pLista->pFimLista = pElem;

        pElem->pAnt = pLista->pElemCorr;
        pLista->pElemCorr->pProx = pElem;
    }

    pLista->pElemCorr = pElem;
    return LIS_CondRetOK;
} /* Fim fun��o: LIS  &Inserir elemento ap�s */

/***************************************************************************
*
*  Fun��o: LIS  &Excluir elemento
*  ****/

LIS_tpCondRet LIS_ExcluirElemento(LIS_tppLista pLista)
{
    tpElemLista * pElem;

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    if(pLista->pElemCorr == NULL)
        return LIS_CondRetListaVazia;

    pElem = pLista->pElemCorr;

    if(pElem->pAnt != NULL) {
        pElem->pAnt->pProx = pElem->pProx;
        pLista->pElemCorr = pElem->pAnt;
    }
    else {
        pLista->pElemCorr = pElem->pProx;
        pLista->pOrigemLista = pLista->pElemCorr;
    }

    if(pElem->pProx != NULL)
        pElem->pProx->pAnt = pElem->pAnt;
    else
        pLista->pFimLista = pElem->pAnt;

    LiberarElemento(pLista , pElem);
    return LIS_CondRetOK;
} /* Fim fun��o: LIS  &Excluir elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*  ****/

void * LIS_ObterValor(LIS_tppLista pLista)
{
#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    if(pLista->pElemCorr == NULL)
        return NULL;
    return pLista->pElemCorr->pValor;
} /* Fim fun��o: LIS  &Obter refer�ncia para o valor contido no elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Setar valor do elemento corrente
*  ****/

LIS_tpCondRet LIS_SetarValor(LIS_tppLista pLista, void *pValor)
{
#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    if(pLista->pElemCorr == NULL)
        return LIS_CondRetListaVazia;
    pLista->pElemCorr->pValor = pValor;
    return LIS_CondRetOK;
} /* Fim fun��o: LIS  &Setar valor do elemento corrente */

/***************************************************************************
*
*  Fun��o: LIS  &Ir para o elemento inicial
*  ****/

void LIS_IrInicioLista(LIS_tppLista pLista)
{
#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    pLista->pElemCorr = pLista->pOrigemLista;
} /* Fim fun��o: LIS  &Ir para o elemento inicial */

/***************************************************************************
*
*  Fun��o: LIS  &Ir para o elemento final
*  ****/

void LIS_IrFinalLista(LIS_tppLista pLista)
{
#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    pLista->pElemCorr = pLista->pFimLista;
} /* Fim fun��o: LIS  &Ir para o elemento final */

/***************************************************************************
*
*  Fun��o: LIS  &Ir para o elemento de ind�ce i
*  ****/

LIS_tpCondRet LIS_IrIndice(LIS_tppLista pLista, int i)
{
#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    LIS_IrInicioLista(pLista);
    return LIS_AvancarElementoCorrente(pLista, i);
} /* Fim fun��o: LIS  &Ir para o elemento de ind�ce i */

/***************************************************************************
*
*  Fun��o: LIS  &Avan�ar elemento
*  ****/

LIS_tpCondRet LIS_AvancarElementoCorrente(LIS_tppLista pLista , int numElem)
{
    int i;

    tpElemLista * pElem;

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    if(pLista->pElemCorr == NULL)
        return LIS_CondRetListaVazia;

    if(numElem > 0) {
        pElem = pLista->pElemCorr;
        for(i = numElem; i > 0; i--) {
            if(pElem == NULL)
                break;
            pElem = pElem->pProx;
        }

        if(pElem != NULL) {
            pLista->pElemCorr = pElem;
            return LIS_CondRetOK;
        }

        pLista->pElemCorr = pLista->pFimLista;
        return LIS_CondRetFimLista;
    }
    else if(numElem < 0) {
        pElem = pLista->pElemCorr;
        for(i = numElem ; i < 0 ; i++) {
            if(pElem == NULL)
                break;
            pElem = pElem->pAnt;
        }

        if(pElem != NULL) {
            pLista->pElemCorr = pElem;
            return LIS_CondRetOK;
        }

        pLista->pElemCorr = pLista->pOrigemLista;
        return LIS_CondRetFimLista;

    }
    return LIS_CondRetOK;
} /* Fim fun��o: LIS  &Avan�ar elemento */

/***************************************************************************
*
*  Fun��o: LIS  &Procurar elemento contendo valor
*  ****/

LIS_tpCondRet LIS_ProcurarValor(LIS_tppLista pLista , void * pValor)
{
    tpElemLista * pElem;

#ifdef _DEBUG
    assert(pLista != NULL);
#endif

    if(pLista->pElemCorr == NULL)
        return LIS_CondRetListaVazia;

    for(pElem = pLista->pElemCorr; pElem != NULL; pElem = pElem->pProx) {
        if(pElem->pValor == pValor) {
            pLista->pElemCorr = pElem;
            return LIS_CondRetOK;
        }
    }

    return LIS_CondRetNaoAchou;
} /* Fim fun��o: LIS  &Procurar elemento contendo valor */

/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: LIS  -Liberar elemento da lista
*
*  $ED Descri��o da fun��o
*     Elimina os espa�os apontados pelo valor do elemento e o
*     pr�prio elemento.
*
***********************************************************************/

void LiberarElemento(LIS_tppLista pLista , tpElemLista *pElem)
{
    if((pLista->ExcluirValor != NULL) && (pElem->pValor != NULL))
        pLista->ExcluirValor(pElem->pValor);

    free(pElem);
    pLista->numElem--;
} /* Fim fun��o: LIS  -Liberar elemento da lista */

/***********************************************************************
*
*  $FC Fun��o: LIS  -Criar o elemento
*  $ED Descri��o da fun��o
*     Cria os espa�os apontados pelo valor do elemento e o
*     pr�prio elemento.
*
***********************************************************************/

tpElemLista * CriarElemento(LIS_tppLista pLista , void * pValor)
{
    tpElemLista * pElem;

    pElem = (tpElemLista *)malloc(sizeof(tpElemLista));
    if(pElem == NULL)
        return NULL;

    pElem->pValor = pValor;
    pElem->pAnt = NULL;
    pElem->pProx = NULL;
    pLista->numElem++;
    return pElem;

} /* Fim fun��o: LIS  -Criar o elemento */

/***********************************************************************
*
*  $FC Fun��o: LIS  -Limpar a cabe�a da lista
*  $ED Descri��o da fun��o
*     
*     Elimina os todos os espa�os apontados pelo elemento de tipo
*     estruturado LIS_tppLista.
*
***********************************************************************/

void LimparCabeca(LIS_tppLista pLista)
{
    pLista->pOrigemLista = NULL;
    pLista->pFimLista = NULL;
    pLista->pElemCorr = NULL;
    pLista->numElem = 0;
} /* Fim fun��o: LIS  -Limpar a cabe�a da lista */


/********** Fim do m�dulo de implementa��o: LIS  Lista duplamente encadeada **********/
