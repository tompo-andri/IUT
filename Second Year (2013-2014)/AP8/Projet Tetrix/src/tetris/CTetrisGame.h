//========================================================================
// Projet C/C++
//
//------------------------------------------------------------------------
// Copyright (c) 2013-2014 Equipe SEASIDE (T. LE NAOUR, J.F KAMP)
// IRISA - UBS  / IUT Informatique Vannes
//========================================================================

#ifndef __CTETRIS_GAME_H__	// routine qui sert à �viter l'inclusion multiple
#define __CTETRIS_GAME_H__	//

#include "CPieceAbstract.h"
#include "CTGameTable.h"
#include "CRandomizer.h"
#include "TetrisUtils.h"
#include "CIPiece.h"
#include "CTPiece.h"
#include "COPiece.h"
#include "CL1Piece.h"
#include "CL2Piece.h"
#include "CZ1Piece.h"
#include "CZ2Piece.h"

class CTetrisGame {

public:
	/**
		\brief constructeur par défaut de la piece
	*/
	CTetrisGame() {;}

	/**
		\brief constructeur
	*/
	CTetrisGame ( unsigned int gamePosX, unsigned int gamePosY, unsigned int boardWidth, unsigned int boardHeight, float dimCase );

	/**
		\brief destructeur de CTetrisGame
	*/
	~CTetrisGame();

	/**
		\brief	met à jour le tetris en fonction du temps passà (le nombre de fois que la boucle de rendu est appelée)
				la méthode descend automatiquement la pièce courante
				check si collision, si ligne à détruire, le score et si game over
		\return l'état du jeu (ok ou game over)
	*/
	ActionResult Update(unsigned int step);

	/**
		\brief	modifie la position et l'orientation de la piece courante
		\param action à faire
		\return l'état du jeu (ok, collision ou game over)
	*/
	ActionResult MovePiece(PieceAction action);

	/**
		\brief renvoit le tableau du jeu avec les cases occupées et leur couleur
		\return le tableau du jeu
	*/
	CTGameTable& GetBoard();

	/**
		\brief renvoit position du jeu dans la fenêtre openGL
		\return entier en abcisse
	*/
	unsigned int GetXPos();

	/**
		\brief renvoit position du jeu dans la fenêtre openGL
		\return entier en ordonnée
	*/
	unsigned int GetYPos();

	/**
		\brief renvoit la taille d'une case du tetris
		\return entier sur la taille des cases
	*/
	float& GetCaseDim();

	/**
		\brief renvoit un pointeur sur la pièce courante
		\return poniteur sur CPieceAbstract
	*/
	CPieceAbstract* GetPiece();

	/**
		\brief renvoit le score courant
		\return entier > 0
	*/
	unsigned int GetScore();

	/**
		\brief collision avec autre objets dans la scene ?
	*/
	bool CheckCollision();


private:

	/**
		\brief ajout d'une piece aléatoire
	*/
	void AddPiece();



	/**
		\brief collision avec les bords du jeu ?
	*/
	bool CheckBorderCollision();

	/**
		\brief insertion de la piece courante dans le tableau de jeu
	*/
	void InsertPiece();

	/**
		\brief cherche la première ligne pleine
		\return index de la ligne pleine , -1 sinon !!!
	*/
	int GetFullRow();

	/**
		\brief supprime une ligne pleine
		\param index de la ligne pleine
	*/
	void DeleteRow(unsigned int rowIndex);

	/**
		\brief check si la partie est termin�e
		\return vrai si c'est le cas
	*/
	bool IsGameOver();

	/**
		\brief renvoit par un entier signà le nombre de colonne du tableau
		\return entier signà de la largeur du tableau
	*/
	int NbBoardCols();


	/**
		\brief renvoit par un entier signà le nombre de lignes du tableau
		\return entier signà de la largeur du tableau
	*/
	int NbBoardRows();


	//----------------------------------------------------------
	// données membres
	//----------------------------------------------------------
	CTGameTable		m_board				;	///< le tableau du jeu avec les cases occupées et leur couleur
	unsigned int	m_xPos				;	///< position en abcisse du jeu dans la fenêtre openGL
	unsigned int	m_yPos				;	///< position en ordonnée du jeu dans la fenêtre openGL
	float			m_caseDim			;	///< taille d'une case du tetris
	CRandomizer		m_randomizer		;   ///<
	CPieceAbstract*	m_pPiece			;	///< une pièce de type abstract
	unsigned int	m_dim				;	///< dimension de la piece
	unsigned int	m_score				;	///< score actuel du joueur
};

#endif
