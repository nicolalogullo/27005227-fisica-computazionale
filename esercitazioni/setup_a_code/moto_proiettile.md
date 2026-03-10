# Esercizio di Programmazione C++: Simulazione del Moto del Proiettile

> **Obiettivi di Apprendimento**
> Al termine di questa sessione sarete in grado di:
> - Organizzare un programma C++ usando le **funzioni**
> - **Leggere parametri di input** da un file formattato
> - **Scrivere output** su più file con nomi diversi usando `sprintf`
> - **Controllare il flusso della simulazione** e fermarla al raggiungimento di una condizione fisica

---

## Richiami di Fisica

Un proiettile lanciato con velocità iniziale $v_0$ e angolo $\theta$ rispetto all'orizzontale è soggetto a un'accelerazione gravitazionale costante $g$ verso il basso. Trascurando la resistenza dell'aria, le **equazioni del moto analitiche** sono:

```
x(t)  =  v0 * cos(θ) * t
y(t)  =  v0 * sin(θ) * t  -  0.5 * g * t²

vx(t) =  v0 * cos(θ)           (costante)
vy(t) =  v0 * sin(θ)  -  g * t
```

**Non** risolveremo un'equazione differenziale in modo numerico — valuteremo invece queste formule a passi di tempo discreti `t = 0, dt, 2*dt, ...` e registreremo la traiettoria.

---

## Passo 1 — Un Programma Minimo Funzionante

Prima di aggiungere qualsiasi funzionalità, assicuratevi di saper compilare ed eseguire un semplice file C++.

```cpp
// step1.cpp  –  Ciao, Proiettile!
#include <iostream>
#include <cmath>

int main() {
    double v0    = 20.0;   // velocità iniziale  [m/s]
    double theta = 45.0;   // angolo di lancio   [gradi]
    double g     = 9.81;   // gravità            [m/s²]
    double dt    = 0.01;   // passo temporale    [s]

    // Conversione dell'angolo in radianti
    double theta_rad = theta * M_PI / 180.0;

    double t  = 0.0;
    double x  = v0 * cos(theta_rad) * t;
    double y  = v0 * sin(theta_rad) * t - 0.5 * g * t * t;

    std::cout << "At t = " << t << " s : "
              << "x = " << x << " m, "
              << "y = " << y << " m" << std::endl;

    return 0;
}
```

**Compilazione ed esecuzione:**
```bash
g++ -o step1 step1.cpp -lm
./step1
```

**✏️ Esercizio 1.1** Cambiate `theta` a 30° e 60°. Cosa vi aspettate per `x` e `y` a `t = 0`? L'output corrisponde alle aspettative?

---

## Passo 2 — Aggiungere un Ciclo Temporale

Iteriamo ora nel tempo e stampiamo la traiettoria sul terminale.

```cpp
// step2.cpp  –  Ciclo temporale
#include <iostream>
#include <cmath>

int main() {
    double v0    = 20.0;
    double theta = 45.0;
    double g     = 9.81;
    double dt    = 0.01;

    double theta_rad = theta * M_PI / 180.0;

    // Stampa intestazione
    std::cout << "t[s]    x[m]    y[m]" << std::endl;

    for (int i = 0; i <= 500; i++) {
        double t = i * dt;
        double x = v0 * cos(theta_rad) * t;
        double y = v0 * sin(theta_rad) * t - 0.5 * g * t * t;

        std::cout << t << "    " << x << "    " << y << std::endl;
    }

    return 0;
}
```

**✏️ Esercizio 2.1** Il ciclo viene eseguito per un numero fisso di 500 passi. Eseguite il programma e osservate che `y` diventa negativo — il proiettile è andato sottoterra! Risolveremo questo problema al Passo 4.

**✏️ Esercizio 2.2** Aggiungete le colonne per `vx` e `vy` all'output.

---

## Passo 3 — Introduzione alle Funzioni

