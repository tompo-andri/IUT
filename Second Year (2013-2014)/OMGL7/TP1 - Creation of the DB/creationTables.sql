/* CANNO Camille
ANDRIAMILANTO Nampoina */


DROP TABLE Commande;
DROP TABLE Titre;
DROP TABLE Client;
DROP TABLE Categorie;
DROP TABLE Album;
DROP TABLE Pays;


CREATE TABLE Pays(
	IdPays INT(3) PRIMARY KEY AUTO_INCREMENT,
	Nom VARCHAR(20) NOT NULL
) ENGINE = INNODB;


CREATE TABLE Album(
	IdAlbum INT(5) PRIMARY KEY AUTO_INCREMENT,
	LibelleAlbum VARCHAR(30) NOT NULL
) ENGINE = INNODB;


CREATE TABLE Categorie(
	IdCategorie INT(2) PRIMARY KEY AUTO_INCREMENT,
	LibelleCategorie VARCHAR(20) NOT NULL
) ENGINE = INNODB;


CREATE TABLE Client(
	Login VARCHAR(20) PRIMARY KEY,
	Password VARCHAR(20) NOT NULL,
	Nom VARCHAR(20) NOT NULL,
	Prenom VARCHAR(20) NOT NULL,
	DateDeNaissance date NOT NULL,
	Email VARCHAR(20) NOT NULL,
	Adresse VARCHAR(20) NOT NULL,
	CodePostal INT NOT NULL,
	Ville VARCHAR(20) NOT NULL,
	IdPays INT NOT NULL,
	CONSTRAINT UQEmail UNIQUE(Email),
	CONSTRAINT CKEmail CHECK(Email LIKE '%@%'),
	CONSTRAINT CK2Email CHECK(Email NOT LIKE '@%'),
	CONSTRAINT CK3Email CHECK(Email NOT LIKE '%@'),
	CONSTRAINT FOREIGN KEY (IdPays) REFERENCES Pays(IdPays)
) ENGINE = INNODB;


CREATE TABLE Titre(
	IdTitre INT(3) PRIMARY KEY AUTO_INCREMENT,
	libelle VARCHAR(30) NOT NULL,
	Prix FLOAT(4, 2) NOT NULL,
	Artiste VARCHAR(20) NOT NULL,
	TitreAlbum INT NOT NULL,
	TitreCategorie INT NOT NULL,
	CONSTRAINT FOREIGN KEY (TitreAlbum) REFERENCES Album(IdAlbum),
	CONSTRAINT FOREIGN KEY (TitreCategorie) REFERENCES Categorie(IdCategorie)
) ENGINE = INNODB;


CREATE TABLE Commande(
	NumeroCommande INT AUTO_INCREMENT,
	ClientCommande VARCHAR(20),
	TitreCommande INT,
	Total FLOAT(4, 2) NOT NULL,
	PRIMARY KEY (NumeroCommande, ClientCommande, TitreCommande),
	CONSTRAINT FOREIGN KEY (ClientCommande) REFERENCES Client(Login),
	CONSTRAINT FOREIGN KEY (TitreCommande) REFERENCES Titre(IdTitre)
) ENGINE = INNODB;
