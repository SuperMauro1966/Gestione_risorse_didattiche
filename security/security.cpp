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
        std :: cerr << "Impossibile creare statement" << std :: endl;
        return (1);
    }

    int pos_par;
    pos_par = sqlite3_bind_parameter_index (pstmt, ":MAIL");
    rc = sqlite3_bind_text (pstmt, pos_par, reinterpret_cast<const char *> (email.c_str()), -1, NULL);
    if ( rc != SQLITE_OK) {
        std :: cerr << "Errore nell'inserimento della mail" << std :: endl;
        return false;
    }

    pos_par = sqlite3_bind_parameter_index (pstmt, ":PASSWORD");
    rc = sqlite3_bind_text (pstmt, pos_par, reinterpret_cast<const char *> (password.c_str()), -1, NULL);
    if ( rc != SQLITE_OK) {
        std :: cerr << "Errore nell'inserimento della password" << std :: endl;
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

bool Admin_TutorPresenti (std :: string email, std :: string password, bool admin){
    int rc;
    sqlite3 *db;
    db = GetConnessione("./db/risorse_didattiche.db");
    const char *verifica_email = "SELECT tb_tutor.mail_interna, tb_tutor.Password FROM tb_tutor WHERE tb_tutor.mail_interna = :MAIL AND tb_tutor.password = :PASSWORD AND tb_tutor.Admin = :ISADMIN;";
    sqlite3_stmt *pstmt;
    rc = sqlite3_prepare_v2 (db, verifica_email, -1, &pstmt, NULL);

    if (rc != SQLITE_OK){
        std :: cerr << "Impossibile creare statement" << std :: endl;
        return false;
    }

    int pos_par;
    pos_par = sqlite3_bind_parameter_index (pstmt, ":MAIL");
    rc = sqlite3_bind_text (pstmt, pos_par, reinterpret_cast<const char *> (email.c_str()), -1, NULL);
    if ( rc != SQLITE_OK) {
        std :: cerr << "Errore nell'inserimento della mail" << std :: endl;
        return false;
    }

    pos_par = sqlite3_bind_parameter_index (pstmt, ":PASSWORD");
    rc = sqlite3_bind_text (pstmt, pos_par, reinterpret_cast<const char *> (password.c_str()), -1, NULL);
    if ( rc != SQLITE_OK) {
        std :: cerr << "Errore nell'inserimento della password" << std :: endl;
        return false;
    }

    pos_par = sqlite3_bind_parameter_index (pstmt, ":ISADMIN");
    rc = sqlite3_bind_int (pstmt, pos_par, admin);
    if ( rc != SQLITE_OK) {
        std :: cerr << "Errore nell'inserimento della password" << std :: endl;
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

bool VerificaStudente (std :: string email, std :: string password) {
    int rc;
    sqlite3 *db;
    db = GetConnessione("./db/risorse_didattiche.db");
    if (rc!= SQLITE_OK) {
        std :: cerr << "Errore apertura database" << std :: endl;
        return false;
    }

    sqlite3_stmt* stmt;
    const char* ver_mail_password = "SELECT tb_studente.mail_istituzionale, tb_studente.Password FROM tb_studente WHERE tb_studente.mail_istituzionale = :MAIL AND tb_studente.password = :PASSWORD;";
    rc = sqlite3_prepare_v2 (db, ver_mail_password, -1, &stmt, NULL);


    if (rc!= SQLITE_OK) {
        std :: clog << "Errore creazione statement" << std :: endl;
        std :: clog << rc << std :: endl;
        std :: clog << sqlite3_errstr(sqlite3_extended_errcode(db)) << std :: endl;
        std :: clog << sqlite3_errmsg(db) << std :: endl;
        sqlite3_finalize (stmt);
        return false;
    }

    int pos_par;
    pos_par = sqlite3_bind_parameter_index (stmt, ":MAIL");
    rc = sqlite3_bind_text (stmt, pos_par, reinterpret_cast<const char *> (email.c_str()), -1, NULL);
    if ( rc != SQLITE_OK) {
        std :: cerr << "Errore nell'inserimento della mail" << std :: endl;
        return false;
    }

    pos_par = sqlite3_bind_parameter_index (stmt, ":PASSWORD");
    rc = sqlite3_bind_text (stmt, pos_par, reinterpret_cast<const char *> (password.c_str()), -1, NULL);
    if ( rc != SQLITE_OK) {
        std :: cerr << "Errore nell'inserimento della password" << std :: endl;
        return false;
    }

    rc = sqlite3_step (stmt);

    if (rc == SQLITE_ROW) {
        std :: clog << "Parametro trovato con successo" << std :: endl;
        sqlite3_finalize (stmt);
        return true;
    }

    else if (rc == SQLITE_DONE) {
        std :: clog << "Nessun utente trovato con tali credenziali" << std :: endl;
        sqlite3_finalize (stmt);
        return false;
    }

    std :: clog << "Errore nell'esecuzione dell'istruzione sql" << std :: endl;
    std :: clog << rc << std :: endl;
    std :: clog << sqlite3_errstr(sqlite3_extended_errcode(db)) << std :: endl;
    std :: clog << sqlite3_errmsg(db) << std :: endl;
    sqlite3_finalize (stmt);
    return false;
}


utente_t AutorizzazioneUtente (std :: string &email, std :: string &password) {
    // Verifico se sono un tutor
    if (VerificaTutor(email, password)){
        return Tutor;
    }
    // Verifico se sono uno studente
    else if (VerificaStudente(email, password)){ // se sei studente ritorna true
        return Studente;
    }
    // Verifico se sono un Admin
    else if (Admin_TutorPresenti(email, password, true)){
        return Admin;
    }
    // Altrimenti ritorna false
    return NonAutorizzato;
}
