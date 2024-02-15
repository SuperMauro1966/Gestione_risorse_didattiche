#include <iostream>
#include <sqlite3.h>
#define P 3.14

using namespace std;
struct dato_composito {
    int a = 0;
    float b = 3.14;
    char c = 'z';
} composito;

struct dato_composito composito2;

typedef struct dato_composito dato_composito;

dato_composito composito3;

void inc (int a) {
    a = a+1;

}

int testa_db () {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    int pos_par;

    rc = sqlite3_open ("./db/risorse_didattiche.db", &db);

    if ( rc != SQLITE_OK) {
        cout << "Can't open database" << endl;
        sqlite3_close (db);
        return (1);
    }
    cout << "aperto database" << endl;
    /* const char *selezione_corso = "SELECT tb_argomento.nome, tb_studente_corso_facoltativo.matricola, tb_studente_corso_facoltativo.id_corso FROM tb_argomento INNER JOIN tb_corso ON tb_argomento.id_corso = tb_corso.ID_corso INNER JOIN tb_studente_corso_facoltativo ON tb_corso.ID_corso = tb_studente_corso_facoltativo.id_corso INNER JOIN tb_studente ON tb_studente_corso_facoltativo.matricola = tb_studente.Matricola;";
    sqlite3_stmt *pStmt;
    rc = sqlite3_prepare_v2(db, selezione_corso, -1, &pStmt, NULL);


     if ( rc != SQLITE_OK) {
        cout << "Impossibile creare statement" << endl;
        sqlite3_close (db);
        return (1);
    }
    cout << "Creato statement" << endl;
    // Recupera posizione per :NOME

    pos_par = sqlite3_bind_parameter_index(pStmt, ":NOME");
    cout << "Recuperato parametro" << endl;
    // Imposto valore parametro nome

    rc = sqlite3_bind_text(pStmt, pos_par,"Corso1",-1,NULL); // puntatore di qualsiasi tipo

    if (rc != SQLITE_OK) {
        cout << "Errore nella valorizzazione del parametro della query" << endl;

    }

    rc = sqlite3_step(pStmt);
    while (rc == SQLITE_ROW) {
        cout << "Recuperata riga di dati" << endl;
        cout << sqlite3_column_text (pStmt, 0) << endl;
        cout << sqlite3_column_int (pStmt, 1) << endl;
        cout << sqlite3_column_int (pStmt, 2) << endl;
        rc = sqlite3_step(pStmt);
    }
    if (rc == SQLITE_DONE) {
        cout << "Completata lettura dei dati della tabella" << endl;
    }
    else {
        cout << "Errore nell'accesso dei dati" << endl;
   } */

    const char *selezione_corso = "SELECT tb_studente.Matricola, tb_tutor.ID_tutor FROM tb_studente INNER JOIN tb_elenco_risorse_disponibili ON tb_studente.Matricola = tb_elenco_risorse_disponibili.matricola INNER JOIN tb_tutor ON tb_elenco_risorse_disponibili.id_tutor = tb_tutor.ID_tutor ";
    sqlite3_stmt *pStmt;
    rc = sqlite3_prepare_v2(db, selezione_corso, -1, &pStmt, NULL);

    rc = sqlite3_step(pStmt);
    while (rc == SQLITE_ROW) {
        cout << "Recuperata riga di dati" << endl;
        cout << sqlite3_column_text (pStmt, 0) << endl;
        cout << sqlite3_column_int (pStmt, 1) << endl;
        rc = sqlite3_step(pStmt);
    }
    if (rc == SQLITE_DONE) {
        cout << "Completata lettura dei dati della tabella" << endl;
    }
    else {
        cout << "Errore nell'accesso dei dati" << endl;
   }


    rc = sqlite3_finalize(pStmt);
    sqlite3_close (db);
    return (0);
}

int testa_db_elenca_argomenti () {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    int pos_par;

    rc = sqlite3_open ("./db/risorse_didattiche.db", &db);

    if ( rc != SQLITE_OK) {
        cout << "Can't open database" << endl;
        sqlite3_close (db);
        return (1);
    }
    cout << "aperto database" << endl;
    const char *selezione_corso = "SELECT tb_argomento.nome, tb_studente_corso_facoltativo.matricola, tb_studente_corso_facoltativo.id_corso FROM tb_argomento INNER JOIN tb_corso ON tb_argomento.id_corso = tb_corso.ID_corso INNER JOIN tb_studente_corso_facoltativo ON tb_corso.ID_corso = tb_studente_corso_facoltativo.id_corso INNER JOIN tb_studente ON tb_studente_corso_facoltativo.matricola = tb_studente.Matricola;";
    sqlite3_stmt *pStmt;
    rc = sqlite3_prepare_v2(db, selezione_corso, -1, &pStmt, NULL);


     if ( rc != SQLITE_OK) {
        cout << "Impossibile creare statement" << endl;
        sqlite3_close (db);
        return (1);
    }

    rc = sqlite3_step(pStmt);
    while (rc == SQLITE_ROW) {
        cout << "Recuperata riga di dati" << endl;
        cout << sqlite3_column_text (pStmt, 0) << endl;
        cout << sqlite3_column_int (pStmt, 1) << endl;
        cout << sqlite3_column_int (pStmt, 2) << endl;
        rc = sqlite3_step(pStmt);
    }
    if (rc == SQLITE_DONE) {
        cout << "Completata lettura dei dati della tabella" << endl;
    }
    else {
        cout << "Errore nell'accesso dei dati" << endl;
   }


    rc = sqlite3_finalize(pStmt);
    sqlite3_close (db);
    return (0);
}




int g (int b[], int size){

       for (int i = 0; i < size; ++i) {
         //   cout << b[i] << endl;
         cout << *(b + i) << endl;
    }
    return 0;
}
int main()
{
    /*
   int i = 1;
   int j = 2;
   int *p = &i;
   *p = 5;
   cout << i << endl;
   cout << p << endl;
   cout << *p <<endl;
   int a [] = {3, 7, 22};
   cout << a << endl;
   *a = 1;
   cout << a[0] << endl;
   cout << * (a + 1) << endl;
   cout << *a << endl;

   int b[] = {1, 2, 3, 4, 5};
    int size = 5;
    g(b, size);

    cout << "composito" << endl;
    cout << composito.a << endl;
    cout << composito.b << endl;
    cout << composito.c << endl;

    composito2.a = 10;
    cout << composito2.a << endl;

    composito3.c = 'h';
    cout << composito3.c << endl;

    return 0;
    */

    // return testa_db ();

    /* int a = 10;
    cout << "Valore di a prima della chiamata: " << a << endl;

    inc (a);

    cout << "Valore di a dopo la chiamata: " << a << endl;*/

    testa_db ();

    return 0;
}