I buoni programmi separano le **responsabilità** in funzioni. Creeremo una funzione per calcolare la posizione e una per la velocità.

```cpp
// step3.cpp  –  Uso delle funzioni
#include <iostream>
#include <cmath>

// ---- Dichiarazioni delle funzioni ----------------------------------------

/** Restituisce la posizione x al tempo t */
double positionX(double v0, double theta_rad, double t) {
    return v0 * cos(theta_rad) * t;
}

/** Restituisce la posizione y al tempo t */
double positionY(double v0, double theta_rad, double g, double t) {
    return v0 * sin(theta_rad) * t - 0.5 * g * t * t;
}

/** Restituisce la velocità y al tempo t */
double velocityY(double v0, double theta_rad, double g, double t) {
    return v0 * sin(theta_rad) - g * t;
}

/** Restituisce la velocità scalare totale al tempo t */
double speed(double v0, double theta_rad, double g, double t) {
    double vx = v0 * cos(theta_rad);
    double vy = velocityY(v0, theta_rad, g, t);
    return sqrt(vx * vx + vy * vy);
}

// ---- Main ---------------------------------------------------------

int main() {
    double v0    = 20.0;
    double theta = 45.0;
    double g     = 9.81;
    double dt    = 0.01;

    double theta_rad = theta * M_PI / 180.0;

    std::cout << "t[s]    x[m]    y[m]    speed[m/s]" << std::endl;

    for (int i = 0; i <= 500; i++) {
        double t = i * dt;
        double x = positionX(v0, theta_rad, t);
        double y = positionY(v0, theta_rad, g, t);
        double s = speed(v0, theta_rad, g, t);

        std::cout << t << "    " << x << "    " << y << "    " << s << std::endl;
    }

    return 0;
}
```

**✏️ Esercizio 3.1** Scrivete una funzione `maxHeight(v0, theta_rad, g)` che calcoli e restituisca **analiticamente** l'altezza massima. Chiamatela dal `main` e stampate il risultato prima del ciclo. Formula: $H = \frac{v_0^2 \sin^2\theta}{2g}$

**✏️ Esercizio 3.2** Scrivete una funzione `rangeAnalytical(v0, theta_rad, g)` che restituisca la gittata analitica $R = \frac{v_0^2 \sin 2\theta}{g}$.

---

## Passo 4 — Fermare la Simulazione all'Atterraggio

Invece di eseguire un numero fisso di passi, **fermiamo la simulazione quando il proiettile tocca terra** (`y` torna a 0 dopo essere partito da esso).

```cpp
// step4.cpp  –  Stop all'atterraggio
#include <iostream>
#include <cmath>

double positionX(double v0, double theta_rad, double t) {
    return v0 * cos(theta_rad) * t;
}

double positionY(double v0, double theta_rad, double g, double t) {
    return v0 * sin(theta_rad) * t - 0.5 * g * t * t;
}

int main() {
    double v0    = 20.0;
    double theta = 45.0;
    double g     = 9.81;
    double dt    = 0.01;

    double theta_rad = theta * M_PI / 180.0;

    std::cout << "t[s]    x[m]    y[m]" << std::endl;

    int i = 0;
    while (true) {
        double t = i * dt;
        double x = positionX(v0, theta_rad, t);
        double y = positionY(v0, theta_rad, g, t);

        std::cout << t << "    " << x << "    " << y << std::endl;

        // --- CONDIZIONE DI ARRESTO ---
        // Dopo il primo passo, ci si ferma quando y scende a zero o sotto
        if (i > 0 && y <= 0.0) {
            std::cout << "# Projectile landed at x = " << x << " m" << std::endl;
            break;
        }

        i++;
    }

    return 0;
}
```

**✏️ Esercizio 4.1** La posizione x di atterraggio trovata dal ciclo differirà leggermente dalla gittata analitica a causa del passo temporale finito. Calcolate entrambe e stampate l'**errore relativo** in percentuale. Come cambia dimezzando `dt`?

