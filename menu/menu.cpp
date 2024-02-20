#include <iostream>
#include "../security/security.hpp"

void MostraMenuTutor () {
    std :: cout << "Men� Tutor: " << std :: endl;
}

void MostraMenuStudente () {
    int scelta;
    std :: cout << '\0x1B' << '[' << '2' << 'J' << std :: flush;
    std :: cout << "Men� Studente: " << std :: endl;
    std :: cout << "Scegliere il men� da visualizzare: ";
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
    std :: cout << "Men� Admin: " << std :: endl;
}

void MostraMenu (utente_t utente){
    switch (utente)
    {
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
