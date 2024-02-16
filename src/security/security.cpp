#include <string>


bool AutorizzazioneUtente () {
    // Richiedi email e la password
    // Se tutor/admin o Studente ritorna ok
    std :: string email ("");
    std :: string password ("");
    cout << "Inserire email" << endl;
    cin >> email;
    cout << "Inserisci password" << endl;
    cin >> password;
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