**✏️ Esercizio 4.2** Aggiungete una seconda condizione di arresto: fermate la simulazione se la **velocità scende sotto i 5 m/s** in qualsiasi momento durante il volo. Ragionate se questo possa mai accadere in assenza di resistenza dell'aria.

---

## Passo 5 — Lettura dell'Input da File

Inserire i parametri direttamente nel codice è una cattiva pratica. Li leggeremo da un **file di input** in formato testo.

### 5a — Creare il file di input

Salvate questo contenuto come `input.txt`:

```
# File di input per il moto del proiettile
# Le righe che iniziano con '#' sono commenti (verranno ignorati nel codice)
v0       20.0      # velocità iniziale [m/s]
theta    45.0      # angolo di lancio  [gradi]
g        9.81      # gravità           [m/s^2]
dt       0.01      # passo temporale   [s]
```

### 5b — Leggere il file in C++

```cpp
// step5.cpp  –  Lettura dell'input da file
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

// Lettore di input: cerca una parola chiave e ne restituisce il valore
double readParam(const std::string& filename, const std::string& keyword) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "ERRORE: impossibile aprire " << filename << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(file, line)) {
        // Salta le righe di commento
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        std::string key;
        double value;
        iss >> key >> value;

        if (key == keyword) {
            return value;
        }
    }

    std::cerr << "ERRORE: parola chiave '" << keyword << "' non trovata in " << filename << std::endl;
    exit(1);
}

double positionX(double v0, double theta_rad, double t) {
    return v0 * cos(theta_rad) * t;
}

double positionY(double v0, double theta_rad, double g, double t) {
    return v0 * sin(theta_rad) * t - 0.5 * g * t * t;
}

int main() {
    // Legge tutti i parametri dal file
    double v0    = readParam("input.txt", "v0");
    double theta = readParam("input.txt", "theta");
    double g     = readParam("input.txt", "g");
    double dt    = readParam("input.txt", "dt");

    std::cout << "Caricati: v0=" << v0 << " theta=" << theta
              << " g=" << g << " dt=" << dt << std::endl;

    double theta_rad = theta * M_PI / 180.0;

    int i = 0;
    while (true) {
        double t = i * dt;
        double x = positionX(v0, theta_rad, t);
        double y = positionY(v0, theta_rad, g, t);

        std::cout << t << "    " << x << "    " << y << std::endl;

        if (i > 0 && y <= 0.0) break;
        i++;
    }

    return 0;
}
```

**✏️ Esercizio 5.1** Aggiungete un nuovo parametro `y0` (altezza iniziale dal suolo) in `input.txt` e modificate la funzione `positionY` per tenerlo in conto. Aggiornate di conseguenza la condizione di arresto.

**✏️ Esercizio 5.2** Cosa succede se scrivete male una parola chiave in `input.txt`? Provatelo. Poi migliorare il messaggio di errore per renderlo più informativo.

---

## Passo 6 — Scrittura dell'Output su File Nominati con `sprintf`

Invece di stampare sul terminale, scriveremo ciascuna grandezza fisica sul proprio **file separato**, con un nome che codifica la variabile e i parametri utilizzati.

