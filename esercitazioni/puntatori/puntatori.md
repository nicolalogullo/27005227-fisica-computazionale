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

|Memoria|Funzione|
|:---:|:---:|
| Sezione Codice | Istruzioni |
| Sezione Dati | Variabili globali e statiche |
| Stack | Variabili locali\/ chiamate a funzioni |
| Heap | Memoria dinamica (new\/malloc) |


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


### 4. Puntatori Nulli


```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "=== PUNTATORI NULLI - PUNTATORI SICURI ===" << endl;

    // Diversi modi per creare puntatori nulli
    int* ptr1 = nullptr;  // C++ moderno (raccomandato)
    int* ptr2 = NULL;     // Vecchio stile C
    int* ptr3 = 0;        // Anche valido

    cout << "ptr1 (nullptr): " << ptr1 << endl;
    cout << "ptr2 (NULL): " << ptr2 << endl;
    cout << "ptr3 (0): " << ptr3 << endl;
    cout << "Tutti puntano all'indirizzo 0 (indirizzo nullo speciale)" << endl;
    cout << endl;

    // Perché usare puntatori nulli?
    cout << "Perché i puntatori nulli sono importanti:" << endl;
    cout << "1. Indicano che il puntatore non punta a memoria valida" << endl;
    cout << "2. Possono essere controllati prima dell'uso" << endl;
    cout << "3. Prevengono l'accesso accidentale a memoria casuale" << endl;
    cout << endl;

    // Controllo sicuro
    if (ptr1 == nullptr) {
        cout << "✓ ptr1 è nullo - sicuro da controllare prima dell'uso" << endl;
        cout << "  Controlla sempre se è nullo prima di dereferenziare!" << endl;
    }

    return 0;
}

```

### 5. Puntatori Void

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "=== PUNTATORI VOID - PUNTATORI SENZA TIPO ===" << endl;

    int numero = 42;
    char lettera = 'Z';
    double pi = 3.14159;

    void* puntatoreGenerico;  // Può puntare a QUALSIASI tipo di dato

    cout << "void* può memorizzare qualsiasi indirizzo, ma non conosce il tipo:" << endl;
    cout << endl;

    // Punta a int
    puntatoreGenerico = &numero;
    cout << "Punta a int (valore: " << numero << ")" << endl;
    cout << "  Indirizzo memorizzato: " << puntatoreGenerico << endl;

    // Deve fare il cast prima di dereferenziare
    cout << "  Dopo il cast a int*: " << *(static_cast<int*>(puntatoreGenerico)) << endl;
    cout << endl;

    // Punta a char
    puntatoreGenerico = &lettera;
    cout << "Punta a char (valore: " << lettera << ")" << endl;
    cout << "  Dopo il cast a char*: " << *(static_cast<char*>(puntatoreGenerico)) << endl;
    cout << endl;

    // Punta a double
    puntatoreGenerico = &pi;
    cout << "Punta a double (valore: " << pi << ")" << endl;
    cout << "  Dopo il cast a double*: " << *(static_cast<double*>(puntatoreGenerico)) << endl;

    return 0;
}

```

## Puntatori e Array

### 1. I nomi degli array come puntatori

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "=== ARRAY E PUNTATORI: LA CONNESSIONE SEGRETA ===" << endl;
    
    int arr[] = {10, 20, 30, 40, 50};
    
    cout << "Quando crei un array:" << endl;
    cout << "  int arr[] = {10, 20, 30, 40, 50};" << endl;
    cout << endl;
    
    cout << "Concetto chiave: arr è in realtà un puntatore al primo elemento!" << endl;
    cout << "  arr = " << arr << " (indirizzo del primo elemento)" << endl;
    cout << "  &arr[0] = " << &arr[0] << " (stesso indirizzo!)" << endl;
    cout << endl;
    
    cout << "Accedere agli elementi - due modi:" << endl;
    cout << "  Notazione array: arr[0] = " << arr[0] << endl;
    cout << "  Notazione puntatore: *arr = " << *arr << endl;
    cout << "  Notazione array: arr[2] = " << arr[2] << endl;
    cout << "  Aritmetica puntatori: *(arr + 2) = " << *(arr + 2) << endl;
    
    return 0;
}

```
### 2. Puntatori agli elementi degli array

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "=== MANIPOLARE ARRAY CON PUNTATORI ===" << endl;
    
    int numeri[] = {1, 2, 3, 4, 5};
    int* ptr = numeri;  // ptr punta al primo elemento
    
    cout << "Stato iniziale:" << endl;
    cout << "  ptr punta a: " << *ptr << " (primo elemento)" << endl;
    cout << endl;
    
    // Muovere il puntatore avanti
    cout << "Muoversi attraverso l'array:" << endl;
    
    ptr++;  // Passa al prossimo intero (4 byte avanti)
    cout << "  Dopo ptr++: punta a " << *ptr << endl;
    
    ptr++;  // Muovi di nuovo
    cout << "  Dopo un altro ptr++: punta a " << *ptr << endl;
    cout << endl;
    
    // Aritmetica dei puntatori con numeri
    ptr = numeri;  // Resetta all'inizio
    cout << "Resettato ptr all'inizio: punta a " << *ptr << endl;
    cout << endl;
    
    cout << "Aggiungere numeri al puntatore:" << endl;
    cout << "  ptr + 2 punta a: " << *(ptr + 2) << " (terzo elemento)" << endl;
    cout << "  ptr + 4 punta a: " << *(ptr + 4) << " (quinto elemento)" << endl;
    
    return 0;
}

