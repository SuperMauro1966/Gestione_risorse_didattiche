#include <iostream>
#include <string>
#include <sqlite3.h>

bool VerificaTutorAdmin (std :: string email, std :: string password) {
    sqlite3 *db;
    int rc;
    rc = sqlite3_open("../db/risorse_didattiche.db", &db);
    if (rc != SQLITE_OK){
        std :: cerr << "Impossibile aprire database" << std :: endl;
        sqlite3_close(db);
        return (1);
    }
    const char *verifica_email = "SELECT tb_tutor.mail_interna, tb_tutor.Password FROM tb_tutor;";
    sqlite3_stmt *pstmt;
    rc = sqlite3_prepare_v2 (db, verifica_email, -1, &pstmt, NULL);

    if (rc != SQLITE_OK){
        std :: cerr << "Impossibile creare statement" << std :: endl;
        sqlite3_close (db);
        return (1);
    }

    rc = sqlite3_step (pstmt);
    bool val = false;
    while (rc == SQLITE_ROW){
        const unsigned char* mail = sqlite3_column_text (pstmt, 0);
        const unsigned char* pass = sqlite3_column_text (pstmt, 1);
        if (email == reinterpret_cast<const char*> (mail) && password == reinterpret_cast<const char*> (pass)){
            std :: cerr << "Utente verificato" << std :: endl;
            val = true;
            break;
        } else {
            std :: cerr << "Email o password errati" << std :: endl;
            break;
        }
        rc = sqlite3_step (pstmt);
    }
    sqlite3_finalize (pstmt);
    sqlite3_close (db);

    return val;

}

bool VerificaStudente (std :: string email, std :: string password) {
    sqlite3* db;
    int rc = sqlite3_open ("../db/risorse_didattiche.db", &db);

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
