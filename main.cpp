#include <iostream>
#include "security/security.hpp"
#include "db/db.hpp"
#include "menu/menu.hpp"

using namespace std;

int StampaMessaggioBenvenuto () {
    cout << "Benvenuto" << endl;
}

int main()
{
    utente_t autorizzazione_utente;
    sqlite3* con;

    con = GetConnessione ("./db/risorse_didattiche.db");

    while (true) {
        StampaMessaggioBenvenuto ();
        autorizzazione_utente = AutorizzazioneUtente ();

        if (autorizzazione_utente != NonAutorizzato) {
            MostraMenu (autorizzazione_utente);
        }
        else {
            cout << "Utente non autorizzato" << endl;
        }
    }

    ChiudiConnessione (con);

    return 0;
}
