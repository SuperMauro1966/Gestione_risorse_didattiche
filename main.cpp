#include <iostream>
#include "security/security.hpp"
#include "db/db.hpp"

using namespace std;

int StampaMessaggioBenvenuto () {
    cout << "Benvenuto" << endl;
}

void MostraMenu (){
    cout << "++Menu principale**" << endl;
}

int main()
{
    bool autorizzato;
    sqlite3* con;

    con = ApriConnessione ("./db/risorse_didattiche.db");

    while (true) {
        StampaMessaggioBenvenuto ();
        autorizzato = AutorizzazioneUtente ();

        if (autorizzato) {
            MostraMenu ();
        }
        else {
            cout << "Utente non autorizzato" << endl;
        }
    }

    ChiudiConnessione (con);

    return 0;
}