```cpp
// step6.cpp  –  Scrittura su file con nomi generati da sprintf
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>    // per sprintf
#include <cmath>

double readParam(const std::string& filename, const std::string& keyword) {
    std::ifstream file(filename);
    if (!file.is_open()) { std::cerr << "Impossibile aprire " << filename << std::endl; exit(1); }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream iss(line);
        std::string key; double val;
        iss >> key >> val;
        if (key == keyword) return val;
    }
    std::cerr << "Parola chiave non trovata: " << keyword << std::endl; exit(1);
}

double positionX(double v0, double theta_rad, double t) {
    return v0 * cos(theta_rad) * t;
}
double positionY(double v0, double theta_rad, double g, double t) {
    return v0 * sin(theta_rad) * t - 0.5 * g * t * t;
}
double velocityY(double v0, double theta_rad, double g, double t) {
    return v0 * sin(theta_rad) - g * t;
}

int main() {
    double v0    = readParam("input.txt", "v0");
    double theta = readParam("input.txt", "theta");
    double g     = readParam("input.txt", "g");
    double dt    = readParam("input.txt", "dt");

    double theta_rad = theta * M_PI / 180.0;

    // --- Costruisce i nomi dei file di output con sprintf ---
    char fname_xy[100], fname_vy[100], fname_energy[100];

    sprintf(fname_xy,     "trajectory_v0%.0f_th%.0f.dat", v0, theta);
    sprintf(fname_vy,     "vy_v0%.0f_th%.0f.dat",         v0, theta);
    sprintf(fname_energy, "energy_v0%.0f_th%.0f.dat",     v0, theta);

    std::cout << "Scrittura su: " << fname_xy << ", "
              << fname_vy << ", " << fname_energy << std::endl;

    // Apertura dei tre file
    std::ofstream file_xy(fname_xy);
    std::ofstream file_vy(fname_vy);
    std::ofstream file_energy(fname_energy);

    // Intestazioni
    file_xy     << "# t[s]   x[m]   y[m]"          << std::endl;
    file_vy     << "# t[s]   vy[m/s]"               << std::endl;
    file_energy << "# t[s]   KE[J]   PE[J]   E[J]"  << std::endl;

    double mass = 1.0;  // massa assunta 1 kg per il calcolo dell'energia

    int i = 0;
    while (true) {
        double t  = i * dt;
        double x  = positionX(v0, theta_rad, t);
        double y  = positionY(v0, theta_rad, g, t);
        double vx = v0 * cos(theta_rad);
        double vy = velocityY(v0, theta_rad, g, t);

        double KE = 0.5 * mass * (vx*vx + vy*vy);
        double PE = mass * g * y;
        double E  = KE + PE;

        file_xy     << t << "   " << x << "   " << y  << std::endl;
        file_vy     << t << "   " << vy                << std::endl;
        file_energy << t << "   " << KE << "   " << PE << "   " << E << std::endl;

        if (i > 0 && y <= 0.0) break;
        i++;
    }

    file_xy.close();
    file_vy.close();
    file_energy.close();

    std::cout << "Fatto." << std::endl;
    return 0;
}
```

**✏️ Esercizio 6.1** Eseguite il programma con `theta = 30`, poi con `theta = 60`. Dovreste ottenere **sei file distinti**. Apriteli e verificate il file dell'energia — l'energia meccanica totale `E` deve essere **costante** durante l'intero volo (conservazione dell'energia). Lo è? Perché potrebbe non esserlo perfettamente?

**✏️ Esercizio 6.2** Aggiungete un quarto file di output `vx_v0...dat` per la componente orizzontale della velocità. In assenza di resistenza dell'aria, cosa vi aspettate di trovare?

**✏️ Esercizio 6.3** Modificate `sprintf` per includere `dt` nel nome del file con due cifre decimali (es. `trajectory_v0_20_th45_dt0.01.dat`). Quale specificatore di formato usereste?

---

## Passo 7 — Mettere Tutto Insieme

Ecco la **versione finale e completa** della simulazione, che riunisce tutte le funzionalità:

