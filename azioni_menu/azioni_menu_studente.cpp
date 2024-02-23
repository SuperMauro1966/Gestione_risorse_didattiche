#include <sqlite3.h>
#include <iostream>
#include <../db/db.hpp>
#include <list>

void MostraRisorseDisponibili () {
    int rc;
    int matricola;

    sqlite3 *db;
    rc = sqlite3_open("./db/risorse_didattiche.db", &db);
    if (rc) {
        std::cerr << "Impossibile aprire il database: " << std::endl;
    }

    const char *mostra_risorse = "SELECT tb_argomento.nome, tb_elenco_risorse_disponibili.Tipo FROM tb_argomento INNER JOIN tb_corso ON tb_argomento.id_corso = tb_corso.ID_corso INNER JOIN tb_studente_corso ON tb_corso.ID_corso = tb_studente_corso.id_corso INNER JOIN tb_studente ON tb_studente_corso.matricola = tb_studente.Matricola INNER JOIN tb_elenco_risorse_disponibili ON tb_studente.Matricola = tb_elenco_risorse_disponibili.matricola WHERE tb_elenco_risorse_disponibili.matricola = :MATRICOLA;";
    sqlite3_stmt *pstmt;
    rc = sqlite3_prepare_v2 (db, mostra_risorse, -1, &pstmt, NULL);

    if (rc != SQLITE_OK){
        std :: cerr << "Impossibile creare statement" << std :: endl;
    }

    std :: cerr << "Inserici il numero della matricola" << std :: endl;
    std :: cin >> matricola;
    int pos_par;
    pos_par = sqlite3_bind_parameter_index (pstmt, ":MATRICOLA");
    rc = sqlite3_bind_int (pstmt, pos_par, matricola);
    if ( rc != SQLITE_OK) {
        std :: cerr << "Errore nell'inserimento del numero della matricola" << std :: endl;
    }

    rc = sqlite3_step(pstmt);

     while ( rc == SQLITE_ROW) {
        std::cout << sqlite3_column_text(pstmt, 0) << " " << sqlite3_column_text(pstmt, 1) << std::endl;
        rc = sqlite3_step(pstmt);
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "Errore nel recupero dei dati: " << std::endl;
    }

    sqlite3_finalize(pstmt);

}

void MostraArgomenti() {
    sqlite3 *db;
    int rc = sqlite3_open("./db/risorse_didattiche.db", &db);
    if (rc) {
        std::cerr << "Impossibile aprire il database: " << std::endl;
    }

    const char *query = "SELECT tb_argomento.nome FROM tb_argomento;";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Impossibile eseguire la query: " << std::endl;
        sqlite3_close(db);
    }

    rc = sqlite3_step(stmt);

    while ( rc != SQLITE_ROW) {
        // Stampa i dati di ogni colonna della riga
        for (int i = 0; i < sqlite3_column_count(stmt); ++i) {
            std::cout << sqlite3_column_text(stmt, i);
        }
        std::cout << std::endl;
    }

    if (rc == SQLITE_DONE) {
        std::cerr << "Errore nel recupero dei dati: " << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

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

}


