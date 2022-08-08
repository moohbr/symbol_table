#include <stdio.h>
#include <stdlib.h>
#include "tabela_simbolos.h"

struct stab
{
  int (*compara)(const void *, const void *);
  void *elemento;
  struct stab *esq;
  struct stab *dir;
};

typedef struct stab *TABELA;

TABELA cria_tabela(int (*compara)(const void *, const void *))
{
  TABELA nova = (TABELA)malloc(sizeof(struct stab));
  nova->compara = compara;
  nova->elemento = NULL, nova->esq = NULL, nova->dir = NULL;
  return nova;
}

void adiciona_elemento(TABELA tab, void *elemento)
{
  if (!tab->elemento)
  {
    tab->elemento = elemento; // se a tabela estiver vazia, adiciona o elemento
    return;
  }
  if (tab->compara(elemento, tab->elemento) < 0) // se o elemento for menor que o elemento da tabela, adiciona no lado esquerdo
  {
    if (!tab->esq) // se o lado esquerdo da tabela estiver vazio, adiciona o elemento
      tab->esq = cria_tabela(tab->compara);
    adiciona_elemento(tab->esq, elemento); // se o lado esquerdo da tabela não estiver vazio, adiciona o elemento no lado esquerdo
  }
  if (tab->compara(elemento, tab->elemento) > 0) // se o elemento for menor que o elemento da tabela, adiciona no lado direito
  {
    if (!tab->dir) // se o lado direito da tabela estiver vazio, adiciona o elemento
      tab->dir = cria_tabela(tab->compara);
    adiciona_elemento(tab->dir, elemento); // se o lado direito da tabela não estiver vazio, adiciona o elemento no lado direito
  }
  return;
}

void *busca_elemento(TABELA tab, void *elemento)
{
  if (!tab) // tabela vazia não tem elemento, logo não tem busca
    return NULL;
  if (!tab->elemento) // elemento é nulo, logo não tem busca
    return NULL;
  if (tab->compara(tab->elemento, elemento) == 0) // elemento é o elemento da tabela
    return tab->elemento;
  return (tab->compara(tab->elemento, elemento) > 0) ? busca_elemento(tab->esq, elemento) : busca_elemento(tab->dir, elemento); // elemento é menor que o elemento da tabela, logo busca na subárvore esquerda, caso contrário busca na subárvore direita
  return NULL;                                                                                                                  // Caso padrão: elemento não encontrado
}

void imprime_crescente(TABELA tab, void (*imprime)(const void *))
{
  if (!tab)                               // Verifica se a tabela eh nula
    return;                               // Não imprime pois pode dar problema
  if (tab->esq)                           // Verifica se a tabela tem filho a esquerda
    imprime_crescente(tab->esq, imprime); // Chama a funcao recursivamente para imprimir a subarvore esquerda
  imprime(tab->elemento);                 // Imprime a cabeca da arvore
  printf("\n");                           // Imprime um espaco entre os elementos
  if (tab->dir)                           // Verifica se a tabela tem filho a direita
    imprime_crescente(tab->dir, imprime); // Chama a funcao recursivamente para imprimir a subarvore direita
}
