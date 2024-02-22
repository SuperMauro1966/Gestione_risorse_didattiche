#include <sqlite3.h>
#include <iostream>
#include <../db/db.hpp>
#include <list>

bool MostraMaterieArgomento () {
    // stampa le materie obbligatorie e facoltative e i loro argomenti collegati che lo studente segue e stamparle

    int rc;
    sqlite3 *db;
    db = GetConnessione("./db/risorse_didattiche.db");
    const char *verifica_email = "SELECT c.Nome AS 'Nome Corso', ar.nome 'Nome Argomento' FROM tb_corso AS c INNER JOIN tb_studente_corso_facoltativo AS cf ON cf.id_corso = c.ID_corso INNER JOIN tb_studente AS st ON cf.matricola = st.Matricola INNER JOIN tb_argomento AS ar ON ar.id_corso = c.id_corso WHERE st.Matricola = :MATRICOLA ORDER BY c.Nome, ar.nome ";
    sqlite3_stmt *pstmt;
    rc = sqlite3_prepare_v2 (db, verifica_email, -1, &pstmt, NULL);

    if (rc != SQLITE_OK){
        std :: cerr << "Impossibile creare statement" << std :: endl;
        return (1);
    }

    int pos_par;
    pos_par = sqlite3_bind_parameter_index (pstmt, ":MATRICOLA");
    rc = sqlite3_bind_int (pstmt, pos_par, -1);
    if ( rc != SQLITE_OK) {
        std :: cerr << "Errore nell'inserimento della matricola" << std :: endl;
        return false;
    }

    rc = sqlite3_step (pstmt);
    if (rc == SQLITE_ROW) {
        std :: clog << "Parametro trovato con successo" << std :: endl;
        sqlite3_finalize (pstmt);
        return true;
    }

    else if (rc == SQLITE_DONE) {
        std :: clog << "Nessun utente trovato con tali credenziali" << std :: endl;
        sqlite3_finalize (pstmt);
        return false;
    }

    std :: clog << "Errore nell'esecuzione dell'istruzione sql" << std :: endl;
    std :: clog << rc << std :: endl;
    std :: clog << sqlite3_errstr(sqlite3_extended_errcode(db)) << std :: endl;
    std :: clog << sqlite3_errmsg(db) << std :: endl;
    sqlite3_finalize (pstmt);
    return false;

    std :: cerr << "Lista delle materie facoltative seguite dallo studente: " << std :: endl;
    std :: list<CorsoArgomento> * corsi_facoltativi = OttieniMaterieFacoltativeByMatricola();
    if (!corsi_facoltativi->empty()) {
    corsi_facoltativi->pop_front();
    }
    delete corsi_facoltativi;
    return true;
}