```cpp
// projectile.cpp  –  Simulazione completa
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <cmath>

// ================================================================
//  Lettore di input
// ================================================================
double readParam(const std::string& filename, const std::string& keyword) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "ERRORE: impossibile aprire '" << filename << "'" << std::endl;
        exit(1);
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream iss(line);
        std::string key; double val;
        iss >> key >> val;
        if (key == keyword) return val;
    }
    std::cerr << "ERRORE: parola chiave '" << keyword << "' non trovata." << std::endl;
    exit(1);
}

// ================================================================
//  Funzioni fisiche
// ================================================================
double positionX(double v0, double theta_rad, double t) {
    return v0 * cos(theta_rad) * t;
}

double positionY(double v0, double theta_rad, double g, double t, double y0 = 0.0) {
    return y0 + v0 * sin(theta_rad) * t - 0.5 * g * t * t;
}

double velocityX(double v0, double theta_rad) {
    return v0 * cos(theta_rad);
}

double velocityY(double v0, double theta_rad, double g, double t) {
    return v0 * sin(theta_rad) - g * t;
}

double kineticEnergy(double mass, double vx, double vy) {
    return 0.5 * mass * (vx * vx + vy * vy);
}

double potentialEnergy(double mass, double g, double y) {
    return mass * g * y;
}

double rangeAnalytical(double v0, double theta_rad, double g) {
    return v0 * v0 * sin(2.0 * theta_rad) / g;
}

// ================================================================
//  Main
// ================================================================
int main() {
    // --- Lettura dei parametri ---
    double v0    = readParam("input.txt", "v0");
    double theta = readParam("input.txt", "theta");
    double g     = readParam("input.txt", "g");
    double dt    = readParam("input.txt", "dt");
    double mass  = readParam("input.txt", "mass");
    double y0    = readParam("input.txt", "y0");

    double theta_rad = theta * M_PI / 180.0;

    std::cout << "=== Simulazione del Moto del Proiettile ===" << std::endl;
    std::cout << "v0=" << v0 << " m/s  theta=" << theta << " deg  g=" << g
              << " m/s2  dt=" << dt << " s  y0=" << y0 << " m" << std::endl;
    std::cout << "Gittata analitica (y0=0): " << rangeAnalytical(v0, theta_rad, g) << " m" << std::endl;

    // --- Apertura dei file di output ---
    char fname_traj[128], fname_vel[128], fname_en[128];
    sprintf(fname_traj, "traj_v0%.0f_th%.0f_dt%.3f.dat",   v0, theta, dt);
    sprintf(fname_vel,  "vel_v0%.0f_th%.0f_dt%.3f.dat",    v0, theta, dt);
    sprintf(fname_en,   "energy_v0%.0f_th%.0f_dt%.3f.dat", v0, theta, dt);

    std::ofstream f_traj(fname_traj);
    std::ofstream f_vel(fname_vel);
    std::ofstream f_en(fname_en);

    f_traj << "# t[s]   x[m]   y[m]"                     << std::endl;
    f_vel  << "# t[s]   vx[m/s]   vy[m/s]   speed[m/s]"  << std::endl;
    f_en   << "# t[s]   KE[J]   PE[J]   E_total[J]"       << std::endl;

    // --- Ciclo di integrazione temporale ---
    int    i      = 0;
    double x_land = 0.0;
    double t_land = 0.0;

    while (true) {
        double t  = i * dt;
        double x  = positionX(v0, theta_rad, t);
        double y  = positionY(v0, theta_rad, g, t, y0);
        double vx = velocityX(v0, theta_rad);
        double vy = velocityY(v0, theta_rad, g, t);
        double sp = sqrt(vx*vx + vy*vy);
        double KE = kineticEnergy(mass, vx, vy);
        double PE = potentialEnergy(mass, g, y);

        f_traj << t << "   " << x  << "   " << y          << std::endl;
        f_vel  << t << "   " << vx << "   " << vy << "   " << sp << std::endl;
        f_en   << t << "   " << KE << "   " << PE << "   " << KE + PE << std::endl;

        // Condizione di arresto: il proiettile torna al livello del suolo
        if (i > 0 && y <= 0.0) {
            x_land = x;
            t_land = t;
            break;
        }
        i++;
    }

    f_traj.close(); f_vel.close(); f_en.close();

    double range_an  = rangeAnalytical(v0, theta_rad, g);
    double rel_error = std::abs(x_land - range_an) / range_an * 100.0;

    std::cout << "Atterraggio numerico x  = " << x_land  << " m  a t = " << t_land << " s" << std::endl;
    std::cout << "Gittata analitica       = " << range_an << " m" << std::endl;
    std::cout << "Errore relativo         = " << rel_error << " %" << std::endl;
    std::cout << "Output scritto su: "
              << fname_traj << ", " << fname_vel << ", " << fname_en << std::endl;

    return 0;
}
```

