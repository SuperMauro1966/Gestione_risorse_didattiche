#ifndef SECURITY_HPP_INCLUDED
#define SECURITY_HPP_INCLUDED
#include <string>

enum utente_t {NonAutorizzato, Studente, Tutor, Admin};

utente_t AutorizzazioneUtente (std :: string &email, std :: string &password);

#endif // SECURITY_HPP_INCLUDED
