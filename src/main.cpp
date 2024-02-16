#include <iostream>
#include "security/security.hpp"

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
    return 0;
}
