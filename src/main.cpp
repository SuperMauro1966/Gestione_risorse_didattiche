#include <iostream>
#include "security/security.hpp"

using namespace std;

int StampaMessaggioBenvenuto () {
    cout << "Benvenuto" << endl;
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
