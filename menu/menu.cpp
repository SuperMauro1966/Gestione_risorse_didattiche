#include <iostream>
#include "../security/security.hpp"


void MostraMenuTutor () {

    int sm;
    std :: cout << "Menù Tutor: " << std :: endl;

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
    std :: cout << "Menù Studente: " << std :: endl;
}

void MostraMenuAdmin () {
    std :: cout << "Menù Admin: " << std :: endl;
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
