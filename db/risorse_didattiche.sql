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
	PRIMARY KEY("id_corso","matricola"),
	FOREIGN KEY("id_corso") REFERENCES "tb_corso"("ID_corso")
);
CREATE TABLE IF NOT EXISTS "tb_risorsa_argomento" (
	"id_risorse"	INTEGER,
	"id_tutor"	INTEGER,
	PRIMARY KEY("id_risorse","id_tutor"),
	FOREIGN KEY("id_risorse") REFERENCES "tb_elenco_risorse_disponibili"("ID_risorse")
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
INSERT INTO "tb_studente_corso" ("id_corso ","matricola","classe","indirizzo") VALUES (1,1,'classe1','indirizzo1'),
 (2,2,'classe2','indirizzo2'),
 (3,3,'classe3','indirizzo3');
INSERT INTO "tb_tutor_argomento" ("id_argomenti","id_tutor") VALUES (1,1),
 (2,2),
 (3,3);
INSERT INTO "tb_studente_corso_facoltativo" ("id_corso","matricola") VALUES (1,1),
 (2,2),
 (3,3);
INSERT INTO "tb_risorsa_argomento" ("id_risorse","id_tutor") VALUES (1,1),
 (2,2),
 (3,3);
INSERT INTO "tb_risorsa_digitale" ("ID_digitale","Nome","Link","Approvata","id_risorse") VALUES (1,'nome1','link1','true',1),
 (2,'nome2','link2','false',2),
 (3,'nome3','link3','true',3);
INSERT INTO "tb_risorsa_fisica" ("ID_fisiche","Nome","Ubicazione","Approvata","Tipo","id_risorse") VALUES (1,'nome1','ubicazione1','true','tipo1',1),
 (2,'nome2','ubicazione2','false','tipo2',2),
 (3,'nome3','ubicazione3','true','tipo3',3);
INSERT INTO "tb_studente" ("Matricola","Nome","Cognome","mail_istituzionale","Data_nascita","Anno_corso","Lingua_scelta","Password") VALUES (1,'Studente1','Cognome1','mail1','01/01/01',1,'lingua1','password1'),
 (2,'Studente2','Cognome2','mail2','02/02/02',2,'lingua2','password2'),
 (3,'Studente3','Cognome3','mail3','03/03/03',3,'lingua3','password3');
INSERT INTO "tb_tutor" ("ID_tutor","Nome","Cognome","mail_interna","Password","Admin","Attivo","id_risorse") VALUES (1,'Tutor1','Cognome1','mail1','password1','true','true',1),
 (2,'Tutor2','Cognome2','mail2','password2','false','true',2),
 (3,'Tutor3','Cognome3','mail3','password3','false ','false',3);
COMMIT;
