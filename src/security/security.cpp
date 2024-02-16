#include <iostream>
#include <string>

bool VerificaTutorAdmin () {
}

bool VerificaStudente () {
}

bool AutorizzazioneUtente () {
    // Richiedi email e la password
    // Se tutor/admin o Studente ritorna ok
    std :: string email ("");
    std :: string password ("");
    std :: cout << "Inserire email" << std :: endl;
    std :: cin >> email;
    std :: cout << "Inserisci password" << std :: endl;
    std :: cin >> password;
    // Se sei tutor o admin ritorna true
    if (VerificaTutorAdmin()){
        return true;
    }
    else if (VerificaStudente()){ // se sei studente ritorna true
        return true;
    }
    // Altrimenti ritorna false
    return false;
}