```

### 3. Array di puntatori 

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "=== MANIPOLARE ARRAY CON PUNTATORI ===" << endl;
    
    int numeri[] = {1, 2, 3, 4, 5};
    int* ptr = numeri;  // ptr punta al primo elemento
    
    cout << "Stato iniziale:" << endl;
    cout << "  ptr punta a: " << *ptr << " (primo elemento)" << endl;
    cout << endl;
    
    // Muovere il puntatore avanti
    cout << "Muoversi attraverso l'array:" << endl;
    
    ptr++;  // Passa al prossimo intero (4 byte avanti)
    cout << "  Dopo ptr++: punta a " << *ptr << endl;
    
    ptr++;  // Muovi di nuovo
    cout << "  Dopo un altro ptr++: punta a " << *ptr << endl;
    cout << endl;
    
    // Aritmetica dei puntatori con numeri
    ptr = numeri;  // Resetta all'inizio
    cout << "Resettato ptr all'inizio: punta a " << *ptr << endl;
    cout << endl;
    
    cout << "Aggiungere numeri al puntatore:" << endl;
    cout << "  ptr + 2 punta a: " << *(ptr + 2) << " (terzo elemento)" << endl;
    cout << "  ptr + 4 punta a: " << *(ptr + 4) << " (quinto elemento)" << endl;
    
    return 0;
}
```

## Aritmentica dei puntatori

### 1. Operazioni aritmentiche di base

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "=== ARITMETICA DEI PUNTATORI: AGGIUNGERE 1 NON SIGNIFICA AGGIUNGERE 1 BYTE ===" << endl;
    
    int arr[] = {10, 20, 30, 40, 50};
    int* ptr = arr;
    
    cout << "Concetto chiave: L'aritmetica dei puntatori è consapevole del tipo!" << endl;
    cout << endl;
    
    cout << "Stato iniziale:" << endl;
    cout << "  ptr = " << ptr << " (indirizzo)" << endl;
    cout << "  *ptr = " << *ptr << " (valore a quell'indirizzo)" << endl;
    cout << endl;
    
    cout << "Quando facciamo ptr++:" << endl;
    cout << "  Non aggiunge semplicemente 1 all'indirizzo" << endl;
    cout << "  Aggiunge sizeof(int) bytes (di solito 4)" << endl;
    
    ptr++;
    cout << "\nDopo ptr++:" << endl;
    cout << "  ptr = " << ptr << " (indirizzo aumentato di " << sizeof(int) << ")" << endl;
    cout << "  *ptr = " << *ptr << " (ora punta all'elemento successivo)" << endl;
    
    return 0;
}

```

### 2. Sottrazione e confronto fra puntatori

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "=== SOTTRAZIONE E CONFRONTO TRA PUNTATORI ===" << endl;

    int arr[] = {10, 20, 30, 40, 50, 60, 70};
    int* inizio = &arr[0];  // Primo elemento
    int* fine = &arr[6];    // Ultimo elemento

    // Sottrazione tra puntatori
    cout << "Sottrazione tra puntatori:" << endl;
    cout << "  inizio punta a: " << *inizio << " (indice 0)" << endl;
    cout << "  fine punta a: " << *fine << " (indice 6)" << endl;
    cout << "  fine - inizio = " << (fine - inizio) << " (numero di elementi tra loro)" << endl;
    cout << "  NON " << ((long)fine - (long)inizio) << " bytes!" << endl;
    cout << endl;

    // Confronto tra puntatori
    cout << "Confronto tra puntatori:" << endl;
    cout << "  inizio < fine? " << (inizio < fine ? "Sì" : "No") << endl;

    return 0;
}
```

