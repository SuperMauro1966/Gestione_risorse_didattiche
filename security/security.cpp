#include <iostream>
#include <string>
#include <sqlite3.h>
#include "../db/db.hpp"

bool VerificaTutorAdmin (std :: string email, std :: string password) {
    int rc;
    sqlite3 *db;
    db = ApriConnessione("./db/risorse_didattiche.db");
    const char *verifica_email = "SELECT tb_tutor.mail_interna, tb_tutor.Password FROM tb_tutor WHERE tb_tutor.mail_interna = :MAIL AND tb_tutor.password = :PASSWORD;";
    sqlite3_stmt *pstmt;
    rc = sqlite3_prepare_v2 (db, verifica_email, -1, &pstmt, NULL);

    if (rc != SQLITE_OK){
        std :: cerr << "Impossibile creare statement" << std :: endl;
        sqlite3_close (db);
        return (1);
    }

    int pos_par;
    pos_par = sqlite3_bind_parameter_index (pstmt, ":MAIL");
    rc = sqlite3_bind_text (pstmt, pos_par, reinterpret_cast<const char *> (email.c_str()), -1, NULL);
    if ( rc != SQLITE_OK) {
        std :: cerr << "Errore nell'inserimento della mail" << std :: endl;
        sqlite3_close (db);
        return false;
    }

    pos_par = sqlite3_bind_parameter_index (pstmt, ":PASSWORD");
    rc = sqlite3_bind_text (pstmt, pos_par, reinterpret_cast<const char *> (password.c_str()), -1, NULL);
    if ( rc != SQLITE_OK) {
        std :: cerr << "Errore nell'inserimento della password" << std :: endl;
        sqlite3_close (db);
        return false;
    }

    rc = sqlite3_step (pstmt);
    if (rc == SQLITE_ROW) {
        std :: cerr << "Parametro trovato con successo" << std :: endl;
        sqlite3_finalize (pstmt);
        sqlite3_close (db);
        return true;
    }

    else if (rc == SQLITE_DONE) {
        std :: cerr << "Nessun utente trovato con tali credenziali" << std :: endl;
        sqlite3_finalize (pstmt);
        sqlite3_close (db);
        return false;
    }

    std :: cerr << "Errore nell'esecuzione dell'istruzione sql" << std :: endl;
    std :: cerr << rc << std :: endl;
    std :: cerr << sqlite3_errstr(sqlite3_extended_errcode(db)) << std :: endl;
    std :: cerr << sqlite3_errmsg(db) << std :: endl;
    sqlite3_finalize (pstmt);
    sqlite3_close (db);
    return false;
    }

bool VerificaStudente (std :: string email, std :: string password) {
    int rc;
    sqlite3 *db;
    db = ApriConnessione("./db/risorse_didattiche.db");
    if (rc!= SQLITE_OK) {
        std :: cerr << "Errore apertura database" << std :: endl;
        sqlite3_close(db);
        return false;
    }

    sqlite3_stmt* stmt;
    const char* ver_mail_password = "SELECT tb_studente.mail_istituzionale, tb_studente.Password FROM tb_studente WHERE tb_studente.mail_istituzionale = :MAIL AND tb_studente.password = :PASSWORD;";
    rc = sqlite3_prepare_v2 (db, "SELECT tb_studente.mail_istituzionale, tb_studente.Password FROM tb_studente WHERE tb_studente.mail_istituzionale = :MAIL AND tb_studente.password = :PASSWORD;", -1, &stmt, NULL);


    if (rc!= SQLITE_OK) {
        std :: cerr << "Errore creazione statement" << std :: endl;
        std :: cerr << rc << std :: endl;
        std :: cerr << sqlite3_errstr(sqlite3_extended_errcode(db)) << std :: endl;
        std :: cerr << sqlite3_errmsg(db) << std :: endl;
        sqlite3_finalize (stmt);
        sqlite3_close(db);
        return false;
    }

    int pos_par;
    pos_par = sqlite3_bind_parameter_index (stmt, ":MAIL");
    rc = sqlite3_bind_text (stmt, pos_par, reinterpret_cast<const char *> (email.c_str()), -1, NULL);
    if ( rc != SQLITE_OK) {
        std :: cerr << "Errore nell'inserimento della mail" << std :: endl;
        sqlite3_close (db);
        return false;
    }

    pos_par = sqlite3_bind_parameter_index (stmt, ":PASSWORD");
    rc = sqlite3_bind_text (stmt, pos_par, reinterpret_cast<const char *> (password.c_str()), -1, NULL);
    if ( rc != SQLITE_OK) {
        std :: cerr << "Errore nell'inserimento della password" << std :: endl;
        sqlite3_close (db);
        return false;
    }

    rc = sqlite3_step (stmt);

    if (rc == SQLITE_ROW) {
        std :: cerr << "Parametro trovato con successo" << std :: endl;

        sqlite3_finalize (stmt);
        sqlite3_close (db);
        return true;
    }

    else if (rc == SQLITE_DONE) {
        std :: cerr << "Nessun utente trovato con tali credenziali" << std :: endl;

        sqlite3_finalize (stmt);
        sqlite3_close (db);
        return false;
    }

    std :: cerr << "Errore nell'esecuzione dell'istruzione sql" << std :: endl;
    std :: cerr << rc << std :: endl;
    std :: cerr << sqlite3_errstr(sqlite3_extended_errcode(db)) << std :: endl;
    std :: cerr << sqlite3_errmsg(db) << std :: endl;
    sqlite3_finalize (stmt);
    sqlite3_close (db);
    return false;
}


bool AutorizzazioneUtente () {
    // Richiedi email e la password
    // Se tutor/admin o Studente ritorna ok
    std :: string email ("");
    std :: string password ("");
    std :: cout << "Inserire email" << std :: endl;
    std :: cin >> email;
    std :: cout << "Inserisci password" << std :: endl;
    std :: cin >> password;
    // Se sei tutor o admin ritorna true
    if (VerificaTutorAdmin(email, password)){
        return true;
    }
    else if (VerificaStudente(email, password)){ // se sei studente ritorna true
        return true;
    }
    // Altrimenti ritorna false
    return false;
}