**File `input.txt` aggiornato:**
```
# File di input per il moto del proiettile
v0       20.0
theta    45.0
g        9.81
dt       0.01
mass     1.0
y0       0.0
```

**Compilazione ed esecuzione:**
```bash
g++ -o projectile projectile.cpp -lm
./projectile
```

---

## Riepilogo

| Funzionalità | Introdotta al |
|---|---|
| Funzioni | Passo 3 |
| Lettura da file con `ifstream` | Passo 5 |
| Condizioni di arresto / `while(true)` + `break` | Passo 4 |
| File di output con `ofstream` | Passo 6 |
| Nomi di file dinamici con `sprintf` | Passo 6 |
| Confronto analitico vs. numerico | Passo 4 / Passo 7 |

---

---

# Esercizi Avanzati per Studenti con Inclinazione Numerica e Informatica

---

## Esercizio Avanzato A — Resistenza dell'Aria (Attrito Lineare)

Aggiungete una **forza di attrito lineare** $\mathbf{F}_\text{drag} = -b\,\mathbf{v}$. La soluzione analitica diventa:

```
vx(t) = vx0 * exp(-b/m * t)
vy(t) = (vy0 + m*g/b) * exp(-b/m * t)  -  m*g/b

x(t)  = (m/b) * vx0 * (1 - exp(-b/m * t))
y(t)  = (m/b) * (vy0 + m*g/b) * (1 - exp(-b/m * t))  -  (m*g/b) * t
```

**Compito:**
1. Aggiungete il parametro `b` (coefficiente di attrito) a `input.txt`.
2. Scrivete le nuove funzioni `posX_drag`, `posY_drag`, `velX_drag`, `velY_drag` che implementano le formule precedenti.
3. Nella stessa esecuzione, scrivete file di output sia per il caso **senza attrito** che **con attrito**, usando `sprintf` per codificare `b` nel nome del file.
4. Tracciate entrambe le traiettorie e calcolate la **riduzione percentuale della gittata** causata dall'attrito.
5. Trovate numericamente il valore di `b` per cui la gittata si riduce esattamente del 50% (suggerimento: usate un ciclo sui valori di `b`).

---

## Esercizio Avanzato B — Angolo di Lancio Ottimale

Senza attrito la gittata massima si ottiene per θ = 45°. Con l'attrito questo non è più vero.

**Compito:**
1. Scrivete una funzione `computeRange(v0, theta, g, b, m, dt)` che esegua la simulazione completa e restituisca la posizione x di atterraggio.
2. Fate variare `theta` da 1° a 89° con passi di 1° e calcolate la gittata per ogni angolo, sia con `b = 0` che con un valore non nullo di `b`.
3. Scrivete i risultati in un file `range_vs_angle_b<valore>.dat`.
4. Trovate l'**angolo ottimale** nel caso con attrito e confrontatelo con 45°.
5. **Sfida:** Usate un semplice algoritmo di **ricerca per sezione aurea** o **ricerca ternaria** per trovare l'angolo ottimale con 4 cifre significative, senza iterare su ogni grado.

---

## Esercizio Avanzato C — Analisi della Convergenza

La condizione di arresto `y <= 0` introduce un **errore di discretizzazione** perché si supera di un passo temporale il punto esatto di atterraggio.