## Puntatori e Funzioni

### 1. Passaggio per riferimento

```cpp
#include <iostream>
using namespace std;

// Funzione che prova a modificare un valore (ma fallisce)
void incrementaMale(int x) {
    x++;  // Modifica la COPIA, non l'originale
    cout << "  Dentro incrementaMale, x ora è: " << x << endl;
}

// Funzione che modifica con successo il valore usando un puntatore
void incrementaBene(int* ptr) {
    (*ptr)++;  // Importante: (*ptr)++ NON *ptr++!
    cout << "  Dentro incrementaBene, *ptr ora è: " << *ptr << endl;
}

int main() {
    cout << "=== PASSAGGIO PER VALORE VS PASSAGGIO PER PUNTATORE ===" << endl;
    
    int num = 5;
    
    cout << "Num originale: " << num << endl;
    cout << endl;
    
    cout << "Chiamata incrementaMale(num):" << endl;
    incrementaMale(num);
    cout << "Dopo incrementaMale, num = " << num << " (invariato!)" << endl;
    cout << endl;
    
    cout << "Chiamata incrementaBene(&num):" << endl;
    incrementaBene(&num);  // Passa l'indirizzo
    cout << "Dopo incrementaBene, num = " << num << " (cambiato!)" << endl;
    
    return 0;
}
```

### 2. Funzioni a volori multipli

```cpp
#include <iostream>
using namespace std;

// Funzione che trova sia il minimo che il massimo in un array
void trovaMinMax(int* arr, int size, int* min, int* max) {
    *min = *max = arr[0];  // Inizializza con il primo elemento

    for(int i = 1; i < size; i++) {
        if(arr[i] < *min) *min = arr[i];
        if(arr[i] > *max) *max = arr[i];
    }
}

int main() {
    cout << "=== RESTITUIRE VALORI MULTIPLI ===" << endl;

    int numeri[] = {34, 12, 56, 78, 23, 45, 67};
    int size = sizeof(numeri) / sizeof(numeri[0]);

    cout << "Array: ";
    for(int i = 0; i < size; i++) cout << numeri[i] << " ";
    cout << endl;

    int minVal, maxVal;
    trovaMinMax(numeri, size, &minVal, &maxVal);

    cout << "Risultati: Min = " << minVal << ", Max = " << maxVal << endl;

    return 0;
}
```
### 3. Puntatore a puntatore

```cpp
#include <iostream>
using namespace std;

// Funzione che alloca memoria e modifica il puntatore stesso
void allocaArray(int** ptr, int size) {
    *ptr = new int[size];  // Questo cambia il puntatore originale!

    // Inizializza i valori
    for(int i = 0; i < size; i++) {
        (*ptr)[i] = (i + 1) * 10;
    }

    cout << "  Array allocato all'indirizzo: " << *ptr << endl;
}

int main() {
    cout << "=== DOPPI PUNTATORI: PUNTATORI A PUNTATORI ===" << endl;

    int* arrayPtr = nullptr;  // Il nostro puntatore che vogliamo modificare

    cout << "Prima dell'allocazione:" << endl;
    cout << "  arrayPtr = " << arrayPtr << " (nullo)" << endl;
    cout << endl;

    cout << "Chiamata allocaArray(&arrayPtr, 5):" << endl;
    allocaArray(&arrayPtr, 5);  // Passa l'indirizzo del nostro puntatore

    cout << "\nDopo l'allocazione:" << endl;
    cout << "  arrayPtr = " << arrayPtr << " (ora punta a memoria valida)" << endl;
    cout << "  Valori: ";
    for(int i = 0; i < 5; i++) {
        cout << arrayPtr[i] << " ";
    }
    cout << endl;

    // Pulizia
    delete[] arrayPtr;

    return 0;
}
```

## Allocazione dinamica della memoria

