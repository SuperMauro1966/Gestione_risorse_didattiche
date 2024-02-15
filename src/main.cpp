#include <iostream>

using namespace std;

int StampaMessaggioBenvenuto () {
    cout << "Benvenuto" << endl;
}

bool AutorizzazioneUtente () {
    // Richiedi email e la password
    // Se tutor/admin o Studente ritorna ok
    string email ("");
    string password ("");
    cout << "Inserire email" << endl;
    cin >> email;
    cout << "Inserisci password" << endl;
    cin >> password;
    // Se sei tutor o admin ritorna true
    // se sei studente ritorna true
    // Altrimenti ritorna false
    return true;
}

bool RuoloStudente () {
    char ruolo;
    cout << "Se studente selezionare s" << endl;
    cin >> ruolo;

    if (ruolo == 's' || ruolo == 'S')
        return true;
    else
        return false;
}

bool RuoloTutor () {
    char ruolo;
    cout << "Se tutor selezionare t" << endl;
    cin >> ruolo;

    if (ruolo == 't' || ruolo == 'T')
        return true;
    else
        return false;
}

void MostraMenu (){
}

int main()
{
    bool autorizzato;

    while (true) {
        StampaMessaggioBenvenuto ();
        autorizzato = AutorizzazioneUtente ();

        if (autorizzato) {
            MostraMenu ();
        }
    }
    return 0;
}
