#include <iostream>
#include "../security/security.hpp"

inline void ClearScreen () {
    std :: cout << "\033[2J\033[\1;1H";
}

void MostraMenuTutor () {
    int sm;
    ClearScreen();
    std :: cout << "Menu Tutor: " << std :: endl;

    std :: cout << "0- Inserisci argomenti: " << std :: endl;
    std :: cout << "1- Rimuovi argomenti: " << std :: endl;
    std :: cout << "2- Modifica argomenti: " << std :: endl;
    std :: cout << "3- I tuoi studenti" << std :: endl;

    std :: cout << "" << std :: endl;
    std :: cout << "Scegli il menu " << std :: endl;
    std :: cin >> sm;

    if (sm == 0) {
        std :: cout << "0- Inserisci argomenti: " << std :: endl;
    }
    else if (sm == 1) {
       std :: cout << "1- Rimuovi argomenti: " << std :: endl;
    }
    else if (sm == 2) {
        std :: cout << "2- Modifica argomenti: " << std :: endl;
    }
    else if (sm == 3) {
        std :: cout << "3- I tuoi studenti" << std :: endl;
    }

}

void MostraMenuStudente () {
    int scelta;
    std :: cout << "\033[2J\033[\1;1H";
    std :: cout << "Menu Studente: " << std :: endl;
    std :: cout << "Scegliere il menu da visualizzare: " << std :: endl;
    std :: cout << "1. Le tue materie" << std :: endl;
    std :: cout << "2. Le risorse disponibili" << std :: endl;
    std :: cout << "3. Aggiungi risorse" << std :: endl;
    std :: cout << "4. Rimuovi risorse" << std :: endl;
    std :: cout << "5. Vedi tutor disponibili" << std :: endl;
    std :: cin >> scelta;
    if ( scelta == 1) {
        std :: cout << "Le tue materie: " << std :: endl;
    }
    else if ( scelta == 2 ) {
        std :: cout << "Le risorse disponibili: " << std :: endl;
    }
    else if ( scelta == 3 ) {
        std :: cout << "Aggiungi risorse: " << std :: endl;
    }
    else if ( scelta == 4 ) {
        std :: cout << "Rimuovi risorse: " << std :: endl;
    }
    else if ( scelta == 5 ) {
        std :: cout << "Vedi tutor disponibili: " << std :: endl;
    }

}

void MostraMenuAdmin () {
    std :: cout << "Menu Admin: " << std :: endl;
}

void MostraMenu (utente_t utente){

    switch (utente) {
        case Admin:
            MostraMenuAdmin ();
            break;
        case Tutor:
            MostraMenuTutor ();
            break;
        case Studente:
            MostraMenuStudente ();
            break;
        default:
            std :: cout << "Nessun menu disponibile per questo utente" << std :: endl;
    }
}