### 1. Operatori "new" e "delete"

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "=== ALLOCAZIONE DINAMICA DELLA MEMORIA: LO HEAP ===" << endl;

    cout << "Concetto chiave: Due tipi di memoria:" << endl;
    cout << "  Stack: Variabili locali (automatiche, dimensione limitata)" << endl;
    cout << "  Heap:  Allocate dinamicamente (manuali, possono essere grandi)" << endl;
    cout << endl;

    // Allocazione di una singola variabile
    cout << "1. Allocare un singolo intero:" << endl;
    int* ptr = new int;  // Richiede memoria dallo heap
    cout << "   new int restituisce indirizzo: " << ptr << endl;

    *ptr = 42;  // Memorizza il valore nella memoria dello heap
    cout << "   Memorizzato " << *ptr << " a quell'indirizzo" << endl;
    cout << endl;

    cout << "2. Bisogna fare delete quando si finisce:" << endl;
    delete ptr;  // Restituisce la memoria allo heap
    ptr = nullptr;
    cout << endl;

    // Allocazione di un array
    cout << "3. Allocare un array:" << endl;
    int size = 5;
    int* arr = new int[size];  // Alloca array sullo heap

    // Inizializza l'array
    for(int i = 0; i < size; i++) {
        arr[i] = (i + 1) * 10;
    }

    cout << "   Valori memorizzati: ";
    for(int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << endl;

    cout << "4. Cancellazione dell'array:" << endl;
    cout << "   Bisogna usare delete[] (con le parentesi!) per gli array" << endl;
    delete[] arr;  // Libera la memoria dell'array
    arr = nullptr;

    return 0;
}
```

## 2. Array 2D Dinamici

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "=== ARRAY 2D DINAMICI ===" << endl;
    
    int righe = 3, colonne = 4;
    
    cout << "Creazione di una matrice " << righe << "x" << colonne << ":" << endl;
    cout << endl;
    
    // Passo 1: Alloca array di puntatori (righe)
    cout << "Passo 1: Alloca i puntatori alle righe" << endl;
    int** matrice = new int*[righe];
    cout << endl;
    
    // Passo 2: Alloca ogni riga
    cout << "Passo 2: Alloca ogni riga" << endl;
    for(int i = 0; i < righe; i++) {
        matrice[i] = new int[colonne];
    }
    cout << endl;
    
    // Inizializza la matrice
    int valore = 1;
    for(int i = 0; i < righe; i++) {
        for(int j = 0; j < colonne; j++) {
            matrice[i][j] = valore++;
        }
    }
    
    // Stampa la matrice
    cout << "Matrice risultante:" << endl;
    for(int i = 0; i < righe; i++) {
        cout << "   Riga " << i << ": ";
        for(int j = 0; j < colonne; j++) {
            cout << matrice[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
    
    // Passo 4: Liberare la memoria (importante!)
    cout << "Passo 4: Liberare la memoria (in ordine inverso)" << endl;
    for(int i = 0; i < righe; i++) {
        delete[] matrice[i];  // Cancella ogni riga
    }
    delete[] matrice;  // Cancella l'array di puntatori
    
    return 0;
}

```

### 3. Dimostrazione Memory

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "\n=== DIMOSTRAZIONE DI MEMORY LEAK ===" << endl;

    cout << "Esempio 1: Dimenticare di fare delete" << endl;
    cout << "  int* ptr = new int(100);" << endl;
    cout << "  // ... del codice ..." << endl;
    cout << "  // Dimenticato: delete ptr;" << endl;
    cout << "  Risultato: La memoria rimane allocata fino alla fine del programma" << endl;

    cout << "\nEsempio 2: Perdere il puntatore" << endl;
    cout << "  int* ptr = new int(100);" << endl;
    cout << "  ptr = new int(200);  // Sovrascrive senza cancellare il primo!" << endl;
    cout << "  // La prima allocazione (100) è persa per sempre!" << endl;

    cout << "\nEsempio 3: Il puntatore esce dallo scope" << endl;
    cout << "  if(true) {" << endl;
    cout << "      int* ptr = new int(100);" << endl;
    cout << "  }  // ptr esce dallo scope, ma la memoria non è liberata!" << endl;
    cout << "  // Non c'è modo di accedere a quella memoria ora - LEAK!" << endl;

    return 0;
}
```

## Errori comuni e buone pratiche

### 1. Dangling pointers

```cpp

