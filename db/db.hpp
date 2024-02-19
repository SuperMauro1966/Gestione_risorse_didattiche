#ifndef DB_HPP_INCLUDED
#define DB_HPP_INCLUDED
#include <sqlite3.h>

sqlite3* ApriConnessione(std :: string nome_db);
void ChiudiConnessione (sqlite3* connessione);

#endif // DB_HPP_INCLUDED
