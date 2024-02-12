BEGIN TRANSACTION;

DROP TABLE IF EXISTS "tb_corso";
DROP TABLE IF EXISTS "tb_elenco_risorse_disponibili";
DROP TABLE IF EXISTS "tb_argomento";
DROP TABLE IF EXISTS "tb_risorsa_digitale";
DROP TABLE IF EXISTS "tb_risorsa_fisica";
DROP TABLE IF EXISTS "tb_studente";
DROP TABLE IF EXISTS "tb_tutor";
DROP TABLE IF EXISTS "tb_studente_corso_facoltativo";
DROP TABLE IF EXISTS "tb_studente_corso";
DROP TABLE IF EXISTS "tb_tutor_argomento";
DROP TABLE IF EXISTS "tb_risorsa_argomento";

CREATE TABLE IF NOT EXISTS "tb_corso" (
	"ID_corso"	INTEGER,
	"Nome"	VARCHAR(30),
	"Anno_corso"	INTEGER,
	PRIMARY KEY("ID_corso")
);
CREATE TABLE IF NOT EXISTS "tb_elenco_risorse_disponibili" (
	"ID_risorse"	INTEGER,
	"Tipo "	VARCHAR(20),
	"matricola"	INTEGER,
	"id_tutor"	INTEGER,
	PRIMARY KEY("ID_risorse")
);
CREATE TABLE IF NOT EXISTS "tb_argomento" (
	"ID_argomenti "	INTEGER,
	"nome"	varchar(50),
	"id_corso"	INTEGER,
	PRIMARY KEY("ID_argomenti ")
);
CREATE TABLE IF NOT EXISTS "tb_studente_corso" (
	"id_corso "	INTEGER,
	"matricola"	INTEGER,
	"classe"	varchar(5) NOT NULL,
	"indirizzo"	varchar(15) NOT NULL,
	PRIMARY KEY("id_corso ","matricola"),
	FOREIGN KEY("matricola") REFERENCES "tb_studente"("Matricola"),
	FOREIGN KEY("id_corso ") REFERENCES "tb_corso"("ID_corso")
);
CREATE TABLE IF NOT EXISTS "tb_tutor_argomento" (
	"id_argomenti"	INTEGER,
	"id_tutor"	INTEGER,
	PRIMARY KEY("id_argomenti","id_tutor"),
	FOREIGN KEY("id_argomenti") REFERENCES "tb_argomento"("ID_argomenti ")
);
CREATE TABLE IF NOT EXISTS "tb_studente_corso_facoltativo" (
	"id_corso"	INTEGER,
	"matricola"	INTEGER,
	FOREIGN KEY("id_corso") REFERENCES "tb_corso"("ID_corso"),
	PRIMARY KEY("id_corso","matricola")
);
CREATE TABLE IF NOT EXISTS "tb_risorsa_argomento" (
	"id_risorse"	INTEGER,
	"id_tutor"	INTEGER,
	FOREIGN KEY("id_risorse") REFERENCES "tb_elenco_risorse_disponibili"("ID_risorse"),
	PRIMARY KEY("id_risorse","id_tutor")
);
CREATE TABLE IF NOT EXISTS "tb_risorsa_digitale" (
	"ID_digitale"	INTEGER,
	"Nome"	VARCHAR(30),
	"Link"	VARCHAR(100),
	"Approvata"	BOOL,
	"id_risorse"	INTEGER,
	PRIMARY KEY("ID_digitale")
);
CREATE TABLE IF NOT EXISTS "tb_risorsa_fisica" (
	"ID_fisiche"	INTEGER,
	"Nome"	VARCHAR(50),
	"Ubicazione"	VARCHAR(50),
	"Approvata"	BOOL,
	"Tipo"	VARCHAR(20),
	"id_risorse"	INTEGER,
	PRIMARY KEY("ID_fisiche")
);
CREATE TABLE IF NOT EXISTS "tb_studente" (
	"Matricola"	INTEGER,
	"Nome"	VARCHAR(50) NOT NULL,
	"Cognome"	VARCHAR(50) NOT NULL,
	"mail_istituzionale"	VARCHAR(30),
	"Data_nascita"	BLOB,
	"Anno_corso"	INTEGER,
	"Lingua_scelta"	VARCHAR(20),
	"Password"	VARCHAR(8),
	PRIMARY KEY("Matricola")
);
CREATE TABLE IF NOT EXISTS "tb_tutor" (
	"ID_tutor"	INTEGER,
	"Nome"	VARCHAR(50) NOT NULL,
	"Cognome"	VARCHAR(50) NOT NULL,
	"mail_interna"	VARCHAR(30) NOT NULL,
	"Password"	VARCHAR(8) NOT NULL,
	"Admin"	BOOL NOT NULL,
	"Attivo"	BOOL NOT NULL,
	"id_risorse"	INTEGER,
	PRIMARY KEY("ID_tutor","id_risorse")
);
COMMIT;