#include <iostream>
using namespace std;

int main() {
    cout << "=== PUNTATORI PENDENTI: PUNTARE A MEMORIA LIBERATA ===" << endl;
    
    int* ptr1 = new int(42);
    int* ptr2 = ptr1;  // Entrambi puntano alla stessa memoria
    
    cout << "Stato iniziale:" << endl;
    cout << "  ptr1 = " << ptr1 << " punta a " << *ptr1 << endl;
    cout << "  ptr2 = " << ptr2 << " punta a " << *ptr2 << endl;
    cout << endl;
    
    cout << "Dopo aver cancellato ptr1:" << endl;
    delete ptr1;
    ptr1 = nullptr;  // Buono: impostato a null
    cout << "  ptr1 = " << ptr1 << " (nullo, sicuro)" << endl;
    cout << "  ptr2 = " << ptr2 << " (ha ancora il vecchio indirizzo!)" << endl;
    cout << "  ptr2 è ora PENDENTE - punta a memoria liberata!" << endl;
    
    // Soluzione
    cout << "\nSoluzione: Imposta TUTTI i puntatori a null dopo delete:" << endl;
    ptr2 = nullptr;
    cout << "  Ora entrambi sono null: ptr1=" << ptr1 << ", ptr2=" << ptr2 << endl;
    
    return 0;
}
```

### 2. Memory leak
```cpp
#include <iostream>
using namespace std;

// Semplice rilevatore di leak (per scopi didattici)
class RilevatoreLeak {
private:
    static int conteggioAllocazioni;
    static int conteggioDeallocazioni;
    
public:
    static void* alloca(size_t size, const char* file, int linea) {
        void* ptr = malloc(size);
        conteggioAllocazioni++;
        cout << "  [+] Allocati " << size << " bytes a " << ptr << endl;
        cout << "      in " << file << ":" << linea << endl;
        return ptr;
    }
    
    static void dealloca(void* ptr, const char* file, int linea) {
        if(ptr) {
            conteggioDeallocazioni++;
            cout << "  [-] Liberata memoria a " << ptr << endl;
            cout << "      in " << file << ":" << linea << endl;
            free(ptr);
        }
    }
    
    static void report() {
        cout << "\n=== REPORT LEAK ===" << endl;
        cout << "  Allocazioni: " << conteggioAllocazioni << endl;
        cout << "  Deallocazioni: " << conteggioDeallocazioni << endl;
        if(conteggioAllocazioni > conteggioDeallocazioni) {
            cout << "  ATTENZIONE: " << (conteggioAllocazioni - conteggioDeallocazioni) 
                 << " memory leak rilevati!" << endl;
        } else {
            cout << "  ✓ Nessun leak rilevato" << endl;
        }
    }
};

int RilevatoreLeak::conteggioAllocazioni = 0;
int RilevatoreLeak::conteggioDeallocazioni = 0;

// Macro per tracciare le allocazioni
#define NEW new(__FILE__, __LINE__)
#define DELETE delete(__FILE__, __LINE__)

// Overload di new e delete con tracciamento
void* operator new(size_t size, const char* file, int linea) {
    return RilevatoreLeak::alloca(size, file, linea);
}

void operator delete(void* ptr, const char* file, int linea) {
    RilevatoreLeak::dealloca(ptr, file, linea);
}

void operator delete(void* ptr) noexcept {
    RilevatoreLeak::dealloca(ptr, "unknown", 0);
}

int main() {
    cout << "=== RILEVAMENTO MEMORY LEAK ===" << endl;
    
    // Buono: new/delete corrispondenti
    cout << "\nEsempio corretto - pulizia appropriata:" << endl;
    int* p1 = NEW int(42);
    DELETE p1;
    
    // Cattivo: memory leak
    cout << "\nEsempio errato - dimenticare di fare delete:" << endl;
    int* p2 = NEW int(100);
    // Dimenticato di fare delete p2!
    
    RilevatoreLeak::report();
    
    return 0;
}
```

### 3. Pattern di uso sicuro dei puntatori

```cpp
#include <iostream>
#include <memory>  // Per smart pointers
using namespace std;

