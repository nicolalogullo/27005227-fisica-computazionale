import numpy as np
import matplotlib.pyplot as plt

def disegna_vettore(punta, coda, color='blue'):
    '''
    disegna un vettore 2D date le coordinate cartesiane della punta e della coda
    DA MIGLIORARE: a volte il plot è vuoto
    '''
    plt.quiver(coda[0], coda[1], punta[0], punta[1], angles='xy', scale_units='xy', scale=1, color=color, width=0.005)
    plt.grid(alpha=.5, ls='--')
    # Per impostare correttamente i limiti del grafico
    plt.plot(punta[0], punta[1], alpha=0)
    plt.plot(coda[0], coda[1], alpha=0)
    return


def sommaNvettori(listavettori):
    '''
    restituisce la somma di una lista di vettori
    '''
    N = len(listavettori)
    i=0
    somma=0
    while i < N:
        somma += listavettori[i]
        i +=1 

    return somma


def da_polari_a_cartesiane(modulo, angolo):     # l'angolo è espresso in gradi
    '''
    date le coordinate polari, restituisce l'array delle coordinate cartesiane corrispondenti
    '''
    angolo = angolo * np.pi / 180               # per trasformare da gradi in radianti       
    vx = modulo * np.cos(angolo)
    vy = modulo * np.sin(angolo)
    return np.array([vx, vy])


def da_cartesiane_a_polari(v):
    '''
    dato un array 2D, restituisce rispettivamente il modulo e l'angolo (compreso tra -pi/2 e 3pi/2)
    DA MIGLIORARE: restituire un angolo nell'intervallo [-pi,pi) oppure [0,2pi)
    '''        
    vx = v[0]
    vy = v[1]
    v_modulo = np.sqrt(np.sum(v**2))
    if vx > 0:
        v_angolo = np.arctan(vy/vx) * 180 / np.pi   # numpy dà sempre il risultato in radianti! Dobbiamo convertire in gradi
    elif vx < 0:
        v_angolo = np.arctan(vy/vx) * 180 / np.pi + 180
    # dobbiamo trattare separatamente i due casi in cui vx è uguale a zero!
    elif vx == 0:
        if vy > 0:
            return v_modulo, 90
        elif vy < 0:
            return v_modulo, 270
    # l'unico caso rimasto è il vettore nullo (0,0), per cui le coordinate polari non sono ben definite
    else:
        print('Attenzione: per il vettore nullo (modulo = 0) l\'angolo non è ben definito.')
        return
    
    return v_modulo, v_angolo


def algoritmo_bisezione(f, x1, x2, risoluzione=0.001, verbose=False):    # f è una funzione!
    # alcune accortezze
    if x2 <= x1:
        print('x2 must be greater than x1')
        return
    elif f(x1)*f(x2) >= 0:
        print('f(x1) and f(x2) must have opposite signs')
        return
    else:
        xm = (x1+x2)/2
        while x2-x1 > risoluzione:
            if verbose:
                print(x1,x2)            # scommenta per stampare le varie iterazioni
            xm = (x1+x2)/2
            if f(xm)*f(x1) >= 0:
                x1 = xm
            else:
                x2 = xm
        return xm
