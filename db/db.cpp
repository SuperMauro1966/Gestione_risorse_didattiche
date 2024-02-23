#include <sqlite3.h>
#include <string>
#include <iostream>
#include <list>
#include "db.hpp"

using std::string;
using std::list;


sqlite3* GetConnessione(std :: string nome_db){
    static sqlite3 *db = NULL;
    int rc;
    if (db != NULL) {
        return db;
    }

    rc = sqlite3_open(reinterpret_cast<const char*>(nome_db.c_str()), &db);
    if (rc != SQLITE_OK){
        std :: clog << "Impossibile aprire database" << std :: endl;
        return nullptr;
    }
    return db;
}

void ChiudiConnessione (sqlite3* connessione) {
    std :: clog << "Chiuso database" << std :: endl;
    sqlite3_close (connessione);
}

// coppia che associa un nome di database ad una connessione
struct data_con {
    std:: string name;
    sqlite3 * con;
};

// dimensione massima del buffer delle connessioni che possiamo tenere aperte
const int MAX_SIZE = 10;

// definizione del buffer delle connessioni (puntatori alla coppia (nome, connessione)
struct data_con * map_con[MAX_SIZE] = {nullptr};

// connessioni già allocate nel buffer
static int n_con = 0;

sqlite3* ApriConnessioni(std :: string nome_db){
    // verifico se ho già aperto la connessione
    int pos = -1;

    // cerco la connessione con nome pari a nome_db tra quelle attuanmente memorizzate
    for (int i=0; i < MAX_SIZE; ++i) {
        if (map_con[i] != nullptr && map_con[i]->name == nome_db) { // (*map_con).name
            pos = i; // pos punta alla posizione all'interno del buffer della coppia (nome, connesione)
            break;
        }
    }

    int rc;
    sqlite3 * db;

    if (pos < 0) {
        // nessuna connessione con nome == nome_db trovata già aperta

        //verfico se ho abbastanza spazio per memorizzare la nuova coppia
        if((n_con+1) >= MAX_SIZE) {
            std::clog << "Numero massimo di connessioni raggiunto" << std::endl;
            return nullptr;
        }

        // spazio sufficiente - proseguo nell'apertura della connessione
        rc = sqlite3_open(reinterpret_cast<const char*>(nome_db.c_str()), &db);
        if (rc != SQLITE_OK){
            std :: clog << "Impossibile aprire database" << std :: endl;
            return nullptr;
        }

        struct data_con * named_con = new struct data_con; // creo in memoria una nuova variabile
        // imposto i valori
        named_con->con = db;
        named_con->name = nome_db;

        // cerco uno slot in cui andare a memorizzare il puntatore alla variabile
        for(int i = 0; i < MAX_SIZE; i++) {
            if (map_con[i] == nullptr) {
                map_con[i] = named_con;
            }
        }

        n_con++; // incremento il numero di connessioni attualmente presenti nel buffer
    }
    else // pos > 0 implica the abbiamo trovato la connessione precedentemente aperta
        db = map_con[pos]->con;

    return db;
}

std::list<CorsoArgomento> OttieniMaterieFacoltativeByMatricola() {
    std::list<CorsoArgomento> lista_corsi_argomenti;

    sqlite3 *db = GetConnessione("./db/risorse_didattiche.db");
    if (!db) {
        std::cerr << "Impossibile aprire il database" << std::endl;
        return lista_corsi_argomenti;
    }

    const char *query = "SELECT tb_argomento.nome FROM tb_argomento";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, query, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Impossibile preparare la query: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return lista_corsi_argomenti;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    const unsigned char* nome_c_str = sqlite3_column_text(stmt, 0);
    if (nome_c_str != nullptr) {
        CorsoArgomento corso;
        corso.nome = std::string(reinterpret_cast<const char*>(nome_c_str));
        lista_corsi_argomenti.push_back(corso);
    } else {
        std::cerr << "Il valore del nome restituito e nullo" << std::endl;
    }
}

    if (rc != SQLITE_DONE) {
        std::cerr << "Errore durante l'esecuzione della query: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return lista_corsi_argomenti;
}

std::list<RisorseArgomento> OttieniRisorseDisponibiliByMatricola() {
    std::list<RisorseArgomento> lista_risorse_disponibili;

    sqlite3 *db = GetConnessione("./db/risorse_didattiche.db");
    if (!db) {
        std::cerr << "Impossibile aprire il database" << std::endl;
        return lista_risorse_disponibili;
    }

    const char *query = "SELECT tb_argomento.nome, tb_elenco_risorse_disponibili.Tipo FROM tb_argomento INNER JOIN tb_corso ON tb_argomento.id_corso = tb_corso.ID_corso INNER JOIN tb_studente_corso ON tb_corso.ID_corso = tb_studente_corso.id_corso INNER JOIN tb_studente ON tb_studente_corso.matricola = tb_studente.Matricola INNER JOIN tb_elenco_risorse_disponibili ON tb_studente.Matricola = tb_elenco_risorse_disponibili.matricola WHERE tb_elenco_risorse_disponibili.matricola = :MATRICOLA;";
    sqlite3_stmt *pstmt;
    int rc = sqlite3_prepare_v2(db, query, -1, &pstmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Impossibile preparare la query: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return lista_risorse_disponibili;
    }

    while ((rc = sqlite3_step(pstmt)) == SQLITE_ROW) {
    const unsigned char* nome_c_str = sqlite3_column_text(pstmt, 0);
    if (nome_c_str != nullptr) {
        RisorseArgomento risorsa;
        risorsa.tipologia = std::string(reinterpret_cast<const char*>(nome_c_str));
        lista_risorse_disponibili.push_back(risorsa);
    } else {
        std::cerr << "Il valore del nome restituito e nullo" << std::endl;
    }
}

    if (rc != SQLITE_DONE) {
        std::cerr << "Errore durante l'esecuzione della query: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(pstmt);
    sqlite3_close(db);

    return lista_risorse_disponibili;
}

