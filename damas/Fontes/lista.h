
/***************************************************************************
*
*  $MCD Módulo de definição: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Projeto: damas
*  Arquivo: damas\fontes\lista.h  
*
*  $HA Histórico de evolução: 
*     Versão  Autor    Data     Observações
*     1       hs/mr/rh   30/abril/2014    implementação parcial do jogo
*    
*  
*  $ED Descrição do módulo
*     Implementa listas genéricas duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
*  $CRE Créditos
*    Arndt von Staa. Programa AutoTest - Arcabouço para a automação de testes de 
		 programas redigidos em C; módulo Lista Duplamente Encadeada
***************************************************************************/
#ifndef LISTA_
#define LISTA_
 
#ifdef LISTA_OWN
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct LIS_tagLista *LIS_tppLista ;

/***********************************************************************
*
*  $TC Tipo de dados: LIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

typedef enum {
    LIS_CondRetOK, /* Concluiu corretamente */
    LIS_CondRetListaVazia, /* A lista não contém elementos */
    LIS_CondRetFimLista, /* Foi atingido o fim de lista */
    LIS_CondRetNaoAchou, /* Não encontrou o valor procurado */
    LIS_CondRetFaltouMemoria /* Faltou memória ao tentar criar um elemento de lista */
} LIS_tpCondRet;

/***********************************************************************
*
*  $FC Função: LIS  &Criar lista
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*      $P ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/

LIS_tppLista LIS_CriarLista(void(*ExcluirValor)(void *pDado));

/***********************************************************************
*
*  $FC Função: LIS  &Destruir lista
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $FV Valor retornado
*     LIS_CondRetOK    - destruiu sem problemas
*
***********************************************************************/

void LIS_DestruirLista(LIS_tppLista pLista);

/***********************************************************************
*
*  $FC Função: LIS  &Esvaziar lista
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Parâmetros
*     $P pLista - ponteiro para a lista a ser esvaziada
*
***********************************************************************/

void LIS_EsvaziarLista(LIS_tppLista pLista);

/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento antes
*
*  $ED Descrição da função
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     $P pLista - ponteiro para a lista onde deve ser inserido o elemento
*     $P pValor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetFaltouMemoria
*
***********************************************************************/

LIS_tpCondRet LIS_InserirElementoAntes(LIS_tppLista pLista, void *pValor);

/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento após
*
*  $ED Descrição da função
*     Insere novo elemento apás o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     
*        $P pLista - ponteiro para a lista onde deve ser inserido o elemento
*        $P pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*
*
*  $FV Valor retornado
*     
*        LIS_CondRetOK 
*        LIS_CondRetFaltouMemoria 
*
***********************************************************************/

LIS_tpCondRet LIS_InserirElementoApos(LIS_tppLista pLista, void *pValor);

/***********************************************************************
*
*  $FC Função: LIS  &Excluir elemento
*
*  $ED Descrição da função
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  $EP Parâmetros
*     $P pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
***********************************************************************/

LIS_tpCondRet LIS_ExcluirElemento(LIS_tppLista pLista);

/***********************************************************************
*
*  $FC Função: LIS  &Obter referência para o valor contido no elemento
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no elemento corrente da lista
*
*  $EP Parâmetros
*     $P pLista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     não NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
***********************************************************************/

void *LIS_ObterValor(LIS_tppLista pLista);

/***********************************************************************
*
*  $FC Função: LIS  &Setar valor do elemento corrente
*
*  $ED Descrição da função
*     Estabelece o valor armazenado no elemento corrente
*
*  $EP Parâmetros
*     $P pLista - ponteiro para a lista que possui o elemento a ser alterado
*	$P  pValor - ponteiro para o novo valor do elemento corrente
*              Pode ser NUL
*
*  $FV Valor retornado
*     LIS_CondRetOK          - se concluiu corretamente
*	  LIS_CondRetListaVazia  - se a lista estiver vazia		
*
***********************************************************************/

LIS_tpCondRet LIS_SetarValor(LIS_tppLista pLista, void *pValor);

/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento inicial
*
*  $ED Descrição da função
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     $P pLista - ponteiro para a lista a manipular
*
***********************************************************************/

void LIS_IrInicioLista(LIS_tppLista pLista);

/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento final
*
*  $ED Descrição da função
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     $P pLista - ponteiro para a lista a manipular
*
***********************************************************************/

void LIS_IrFinalLista(LIS_tppLista pLista);

/***********************************************************************
*  $FC Função: LIS  &Ir para o elemento de indíce i
*
*  $ED Descrição da função
*     Torna corrente o elemento de indíce i da lista.
*	  Se o parâmetro i for maior que o número de elementos da lista,
*				torna corrente o elemento final da lista
*	  Se o parâmetro i for zero ou negativo, torna corrente o primeiro
*				elemento da lista
*
*  $EP Parâmetros
*     $P pLista - ponteiro para a lista a manipular
*	$P  i   - índice do elemento da lista a ser tornado elemento corrente
*
*  $FV Valor retornado
*     CondRetOK         - se o elemento de índice i existir e for o novo
*						  elemento corrente
*     CondRetFimLista   - se o parãmetro i for maior que o tamanho da lista
*						  ou negativo
*     CondRetListaVazia - se a lista está vazia
*
***********************************************************************/

LIS_tpCondRet LIS_IrIndice(LIS_tppLista pLista, int i);

/***********************************************************************
*
*  $FC Função: LIS  &Avançar elemento
*
*  $ED Descrição da função
*     Avança o elemento corrente numElem elementos na lista
*     Se numElem for positivo avança em direção ao final
*     Se numElem for negativo avança em direção ao início
*     numElem pode ser maior do que o númro de elementos existentes na
*               direção desejada
*     Se numElem for zero somente verifica se a lista está vazia
*
*  $EP Parâmetros
*     $P pLista  - ponteiro para a lista a ser manipulada
*     $P numElem - o número de elementos a andar
*
*  $FV Valor retornado
*     CondRetOK         - se numElem elementos tiverem sido andados
*     CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     CondRetListaVazia - se a lista está vazia
*
***********************************************************************/

LIS_tpCondRet LIS_AvancarElementoCorrente(LIS_tppLista pLista, int numElem);

/***********************************************************************
*
*  $FC Função: LIS  &Procurar elemento contendo valor
*
*  $ED Descrição da função
*     Procura o elemento que referencia o valor dado.
*     A função compara ponteiro e não conteúdo apontado.
*
*  $EP Parâmetros
*      $P pLista  - ponteiro para a lista onde procura
*      $P pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente é o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que contém o ponteiro procurado
*
*     LIS_CondRetNaoEncontrou - se o ponteiro não foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*
***********************************************************************/

LIS_tpCondRet LIS_ProcurarValor(LIS_tppLista pLista, void *pValor);

#undef LISTA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#endif
