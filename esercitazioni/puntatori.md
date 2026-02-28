# Basi sui puntatori in C++

## Indice
1. [Introduzione ai Puntatori](#introduzione-ai-puntatori)
2. [Basi dei Puntatori](#basi-dei-puntatori)
3. [Puntatori e Array](#puntatori-e-array)
4. [Aritmetica dei Puntatori](#aritmetica-dei-puntatori)
5. [Puntatori e Funzioni](#puntatori-e-funzioni)
6. [Allocazione Dinamica della Memoria](#allocazione-dinamica-della-memoria)
7. [Errori Comuni e Buone Pratiche](#errori-comuni-e-buone-pratiche)

---

## Introduzione ai Puntatori

### Cos'è un Puntatore? - Un'Analogia Semplice

Pensa alla memoria del computer come a un grande condominio:
- Ogni **appartamento** è una posizione di memoria
- Ogni **numero di appartamento** è un indirizzo di memoria
- Ogni **inquilino** è un valore memorizzato
- Un **puntatore** è come un post-it con il numero di appartamento di qualcuno



### Perché Abbiamo Bisogno dei Puntatori?

I puntatori risolvono diverse sfide fondamentali della programmazione:

1. **Manipolazione Efficiente degli Array**: Invece di copiare interi array, possiamo passare il loro indirizzo iniziale
2. **Memoria Dinamica**: Creare strutture dati che possono crescere/diminuire durante l'esecuzione
3. **Parametri di Funzione**: Modificare variabili passate alle funzioni (passaggio per riferimento)
4. **Strutture Dati**: Costruire liste concatenate, alberi, grafi dove gli elementi puntano l'uno all'altro
5. **Prestazioni**: Evitare di copiare grandi quantità di dati
6. **Accesso Hardware**: Interagire direttamente con dispositivi mappati in memoria

### Layout della Memoria - Il Quadro Generale

La Memoria del tuo Computer:

|---|---|---|---|
| Sezione Codice| Sezione Dati| Stack │  Heap |
|---|---|---|---|

Ogni cella di memoria ha:

- Un indirizzo (come un numero civico)
- Un valore (cosa è memorizzato lì)
- Un tipo (come interpretare il valore)



---

## Basi dei Puntatori

### 1. Dichiarare i Puntatori - Sintassi Spiegata

```cpp
#include <iostream>
using namespace std;

int main() {
    // L'asterisco (*) significa "puntatore a"
    int* ptr1;      // puntatore a un intero
    char* ptr2;     // puntatore a un carattere
    double* ptr3;   // puntatore a un double

    // Perché tipi diversi? Il tipo del puntatore dice al compilatore:
    // 1. Quanti byte leggere quando si dereferenzia
    // 2. Come interpretare quei byte
    // 3. Quanto aggiungere quando si fa aritmetica dei puntatori

    cout << "Dimensione di int*: " << sizeof(int*) << " bytes" << endl;
    cout << "Dimensione di char*: " << sizeof(char*) << " bytes" << endl;
    cout << "Nota: Tutti i puntatori hanno la stessa dimensione sullo stesso sistema!" << endl;
    cout << "Sanno solo come interpretare diversi tipi di dati." << endl;

    // Errore comune: Dichiarazioni multiple
    int* p, q;      // p è puntatore, q è int! (l'asterisco si applica solo a p)
    int *r, *s;     // Sia r che s sono puntatori (asterisco con ciascuno)

    cout << "\nRegole di dichiarazione dei puntatori:" << endl;
    cout << "int* p, q;    -> p è puntatore, q è int" << endl;
    cout << "int *p, *q;   -> entrambi sono puntatori" << endl;

    return 0;
}

```

### 2. Ottenere indirizzo con l'Operatore &

La "e commericale" (&) agisce come chiedere "Dove abiti?"

```cpp
#include <iostream>
using namespace std;

int main() {
    int numero = 42;
    double prezzo = 99.99;
    char lettera = 'A';

    cout << "=== COMPRENDERE GLI INDIRIZZI ===" << endl;
    cout << "Variabile: numero" << endl;
    cout << "  Valore:  " << numero << endl;
    cout << "  Indirizzo: " << &numero << " (esadecimale)" << endl;
    cout << "  Nota:    Gli indirizzi sono solitamente mostrati in esadecimale" << endl;
    cout << endl;

    cout << "Variabile: prezzo" << endl;
    cout << "  Valore:  " << prezzo << endl;
    cout << "  Indirizzo: " << &prezzo << endl;
    cout << "  Nota:    Variabili diverse hanno indirizzi diversi" << endl;
    cout << endl;

    cout << "Variabile: lettera" << endl;
    cout << "  Valore:  " << lettera << endl;
    cout << "  Indirizzo: " << (void*)&lettera << endl;
    cout << "  Nota:    Cast speciale necessario per char* per stampare come indirizzo" << endl;

    return 0;
}#include <iostream>
using namespace std;

int main() {
    int numero = 42;
    double prezzo = 99.99;
    char lettera = 'A';

    cout << "=== COMPRENDERE GLI INDIRIZZI ===" << endl;
    cout << "Variabile: numero" << endl;
    cout << "  Valore:  " << numero << endl;
    cout << "  Indirizzo: " << &numero << " (esadecimale)" << endl;
    cout << "  Nota:    Gli indirizzi sono solitamente mostrati in esadecimale" << endl;
    cout << endl;

    cout << "Variabile: prezzo" << endl;
    cout << "  Valore:  " << prezzo << endl;
    cout << "  Indirizzo: " << &prezzo << endl;
    cout << "  Nota:    Variabili diverse hanno indirizzi diversi" << endl;
    cout << endl;

    cout << "Variabile: lettera" << endl;
    cout << "  Valore:  " << lettera << endl;
    cout << "  Indirizzo: " << (void*)&lettera << endl;
    cout << "  Nota:    Cast speciale necessario per char* per stampare come indirizzo" << endl;

    return 0;
}
```



### 3. Dereferenziare con l'Operatore *

L'asterisco (\*) quando usato su un puntatore significa "vai a questo indirizzo e prendi il valore"

```cpp
#include <iostream>
using namespace std;

int main() {
    int voto = 28;
    int* ptr = &voto;  // ptr memorizza l'indirizzo di voto

    cout << "=== DEREFERENZIAMENTO DEI PUNTATORI SPIEGATO ===" << endl;
    cout << "Variabile originale:" << endl;
    cout << "  voto = " << voto << endl;
    cout << "  &voto = " << &voto << " (indirizzo dove vive voto)" << endl;
    cout << endl;

    cout << "Variabile puntatore:" << endl;
    cout << "  ptr = " << ptr << " (contiene l'indirizzo di voto)" << endl;
    cout << "  *ptr = " << *ptr << " (vai all'indirizzo ptr e prendi il valore)" << endl;
    cout << endl;

    // Modificare attraverso il puntatore
    cout << "Modificare il valore attraverso il puntatore:" << endl;
    *ptr = 100;  // "Vai all'indirizzo ptr e imposta quel valore a 100"
    cout << "  Dopo *ptr = 100:" << endl;
    cout << "  voto = " << voto << " (variabile originale cambiata!)" << endl;
    cout << "  *ptr = " << *ptr << " (il puntatore mostra lo stesso valore)" << endl;

    return 0;
}

```

