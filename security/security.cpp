#include <iostream>
#include <string>
#include <sqlite3.h>
#include "../db/db.hpp"
#include "../security/security.hpp"

bool VerificaTutor (std :: string email, std :: string password) {
    int rc;
    sqlite3 *db;
    db = GetConnessione("./db/risorse_didattiche.db");
    const char *verifica_email = "SELECT tb_tutor.mail_interna, tb_tutor.Password FROM tb_tutor WHERE tb_tutor.mail_interna = :MAIL AND tb_tutor.password = :PASSWORD;";
    sqlite3_stmt *pstmt;
    rc = sqlite3_prepare_v2 (db, verifica_email, -1, &pstmt, NULL);

    if (rc != SQLITE_OK){
        std :: clog << "Impossibile creare statement" << std :: endl;
        sqlite3_close (db);
        return (1);
    }

    int pos_par;
    pos_par = sqlite3_bind_parameter_index (pstmt, ":MAIL");
    rc = sqlite3_bind_text (pstmt, pos_par, reinterpret_cast<const char *> (email.c_str()), -1, NULL);
    if ( rc != SQLITE_OK) {
        std :: clog << "Errore nell'inserimento della mail" << std :: endl;
        sqlite3_close (db);
        return false;
    }

    pos_par = sqlite3_bind_parameter_index (pstmt, ":PASSWORD");
    rc = sqlite3_bind_text (pstmt, pos_par, reinterpret_cast<const char *> (password.c_str()), -1, NULL);
    if ( rc != SQLITE_OK) {
        std :: clog << "Errore nell'inserimento della password" << std :: endl;
        sqlite3_close (db);
        return false;
    }

    rc = sqlite3_step (pstmt);
    if (rc == SQLITE_ROW) {
        std :: clog << "Parametro trovato con successo" << std :: endl;
        sqlite3_finalize (pstmt);
        sqlite3_close (db);
        return true;
    }

    else if (rc == SQLITE_DONE) {
        std :: clog << "Nessun utente trovato con tali credenziali" << std :: endl;
        sqlite3_finalize (pstmt);
        sqlite3_close (db);
        return false;
    }

    std :: clog << "Errore nell'esecuzione dell'istruzione sql" << std :: endl;
    std :: clog << rc << std :: endl;
    std :: clog << sqlite3_errstr(sqlite3_extended_errcode(db)) << std :: endl;
    std :: clog << sqlite3_errmsg(db) << std :: endl;
    sqlite3_finalize (pstmt);
    sqlite3_close (db);
    return false;
    }

bool VerificaAdmin (std :: string email, std :: string password){
    return true;
}

bool VerificaStudente (std :: string email, std :: string password) {
    int rc;
    sqlite3 *db;
    db = GetConnessione("./db/risorse_didattiche.db");
    if (rc!= SQLITE_OK) {
        std :: clog << "Errore apertura database" << std :: endl;
        sqlite3_close(db);
        return false;
    }

    sqlite3_stmt* stmt;
    const char* ver_mail_password = "SELECT tb_studente.mail_istituzionale, tb_studente.Password FROM tb_studente WHERE tb_studente.mail_istituzionale = :MAIL AND tb_studente.password = :PASSWORD;";
    rc = sqlite3_prepare_v2 (db, "SELECT tb_studente.mail_istituzionale, tb_studente.Password FROM tb_studente WHERE tb_studente.mail_istituzionale = :MAIL AND tb_studente.password = :PASSWORD;", -1, &stmt, NULL);


    if (rc!= SQLITE_OK) {
        std :: clog << "Errore creazione statement" << std :: endl;
        std :: clog << rc << std :: endl;
        std :: clog << sqlite3_errstr(sqlite3_extended_errcode(db)) << std :: endl;
        std :: clog << sqlite3_errmsg(db) << std :: endl;
        sqlite3_finalize (stmt);
        sqlite3_close(db);
        return false;
    }

    int pos_par;
    pos_par = sqlite3_bind_parameter_index (stmt, ":MAIL");
    rc = sqlite3_bind_text (stmt, pos_par, reinterpret_cast<const char *> (email.c_str()), -1, NULL);
    if ( rc != SQLITE_OK) {
        std :: clog << "Errore nell'inserimento della mail" << std :: endl;
        sqlite3_close (db);
        return false;
    }

    pos_par = sqlite3_bind_parameter_index (stmt, ":PASSWORD");
    rc = sqlite3_bind_text (stmt, pos_par, reinterpret_cast<const char *> (password.c_str()), -1, NULL);
    if ( rc != SQLITE_OK) {
        std :: clog << "Errore nell'inserimento della password" << std :: endl;
        sqlite3_close (db);
        return false;
    }

    rc = sqlite3_step (stmt);

    if (rc == SQLITE_ROW) {
        std :: clog << "Parametro trovato con successo" << std :: endl;

        sqlite3_finalize (stmt);
        sqlite3_close (db);
        return true;
    }

    else if (rc == SQLITE_DONE) {
        std :: clog << "Nessun utente trovato con tali credenziali" << std :: endl;

        sqlite3_finalize (stmt);
        sqlite3_close (db);
        return false;
    }

    std :: clog << "Errore nell'esecuzione dell'istruzione sql" << std :: endl;
    std :: clog << rc << std :: endl;
    std :: clog << sqlite3_errstr(sqlite3_extended_errcode(db)) << std :: endl;
    std :: clog << sqlite3_errmsg(db) << std :: endl;
    sqlite3_finalize (stmt);
    sqlite3_close (db);
    return false;
}


utente_t AutorizzazioneUtente () {
    // Richiedi email e la password
    // Se tutor/admin o Studente ritorna ok
    std :: string email ("");
    std :: string password ("");
    std :: cout << "Inserire email" << std :: endl;
    std :: cin >> email;
    std :: cout << "Inserisci password" << std :: endl;
    std :: cin >> password;
    // Se sei tutor o admin ritorna true
    if (VerificaTutor(email, password)){
        return Tutor;
    }
    else if (VerificaStudente(email, password)){ // se sei studente ritorna true
        return Studente;
    }
    else if (VerificaAdmin(email, password)){
        return Admin;
    }
    // Altrimenti ritorna false
    return NonAutorizzato;
}
