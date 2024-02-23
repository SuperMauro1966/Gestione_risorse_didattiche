#ifndef DB_HPP_INCLUDED
#define DB_HPP_INCLUDED
#include <sqlite3.h>
#include <string>
#include <list>

struct CorsoArgomento {
        std::string NomeCorso;
        std::string NomeArgomento;
        std::string nome;
};

typedef struct CorsoArgomento CorsoArgomento;

struct RisorseArgomento {
        std :: string Argomento;
        std :: string tipologia;
};

typedef struct RisorseArgomento RisorseArgomento;


sqlite3* GetConnessione(std :: string nome_db);
void ChiudiConnessione (sqlite3* connessione);

std::list<CorsoArgomento> OttieniMaterieFacoltativeByMatricola();

std::list<RisorseArgomento> OttieniRisorseDisponibiliByMatricola();

#endif // DB_HPP_INCLUDE