**Compito:**
1. Eseguite la simulazione per `dt = 0.1, 0.05, 0.01, 0.005, 0.001, 0.0005`.
2. Per ciascun `dt`, registrate la posizione di atterraggio numerica $x_\text{num}$ e confrontatela con la gittata analitica $R$.
3. Calcolate $\varepsilon(dt) = |x_\text{num}(dt) - R|$.
4. Scrivete tutti i risultati in un unico file `convergence.dat` con colonne `dt   x_num   error`.
5. Su assi log–log (potete usare gnuplot o Python/matplotlib), tracciate $\varepsilon$ in funzione di $dt$. Qual è l'**ordine di convergenza**? Spiegatelo.
6. **Sfida:** Implementate l'**interpolazione lineare** per trovare con precisione l'istante in cui $y = 0$, e confrontate l'ordine di convergenza con il caso senza interpolazione.

---

## Esercizio Avanzato D — Più Proiettili da un File Batch

**Compito:**
1. Create un file `batch.txt` con una configurazione di lancio per riga:
   ```
   # v0   theta   etichetta
   20.0   30.0   basso
   20.0   45.0   ottimale
   20.0   60.0   alto
   30.0   45.0   veloce
   ```
2. Scrivete un programma C++ che legga questo file **riga per riga**, esegua la simulazione completa per ciascuna configurazione e scriva la traiettoria in un file chiamato `traj_<etichetta>.dat`.
3. Al termine dell'elaborazione, scrivete un file riassuntivo `summary.dat` con le colonne:
   `etichetta   v0   theta   gittata_numerica   gittata_analitica   errore_percentuale`
4. **Sfida:** Ordinate i risultati del riepilogo per gittata (dal più grande al più piccolo) senza usare `std::sort` — implementate il vostro **insertion sort** su un array di struct.

---

## Esercizio Avanzato E — Diagnostica della Conservazione dell'Energia

Nel caso senza attrito, l'energia meccanica totale $E = KE + PE$ deve essere **esattamente costante** durante l'intero volo (poiché usiamo la soluzione analitica e non un integratore numerico).

**Compito:**
1. Calcolate $E(t)$ lungo la traiettoria e registrate sia $E(t)$ che la **deviazione relativa** $\delta E(t) = |E(t) - E(0)| / E(0)$.
2. Spiegate analiticamente perché $\delta E$ potrebbe non essere esattamente zero nell'aritmetica in virgola mobile. Qual è l'ordine di grandezza atteso delle deviazioni?
3. Introducete ora un **errore deliberato**: sostituite il $y(t)$ analitico con uno step di integrazione numerica di Eulero in avanti:
   ```
   y_{i+1}  = y_i  + vy_i * dt
   vy_{i+1} = vy_i - g * dt
   ```
   e ripetete l'analisi dell'energia. Come scala la deriva energetica con `dt`?
4. **Sfida:** Implementate l'**integratore di Störmer–Verlet (leapfrog)** per il moto verticale e confrontate la sua conservazione dell'energia con quella di Eulero. Quale conserva meglio l'energia e perché?

---

## Esercizio Avanzato F — Proiettile 3D con Vento

Estendete la simulazione a **tre dimensioni** aggiungendo una componente di vento trasversale.

**Compito:**
1. Introducete un vettore velocità del vento $(w_x, w_y, w_z)$ letto dal file di input.
2. Con attrito lineare, le equazioni diventano:
   ```
   ax = -b/m * (vx - wx)
   ay = -b/m * (vy - wy)
   az = -g   - b/m * (vz - wz)
   ```
   Hanno ancora soluzione analitica (ogni asse è disaccoppiato dagli altri). Derivate e implementate la soluzione.
3. Scrivete file di output separati per le proiezioni `x-z`, `y-z` e `x-y` della traiettoria.
4. Usate `sprintf` per codificare tutti e sei i parametri `(v0, theta, phi, b, wx, wz)` nel nome del file.
5. **Sfida:** Trovate l'angolo azimutale iniziale $\phi$ (direzione orizzontale) che **massimizza la distanza percorsa** in presenza di un vento trasversale noto, tramite un ciclo di ottimizzazione numerica.

---

*Buona fortuna, e ricordate: un programma che compila e gira è solo l'inizio — verificate sempre la fisica!*
