BEGIN TRANSACTION;
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
	FOREIGN KEY("id_corso ") REFERENCES "tb_corso"("ID_corso"),
	FOREIGN KEY("matricola") REFERENCES "tb_studente"("Matricola"),
	PRIMARY KEY("id_corso ","matricola")
);
CREATE TABLE IF NOT EXISTS "tb_tutor_argomento" (
	"id_argomenti"	INTEGER,
	"id_tutor"	INTEGER,
	FOREIGN KEY("id_argomenti") REFERENCES "tb_argomento"("ID_argomenti "),
	PRIMARY KEY("id_argomenti","id_tutor")
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
INSERT INTO "tb_corso" ("ID_corso","Nome","Anno_corso") VALUES (1,'ProvaCorso1',1),
 (2,'ProvaCorso2',2),
 (3,'ProvaCorso3',3);
INSERT INTO "tb_elenco_risorse_disponibili" ("ID_risorse","Tipo ","matricola","id_tutor") VALUES (1,'tipo1',1,1),
 (2,'tipo2',2,2),
 (3,'tipo3',3,3);
INSERT INTO "tb_argomento" ("ID_argomenti ","nome","id_corso") VALUES (1,'argomento1',1),
 (2,'argomento2',2),
 (3,'argomento3',3);
INSERT INTO "tb_risorsa_argomento" ("id_risorse","id_tutor") VALUES (1,1),
 (2,2),
 (3,3);
INSERT INTO "tb_risorsa_digitale" ("ID_digitale","Nome","Link","Approvata","id_risorse") VALUES (1,'nome1','link1','true',1),
 (2,'nome2','link2','false',2),
 (3,'nome3','link3','true',3);
INSERT INTO "tb_risorsa_fisica" ("ID_fisiche","Nome","Ubicazione","Approvata","Tipo","id_risorse") VALUES (1,'nome1','ubicazione1','true','tipo1',1),
 (2,'nome2','ubicazione2','false','tipo2',2),
 (3,'nome3','ubicazione3','true','tipo3',3);
COMMIT;
