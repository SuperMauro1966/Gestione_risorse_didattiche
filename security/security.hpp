#ifndef SECURITY_HPP_INCLUDED
#define SECURITY_HPP_INCLUDED

enum utente_t {NonAutorizzato, Studente, Tutor, Admin};

utente_t AutorizzazioneUtente ();

#endif // SECURITY_HPP_INCLUDED
