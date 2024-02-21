#include <iostream>
#include "security/security.hpp"
#include <string>
#include "db/db.hpp"
#include "menu/menu.hpp"

// using namespace std;
using std :: cout, std :: cin, std :: endl;
void RichiediCredenziali (std :: string &email, std :: string &password) {

    cout << "Inserire email" << std :: endl;
    cin >> email;
    std :: cout << "Inserisci password" << std :: endl;
    std :: cin >> password;

}
int StampaMessaggioBenvenuto () {
    cout << "Benvenuto" << endl;
}

int main()
{
    utente_t autorizzazione_utente;
    sqlite3* con;
    std :: string email;
    std :: string password;

    con = GetConnessione ("./db/risorse_didattiche.db");

    while (true) {
        StampaMessaggioBenvenuto ();
        RichiediCredenziali (email, password);
        if (email == "q" && password == "q"){
            break;
        }
        autorizzazione_utente = AutorizzazioneUtente (email, password);
        if (autorizzazione_utente != NonAutorizzato) {
            MostraMenu (autorizzazione_utente);
        }
        else
        {
            cout << "Utente non autorizzato" << endl;
        }
    }

    ChiudiConnessione (con);

    return 0;
}
