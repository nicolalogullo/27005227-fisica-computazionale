
# Installazione e configuratione WSL
## Abilitare la virtualizzazione sul proprio PC

- Seguire [queste istruzioni](https://learn.microsoft.com/it-it/windows/wsl/install-manual#step-3---enable-virtual-machine-feature). Qualora non dovesse funzionare, abilitare la virtualizzazione manualmente dal BIOS. Consultare il sito del produttore della scheda madre.

## Setup Windodws Subsystem for Linux

Queste istruzioni sono prese da [qui](https://learn.microsoft.com/it-it/windows/wsl/install-manual)

- In generale dovrebbe bastare **eseguire come amministratore** il Prompt dei comandi e eseguire il comando

´´´ wsl --install ´´´

- (Probabilmente non necessario) Aggiornare il kernel Linux scaricando e installando il pacchetto che si trova [qui](https://learn.microsoft.com/it-it/windows/wsl/install-manual#step-4---download-the-linux-kernel-update-package)

# Installare Ubuntu

Sempre dal prompt dei comandi eseguire il comando

´´´ wsl --install -d ubuntu ´´´

Procedere con la configurazione dell'account come richiesto nel terminale. Bisogna fornire un nome utente e una password.

Procedere ora con un aggiornamento del sistema eseguendo i comandi

´´´ sudo apt install update
    sudo apt install upgrade ´´´




