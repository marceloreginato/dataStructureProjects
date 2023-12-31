#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncad.h"  //inclui os Prototipos
#include <string.h>

Cursor* cria_cursor(){
    Cursor* cursor;

    cursor = (Cursor*)malloc(sizeof(Cursor));
    if(cursor != NULL)
        *cursor = NULL;
    return cursor;
}

void libera_cursor(Cursor* cursor){
    if(cursor != NULL)
        free(cursor);
}

Lista* cria_lista()
{
    Lista* li;

    li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li)
{
    if(li != NULL){
        Elem* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int consulta_lista_pos(Lista* li, int pos, Elem **el)
{
    if(li == NULL || pos <= 0)
        return ERRO;
    Elem *no = *li;
    int i = 1;
    while(no != NULL && i < pos){
        no = no->prox;
        i++;
    }
    if(no == NULL)
        return ERRO;
    else{
        *el = no;
        return OK;
    }
}

int consulta_lista_dado(Lista* li, Tipo_Dado dt, Elem **el)
{
    Elem *no;

    no = *li;
    if(li == NULL)
        return ERRO;
    while(no != NULL && no->dado != dt){
        no = no->prox;
    }
    if(no == NULL)
        return ERRO;
    else{
        *el = no;
        return OK;
    }
}

int insere_lista_final(Lista* li, Cursor* cursor, Tipo_Dado dt)
{
    Elem *no;

    if (li == NULL) return ERRO;
    no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return ERRO;

    strncpy(no->dado, dt, 10);
    no->prox = NULL;
    if ((*li) == NULL) { //lista vazia: insere inicio
        *li = no;
        *cursor = *li;
    } else {
        Elem *aux;
        aux = *li;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = no;
        *cursor = no; // cursor aponta para a palavra inserida no final
    }
    return OK;
}

int insere_lista_inicio(Lista* li, Cursor* cursor, Tipo_Dado dt)
{
    Elem* no;

    if (li == NULL) return ERRO;
    no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return ERRO;

    strncpy(no->dado, dt, 10);
    no->prox = (*li);
    *li = no;
    *cursor = no;  // cursor aponta para a palavra inserida no inicio

    return OK;
}

int insere_lista_ordenada(Lista* li, Tipo_Dado dt)
{
    if (li == NULL) return ERRO;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return ERRO;

    strncpy(no->dado, dt, 10);
    if ((*li) == NULL) { //lista vazia: insere in�cio
        no->prox = NULL;
        *li = no;
        return OK;
    }
    else {
        Elem *ant, *atual = *li;
        while (atual != NULL && atual->dado < dt) {
            ant = atual;
            atual = atual->prox;
        }
        if (atual == *li) { //insere in�cio
            no->prox = (*li);
            *li = no;
        }
        else
        {
            no->prox = atual;
            ant->prox = no;
        }
        return OK;
    }
}

// Novas rotinas: Insere Antes e Insere Depois
int insere_lista_antes(Lista* li, Cursor* cursor, Tipo_Dado dt)
{
    if (li == NULL) return ERRO;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return ERRO;

    strncpy(no->dado, dt, 10);
    if ((*cursor == NULL) && (*li==NULL))  { //lista vazia: insere inicio
        no->prox = NULL;
        *li = no;
        *cursor = no;
        return OK;
    }
    else
    {
        Elem *ant, *atual = *li;
        while (atual != NULL && atual != *cursor) {  // Acha o nodo e seu anterior
            ant = atual;
            atual = atual->prox;
        }

        if (atual != *cursor) // Ops: nao achou o nodo de referencia para insercao!
            return ERRO;

        if (atual == *li) { //insere antes (no inicio da lista)
            no->prox = (*li);
            *li = no;
            *cursor = no;
        }
        else
        {
            no->prox = atual;
            ant->prox = no;
            *cursor = no;
        }
        return OK;
    }
}

int insere_lista_depois(Lista* li, Cursor* cursor, Tipo_Dado dt)
{
    Elem *no;

    if (li == NULL) return ERRO;
    no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return ERRO;

    strncpy(no->dado, dt, 10);
    if ((*cursor == NULL) && (*li==NULL))  // Lista vazia
       no->prox = NULL;
    else
       if ((*cursor == NULL) || (*li==NULL))  // Inconsistencia nos parametros (ponteiros) da rotina
           return(ERRO);

    if ((*li) == NULL) { // Lista vazia: insere inicio
        *li = no;
        *cursor = no;
    }
    else
    {
        no->prox  = (*cursor)->prox;
        (*cursor)->prox = no;
        *cursor = no;
    }
    return OK;
}

int remove_lista(Lista* li, Tipo_Dado dt)
{
    if(li == NULL)
        return ERRO;
    if((*li) == NULL)//lista vazia
        return ERRO;
    Elem *ant, *no = *li;
    while(no != NULL && no->dado != dt){
        ant = no;
        no = no->prox;
    }
    if(no == NULL) //nao encontrado
        return ERRO;

    if(no == *li) //remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return OK;
}

int remove_lista_inicio(Lista* li)
{
    if(li == NULL)
        return ERRO;
    if((*li) == NULL) //lista vazia
        return ERRO;

    Elem *no = *li;
    *li = no->prox;
    free(no);
    return OK;
}

int remove_lista_final(Lista* li)
{
    if(li == NULL)
        return ERRO;
    if((*li) == NULL) //lista vazia
        return ERRO;

    Elem *ant, *no = *li;
    while(no->prox != NULL){
        ant = no;
        no = no->prox;
    }

    if(no == (*li)) //remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return OK;
}

int tamanho_lista(Lista* li)
{
    if(li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li)
{
    return 0;
}

int lista_vazia(Lista* li)
{
    if(li == NULL)
        return 1;
    if(*li == NULL)
        return 1;
    return 0;
}

void imprime_lista(Lista* li)
{
    if(li == NULL)
        return;
    Elem* no = *li;
    while(no != NULL){
        printf("%s ", no->dado); 
        no = no->prox;
    }
}

void imprime_cursor(Cursor* cursor){

    if(cursor == NULL)
        return;
    printf("O cursor se encontra em: %s\n", (*cursor)->dado);

}

int buscar_palavra(Lista* li, Cursor* cursor, Tipo_Dado chave){

    if(li == NULL)
        return ERRO;
    if((*li) == NULL) // lista vazia
        return ERRO;
    if(cursor == NULL)
        return ERRO;
    Elem *aux;
    aux = *cursor;
    while(aux->prox != NULL && strcmp(chave, aux->dado) != 0) // busca palavra chave
        aux = aux->prox;
    if(strcmp(chave, aux->dado) == 0){  //verifica se achou a palavra chave ou terminou a lista
        *cursor = aux;
        return OK;
    }
    else if(aux->prox == NULL)  // se terminou a lista cursor continua no mesmo lugar
        return OK;
}

int remove_lista_cursor(Lista* li, Cursor* cursor){

    if(li == NULL)
        return ERRO;
    if((*li) == NULL)//lista vazia
        return ERRO;
    Elem *ant, *no = *li;
    while(no != NULL && no->dado != (*cursor)->dado){ // busca a palavra onde esta posicionado o cursor
        ant = no;
        no = no->prox;
    }
    if(no == NULL) //nao encontrado
        return ERRO;

    if(no == *li){ //remover o primeiro e inserir cursor no inicio
        *li = no->prox;
        *cursor = no->prox;
        free(no);
        return OK;
    }
    else{                     // remover e inserir cursor na posicao imediatamente anterior
        ant->prox = no->prox;
        *cursor = ant;
        free(no);
        return OK;
    }
}

int go_inicio(Lista* li, Cursor* cursor){

    if(li == NULL)
        return ERRO;
    if(cursor ==  NULL)
        return ERRO;
    *cursor = *li;
    return OK;
}

int go_fim(Lista* li, Cursor* cursor){

    if(li == NULL)
        return ERRO;
    if(cursor ==  NULL)
        return ERRO;
    if(*li == NULL){                // lista vazia apontar para NULL
        *cursor = *li;
        return OK;
    }
    Elem* aux = *li;
    while(aux->prox != NULL)
        aux = aux->prox;
    *cursor = aux;
    return OK;
}

int go_prox(Lista* li, Cursor* cursor){

    if(li == NULL)
        return ERRO;
    if(cursor == NULL)
        return ERRO;
    if(*li == NULL){                            // lista vazia aponta para NULL
        *cursor = *li;
        return OK;
    }
    *cursor = (*cursor)->prox;                  // aponta para NULL caso o cursor esteja em ultimo
    return OK;
}

int go_ant(Lista* li, Cursor* cursor){

    if(li == NULL)
        return ERRO;
    if(cursor ==  NULL)
        return ERRO;
    Elem *ant, *no = *li;
    while(no != NULL && no->dado != (*cursor)->dado){ // busca a palavra onde esta posicionado o cursor e acha sua anterior
        ant = no;
        no = no->prox;
    }
    if(no == *li)   // caso cursor esteja na primeira posicao escohli continuar nela
        *cursor = *li;
    else
        *cursor = ant;
    return OK;
}