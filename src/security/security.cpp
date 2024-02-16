#include <iostream>
#include <string>
#include <sqlite3.h>

bool VerificaTutorAdmin (std :: string email, std :: string password) {
    sqlite3 *db;
    int rc;
    rc = sqlite3_open("../db/risorse_didattiche.db", &db);
    if (rc != SQLITE_OK){
        std :: cout << "Impossibile aprire database" << std :: endl;
        sqlite3_close(db);
        return (1);
    }
    const char *verifica_email = "SELECT tb_tutor.mail_interna, tb_tutor.Password FROM tb_tutor;";
    sqlite3_stmt *pstmt;
    rc = sqlite3_prepare_v2 (db, verifica_email, -1, &pstmt, NULL);

    if (rc != SQLITE_OK){
        std :: cout << "Impossibile creare statement" << std :: endl;
        sqlite3_close (db);
        return (1);
    }

    rc = sqlite3_step (pstmt);
    bool val = false;
    while (rc == SQLITE_ROW){
        const unsigned char* mail = sqlite3_column_text (pstmt, 0);
        const unsigned char* pass = sqlite3_column_text (pstmt, 1);
        if (email == reinterpret_cast<const char*> (mail) && password == reinterpret_cast<const char*> (pass)){
            std :: cout << "Utente verificato" << std :: endl;
            val = true;
            break;
        }
        rc = sqlite3_step (pstmt);
    }
    sqlite3_finalize (pstmt);
    sqlite3_close (db);

    return val;

}

bool VerificaStudente () {
    return true;
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
    else if (VerificaStudente()){ // se sei studente ritorna true
        return true;
    }
    // Altrimenti ritorna false
    return false;
}