int main() {
    cout << "=== PATTERN DI PUNTATORI SICURI ===" << endl;

    // Pattern 1: Inizializza sempre
    cout << "Pattern 1: Inizializza sempre i puntatori" << endl;
    int* ptr1 = nullptr;  // Buono
    cout << "  ptr1 = " << ptr1 << " (sicuro da controllare)" << endl;
    cout << endl;

    // Pattern 2: Controlla prima di usare
    cout << "Pattern 2: Controlla se è nullo prima di dereferenziare" << endl;
    if(ptr1 != nullptr) {
        cout << "  *ptr1 = " << *ptr1 << endl;
    } else {
        cout << "  ptr1 è nullo, salto la dereferenziazione" << endl;
    }
    cout << endl;

    // Pattern 3: Imposta a null dopo delete
    cout << "Pattern 3: Imposta a null dopo delete" << endl;
    int* ptr3 = new int(42);
    cout << "  ptr3 = " << ptr3 << " punta a " << *ptr3 << endl;
    delete ptr3;
    ptr3 = nullptr;  // Importante!
    cout << "  Dopo delete e impostazione a null: " << ptr3 << endl;
    cout << endl;

    // Pattern 4: Usa smart pointers (C++ moderno)
    cout << "Pattern 4: Usa smart pointers (C++11+)" << endl;
    cout << "  Gli smart pointer cancellano automaticamente quando escono dallo scope" << endl;

    {
        unique_ptr<int> smartPtr = make_unique<int>(100);
        cout << "  Dentro il blocco, smartPtr punta a " << *smartPtr << endl;
        // Non serve fare delete - gestito automaticamente
    }
    cout << "  Fuori dal blocco, la memoria è automaticamente liberata" << endl;

    return 0;
}
```

## Cheat sheet

CHEAT SHEET DEI PUNTATORI - CON SPIEGAZIONI

DICHIARAZIONE:
    int* ptr;           // Puntatore a int - memorizza l'indirizzo di un int
    int** ptr2;         // Puntatore a puntatore - memorizza l'indirizzo di un int*

    PERCHÉ: Il tipo dice al compilatore come interpretare la memoria a quell'indirizzo

OPERATORI:
    &x                  // Operatore "indirizzo di" - ottiene l'indirizzo di memoria di x
    *ptr                // Operatore "dereferenziazione" - ottiene il valore all'indirizzo di ptr

    int x = 5;
    int* p = &x;        // p memorizza DOVE vive x
    int y = *p;         // y ottiene COSA c'è all'indirizzo p (5)

ARITMETICA DEI PUNTATORI:
    ptr++               // Passa all'elemento successivo (aggiunge sizeof(tipo) bytes)
    ptr + n             // Avanza di n elementi
    ptr1 - ptr2         // Numero di elementi tra i puntatori

    int arr[5] = {10,20,30,40,50};
    int* p = arr;       // p punta a 10
    p += 2;             // p ora punta a 30 (spostato di 2 * sizeof(int) bytes)

MEMORIA DINAMICA:
    new int             // Alloca un singolo int sullo heap, restituisce l'indirizzo
    new int[10]         // Alloca un array di 10 int sullo heap
    delete ptr          // Libera una singola allocazione
    delete[] ptr        // Libera un array

    PERCHÉ HEAP? Dimensione sconosciuta in compilazione, deve sopravvivere al ritorno della funzione

ERRORI COMUNI:

    1. Puntatore non inizializzato:
       int* p;           // p contiene un indirizzo casuale
       *p = 5;           // CRASH! Scrive in memoria casuale

    2. Dereferenziare nullo:
       int* p = nullptr;
       *p = 5;           // CRASH! Non si può scrivere all'indirizzo 0

    3. Memory leak:
       int* p = new int(5);
       p = new int(10);  // Prima allocazione persa per sempre!

    4. Puntatore pendente:
       int* p = new int(5);
       int* q = p;
       delete p;         // Memoria liberata
       *q = 10;          // COMPORTAMENTO INDEFINITO! q punta a memoria liberata

BUONE PRATICHE:

    1. Inizializza sempre i puntatori
       int* p = nullptr;  // Se non usato subito, mettilo a null

    2. Controlla se è nullo prima di dereferenziare
       if(p != nullptr) { *p = 5; }

    3. Imposta a null dopo delete
       delete p;
       p = nullptr;

    4. Abbina new con delete, new[] con delete[]
       int* p = new int;    // Usa delete p
       int* arr = new int[5]; // Usa delete[] arr

    5. Usa smart pointers in C++ moderno
       unique_ptr<int> p = make_unique<int>(5);
