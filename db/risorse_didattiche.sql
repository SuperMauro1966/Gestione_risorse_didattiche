BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS "tb_Corsi" (
	"ID_corso"	INTEGER NOT NULL,
	"Nome"	VARCHAR(50) NOT NULL UNIQUE,
	"Anno_corso"	INTEGER,
	PRIMARY KEY("ID_corso")
);
INSERT INTO "tb_Corsi" ("ID_corso","Nome","Anno_corso") VALUES (1,'''ProvaCorso1''',1),
 (2,'''ProvaCorso2''',2),
 (3,'''ProvaCorso3''',3);
CREATE INDEX IF NOT EXISTS "idx_tb_Corsi_Nome" ON "tb_Corsi" (
	"Nome"
);
CREATE VIEW vw_Corsi_Nome AS
SELECT Nome
FROM tb_Corsi;
COMMIT;
