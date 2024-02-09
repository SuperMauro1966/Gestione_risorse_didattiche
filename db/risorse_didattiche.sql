BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "Studenti" (
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
CREATE TABLE IF NOT EXISTS "Corsi" (
	"ID_corso"	INTEGER,
	"Nome"	VARCHAR(30),
	"Anno_corso"	INTEGER,
	PRIMARY KEY("ID_corso")
);
CREATE TABLE IF NOT EXISTS "Tutor" (
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
CREATE TABLE IF NOT EXISTS "Elenco_risorse_disponibili" (
	"ID_risorse"	INTEGER,
	"Tipo "	VARCHAR(20),
	"matricola"	INTEGER,
	"id_tutor"	INTEGER,
	PRIMARY KEY("ID_risorse")
);
CREATE TABLE IF NOT EXISTS "Risorse_digitali" (
	"ID_digitale"	INTEGER,
	"Nome"	VARCHAR(30),
	"Link"	VARCHAR(100),
	"Approvata"	BOOL,
	"id_risorse"	INTEGER,
	PRIMARY KEY("ID_digitale")
);
CREATE TABLE IF NOT EXISTS "Risorse_fisiche" (
	"ID_fisiche"	INTEGER,
	"Nome"	VARCHAR(50),
	"Ubicazione"	VARCHAR(50),
	"Approvata"	BOOL,
	"Tipo"	VARCHAR(20),
	"id_risorse"	INTEGER,
	PRIMARY KEY("ID_fisiche")
);
CREATE TABLE IF NOT EXISTS "Studenti-corsi-facoltativi" (
	"id_corso"	INTEGER,
	"matricola"	INTEGER,
	PRIMARY KEY("id_corso","matricola"),
	FOREIGN KEY("id_corso") REFERENCES "Corsi"("ID_corso")
);
COMMIT;
