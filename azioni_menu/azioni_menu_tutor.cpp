#include <iostream>
#include <sqlite3.h>
#include <string>
#include "../db/db.hpp"


bool RimuoviArgomenti () {
    int rc;
    std :: string argomento;
    std :: cout << "Inserisci il nome del argomento che vuoi rimuovere" << std :: endl;
    std :: cin >> argomento;

    std::cout << "Sei sicuro di cancellare l'argomento? s==si, n==no" << std :: endl;
    char risposta;
    std::cin >> risposta;
    if (risposta != 's') {
        std::cout << "Operazione annullata." << std::endl;
        return false;
    }


    sqlite3 *db;
    db = GetConnessione("./db/risorse_didattiche.db");

    const char *rimuovi_argomenti = "UPDATE tb_argomento SET nome = NULL WHERE nome = :NOME;";
    sqlite3_stmt *pstmt;
    rc = sqlite3_prepare_v2 (db, rimuovi_argomenti, -1, &pstmt, NULL);

    if (rc != SQLITE_OK){
        std :: cerr << "Impossibile creare statement" << std :: endl;
        return (1);
    }

    int pos_par;
    pos_par = sqlite3_bind_parameter_index (pstmt, ":NOME");
    rc = sqlite3_bind_text (pstmt, pos_par, reinterpret_cast<const char *> (argomento.c_str()), -1, NULL);
    if ( rc != SQLITE_OK) {
        std :: cerr << "" << std :: endl;
        return false;
    }

    rc = sqlite3_step(pstmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Errore nell'esecuzione dello statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(pstmt);
        sqlite3_close(db);
        return false;
    }

    std::cout << "Argomento rimosso con successo." << std::endl;

    sqlite3_finalize (pstmt);
    return false;
}
