#include <iostream>
#include <sqlite3.h>

using namespace std;

struct dato_composito {
    int a = 0;
    float b = 3.14;
    char c = 'z';
} composito;

struct dato_composito composito2;

typedef struct dato_composito dato_composito;

dato_composito composito3;

void inc (int a){
    a = a+1;
}

int testa_db (){
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc; // contiene lo stato di ritorno
   int pos_par;
   rc = sqlite3_open("./db/risorse_didattiche.db", &db);

   if( rc != SQLITE_OK ){
    cout << "Can't open database:" << endl;
    sqlite3_close(db);
    return(1);
   }
   cout << "aperto database" << endl;
   /*
   const char *selezione_corso = "SELECT tb_argomento.nome, tb_studente_corso_facoltativo.matricola, tb_studente_corso_facoltativo.id_corso FROM tb_argomento INNER JOIN tb_corso ON tb_argomento.id_corso = tb_corso.ID_corso INNER JOIN tb_studente_corso_facoltativo ON tb_corso.ID_corso = tb_studente_corso_facoltativo.id_corso INNER JOIN tb_studente ON tb_studente_corso_facoltativo.matricola = tb_studente.Matricola;";
   sqlite3_stmt *pstmt;
   rc = sqlite3_prepare_v2(db, selezione_corso, -1, &pstmt, NULL);
*/

   /* if( rc != SQLITE_OK ){
    cout << "Impossibile creare statement:" << endl;
    sqlite3_close(db);
    return(1);
   }

   cout << "creato statement" << endl;
// recupera posizione per :NOME

    pos_par = sqlite3_bind_parameter_index(pstmt, ":NOME");
    cout << "Recuperato parametro" << endl;

// Imposto valore parametro nome

    rc = sqlite3_bind_text (pstmt, pos_par, "ProvaCorso1", -1, NULL); // puntatori di qualsiasi tipo che non ritorna niente

    if (rc != SQLITE_OK) {
        cout << "Errore nella valorizzazione del parametro della query" << endl;
         rc = sqlite3_finalize (pstmt);
         sqlite3_close(db);
    }*/

   /* rc = sqlite3_step (pstmt);
   while (rc == SQLITE_ROW){
    cout << "Recuperata riga di dati" << endl;
    cout << sqlite3_column_text (pstmt, 0) << endl;
    cout << sqlite3_column_int (pstmt, 1) << endl;
    cout << sqlite3_column_int (pstmt, 2) << endl;
    rc = sqlite3_step (pstmt);
   }
   if (rc == SQLITE_DONE) {
    cout << "Completata lettura dei dati della tabella" << endl;
   }
   else {
    cout << "Errore nell'accesso dei dati" << endl;
   } */

   const char *selezione_corso = "SELECT tb_studente.Matricola, tb_tutor.ID_tutor FROM tb_studente INNER JOIN tb_elenco_risorse_disponibili ON tb_studente.Matricola = tb_elenco_risorse_disponibili.matricola INNER JOIN tb_tutor ON tb_elenco_risorse_disponibili.id_tutor = tb_tutor.ID_tutor;";
   sqlite3_stmt *pstmt;
   rc = sqlite3_prepare_v2(db, selezione_corso, -1, &pstmt, NULL);

   rc = sqlite3_step (pstmt);
   while (rc == SQLITE_ROW){
    cout << "Recuperata riga di dati" << endl;
    cout << sqlite3_column_text (pstmt, 0) << endl;
    cout << sqlite3_column_int (pstmt, 1) << endl;
    rc = sqlite3_step (pstmt);
   }

   if (rc == SQLITE_DONE) {
    cout << "Completata lettura dei dati della tabella" << endl;
   }
   else {
    cout << "Errore nell'accesso dei dati" << endl;
   }

   rc = sqlite3_finalize (pstmt);
   sqlite3_close(db);
   return (0);

}

int testa_db_elenco_argomenti () {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc; // contiene lo stato di ritorno
   int pos_par;
   rc = sqlite3_open("./db/risorse_didattiche.db", &db);

   if( rc != SQLITE_OK ){
    cout << "Can't open database:" << endl;
    sqlite3_close(db);
    return(1);
   }
   cout << "aperto database" << endl;

   const char *selezione_corso = "SELECT tb_argomento.ID_argomenti, tb_argomento.nome As Nome_argomento, FROM tb_argomento INNER JOIN tb_corso ON tb_argomento.id_corso = tb_corso.ID_corso INNER JOIN tb_studente_corso_facoltativo ON tb_corso.ID_corso = tb_studente_corso_facoltativo.id_corso INNER JOIN tb_studente ON tb_studente_corso_facoltativo.matricola = tb_studente.Matricola;";
   sqlite3_stmt *pstmt;
   rc = sqlite3_prepare_v2(db, selezione_corso, -1, &pstmt, NULL);

   rc = sqlite3_step (pstmt);
   while (rc == SQLITE_ROW){
    cout << "Recuperata riga di dati" << endl;
    cout << sqlite3_column_int (pstmt, 1) << endl;
    cout << sqlite3_column_text (pstmt, 0) << endl;
    rc = sqlite3_step (pstmt);
   }

   if (rc == SQLITE_DONE) {
    cout << "Completata lettura dei dati della tabella" << endl;
   }
   else {
    cout << "Errore nell'accesso dei dati" << endl;
   }

   rc = sqlite3_finalize (pstmt);
   sqlite3_close(db);
   return (0);

}


int g (int b[], int size){
    for (int i = 0; i < size; i++) {
        cout << b [i] << endl;
    }
    return (0);
}
int main(){
    /*
    int i = 1;
    int j = 2;
    int *p = &i;
    *p = 5;
    cout << i<< endl;
    cout << p << endl;
    cout << *p << endl;
    int a [] = {3, 7, 22};
    cout << a << endl;
    *a = 1;
    cout << a[0] << endl;
    cout << * (a + 1) << endl;
    cout << *a << endl;

    int b [] = {1, 2, 3, 4, 5};
    int size = 5;
    g (b, size);

    cout << "composito" << endl;
    cout << composito.a << endl;
    cout << composito.b << endl;
    cout << composito.c << endl;

    composito2.a = 10;
    cout << composito 2.a << endl;

    composito3.c = 'h';
    cout << composito3.c << endl;

    return 0;
    */

  //  return testa_db ();

   /* int a = 10;
    cout << "valore di a prima della chiamata" << a << endl;

    inc (a);
    cout << "Valore di a dopo la chiamata: " << a << endl;
*/

    testa_db();
    testa_db_elenco_argomenti ();


    return 0;
}
