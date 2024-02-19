#include <sqlite3.h>
#include <string>
#include <iostream>

sqlite3* ApriConnessione(std :: string nome_db){
    sqlite3 *db;
    int rc;
    rc = sqlite3_open(reinterpret_cast<const char*>(nome_db.c_str()), &db);
    if (rc != SQLITE_OK){
        std :: clog << "Impossibile aprire database" << std :: endl;
        return nullptr;
    }
    return db;
}

void ChiudiConnessione (sqlite3* connessione) {
    std :: clog << "Chiuso database" << std :: endl;
    sqlite3_close (connessione);
}
