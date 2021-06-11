#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "tree.h"
#include <limits.h>

/** @brief NV viene usato per gli Elemtype di tipo "int" con valore 'INT_MAX' per definire i valori NULL nel vettore scritto per livelli per costruire un albero. */
#define NV INT_MAX

/** @brief TAB_SIZE viene usato per gli spazi usati per una tabulazione nella stampa di un albero per livelli. */
#define TAB_SIZE 3

/** @brief NV_PRINT viene usato come carattere stampato in caso di puntatore a NULL nella stampa di un albero per livelli. */
#define NV_PRINT 'X'

/** @brief FRECCIA_SX viene usato come carattere stampato per rappresentare una freccia sinistra nella stampa di un albero per livelli. */
#define FRECCIA_SX (char)-55 //(char)-38

/** @brief FRECCIA_DX viene usato come carattere stampato per rappresentare una freccia destra nella stampa di un albero per livelli. */
#define FRECCIA_DX (char)-69 //(char)-65

/** @brief PLUS viene usato come carattere stampato per rappresentare il link coi figli nella stampa di un albero per livelli. */
#define PLUS (char)-54 //(char)-63

/** @brief LINE viene usato come carattere stampato per rappresentare la linea di collegamento coi figli nella stampa di un albero per livelli. */
#define LINE (char)-51 //(char)-60

/**
@brief La funzione ritorna l'altezza dell'albero "n".
@param[in] n: Puntatore dell'albero.
@return La funzione ritorna l'altezza dell'albero puntato da "n".
*/
extern size_t TreeGetHeight(Node* n);

/**
@brief La funzione confronta due alberi e ritorna se contengono gli stessi elementi nella stessa posizione.
@param[in] n1: Puntatore del primo albero.
@param[in] n2: Puntatore del secondo albero.
@return La funzione ritorna 'true' se gli alberi "n1" e "n2" hanno gli stessi valori nella stessa posizione 'false' altrimenti.
*/
extern bool TreeIsSame(Node* n1, Node* n2);

/**
@brief La funzione costruisce un albero a partire da un vettore strutturato per livelli e lo ritorna.
@param[in] v: Vettore di Elemtype per popolare l'albero.
@param[in] v_size: Dimensione del vettore "v".
@return La funzione ritorna un albero costituito dagli elementi presenti nel vettore "v" seguendo l'ordine per livelli.
*/
extern Node* TreeFromLevelVector(const ElemType* v, size_t v_size);

/**
@brief La funzione ritorna un vettore di ElemType costituito dagli elementi del livello "level" dell'albero "n".
@param[in] n: Puntatore dell'albero.
@param[in] level: Livello dell'albero che si vuole ottenere (può essere maggiore dell'altezza dell'albero).
@return La funzione ritorna un vettore di dimensione '2 alla level' di ElemType costituito dagli elementi presenti nel livello "level" dell'albero "n", dove non presenti elementi saranno NULL.
*/
extern const ElemType** TreeGetLevelValues(const Node* n, size_t level);

/**
@brief La funzione stampa su stdout l'albero "n" per livelli, i valori NULL sono rappresentati da 'X'.
@param[in] n: Puntatore dell'albero.
@return Nessun valore di ritorno.
*/
extern void TreePrintLevel(Node* n);

/* FUNZIONI UTILIZZATE ALL'INTERNO DEL FILE alex_tree.c */

/**
@brief La funzione viene utilizzata per trovare l'altezza di un albero in modo ricorsivo.
@param[in] n: Puntatore dell'albero.
@param[in] curr_lvl: Livello attuale durante l'esplorazione dell'albero "n".
@param[out] level: Puntatore a size_t che contiene il valore massimo di ogni "curr_lvl" durante l'esplorazione dell'albero "n".
@return Nessun valore di ritorno.
*/
static void TreeGetHeightRec(Node* n, size_t curr_lvl, size_t* level);

/**
@brief La funzione viene utilizzata per verificare l'ugualianza degli alberi "n1" e "n2" in modo ricorsivo.
@param[in] n1: Puntatore al primo albero.
@param[in] n2: Puntatore al secondo albero.
@param[out] same: Puntatore a bool che contiene il valore 'true' o 'false' dell'ugualianza dei valori contenuti durante l'esplorazione degli alberi "n1" e "n2".
@return Nessun valore di ritorno.
*/
static void TreeIsSameRec(Node* n1, Node* n2, bool* same);

/**
@brief La funzione viene utilizzata per costruire un vettore di ElemType costituito dagli elementi del livello "level" dell'albero "n" in modo ricorsivo.
@param[in] n: Puntatore dell'albero.
@param[out] ris: Puntatore al vettore di Elemtype* che conterrà tutti i puntatori ai vari ElemType di un livello (può contenere dei valori NULL).
@param[in] level: Livello dell'albero che si vuole ottenere (può essere maggiore dell'altezza dell'albero).
@param[in] curr_lvl: Livello attuale durante l'esplorazione dell'albero.
@param[in] index: Puntatore a size_t che contiene l'indice per scrivere un elemento dentro al vettore "ris".
@return Nessun valore di ritorno.
*/
static void TreeGetLevelValuesRec(const Node* n, const ElemType** ris, size_t level, size_t curr_lvl, size_t* index);

/**
@brief La funzione viene utilizzata per scrivere n * TAB_SIZE spazi nella stringa "str".
@param[out] str: Stringa di destinazione.
@param[in] n: Numero di TAB_SIZE spazi da stampare nella stringa "str".
@return Nessun valore di ritorno.
*/
static void PrintfNTabOnString(char* str, size_t n);

/**
@brief La funzione viene utilizzata per scrivere il contenuto del puntatore a Elemtype "e" nella stringa "str".
@param[out] str: Stringa di destinazione.
@param[in] e: Puntatore all'elemento da stampare (può essere NULL, in questo caso stamperà NV_PRINT).
@return Nessun valore di ritorno.
*/
static void PrintfInString(char* str, const ElemType* e);

/**
@brief La funzione viene utilizzata per costruire un vettore di vettori di ElemType costituito dai livelli dell'albero "n" dove ogni vettore è costituito dai puntatori agli elementi del livello dell'albero (anche NULL).
@param[in] n: Puntatore dell'albero.
@return Vettore di dimensione altezza dell'albero "n" + 1 contenente vettori di dimensione '2 alla level' contenente i puntatori a ElemType, possono essere NULL.
*/
static const ElemType*** TreeGetLevelVectors(Node* n);