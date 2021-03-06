//========================================================================
// Projet C/C++
//
//------------------------------------------------------------------------
// Copyright (c) 2013-2014 Equipe SEASIDE (T. LE NAOUR, J.F KAMP)
// IRISA - UBS  / IUT Informatique Vannes
//========================================================================

#include "CTetrisGame.h"

/****************************************/
CTetrisGame::CTetrisGame(unsigned int gamePosX, unsigned int gamePosY, unsigned int boardWidth, unsigned int boardHeight, float dimCase) {

	m_board = CTGameTable ( boardWidth, boardHeight );	// appel de CTGameTable ( int width, int height )
	m_xPos = gamePosX;
	m_yPos = gamePosY;
	m_caseDim = dimCase;
	m_pPiece = NULL;
	m_randomizer = CRandomizer (1, 7);

	//AddPiece();
}

/****************************************/


CTetrisGame::~CTetrisGame() {
	delete m_pPiece;
}


/****************************************/

CTGameTable& CTetrisGame::GetBoard() {

	return m_board;
}

/****************************************/

unsigned int CTetrisGame::GetXPos() {

	return m_xPos;
}

/****************************************/

unsigned int CTetrisGame::GetYPos() {

	return m_yPos;
}

/****************************************/

float& CTetrisGame::GetCaseDim()
{
	return m_caseDim;
}


void CTetrisGame::AddPiece() {

	if (m_pPiece == NULL) {

		srand(time(NULL));
		int tirage = (rand() %7);

		const CVector3 color(0.0f, 1.0f, 0.0f);


		switch (tirage)
		{
			case 0:
			{
				m_pPiece =  new CIPiece (3, 3, 17, color);
				m_pPiece -> Turn();
				break;
			}

			case 1:
			{
				m_pPiece = new CTPiece (3, 3, 17, color);
				m_pPiece -> Turn();
				break;
			}

			case 2:
			{
				m_pPiece = new COPiece (3, 3, 17, color);
				m_pPiece -> Turn();
				break;
			}

			case 3:
			{
				m_pPiece = new CL1Piece (3, 3, 17, color);
				m_pPiece -> Turn();
				break;
			}

			case 4:
			{
				m_pPiece = new CL2Piece (3, 3, 17, color);
				m_pPiece -> Turn();
				break;
			}

			case 5:
			{
				m_pPiece = new CZ1Piece (3, 3, 17, color);
				m_pPiece -> Turn();
				break;
			}

			case 6:
			{
				m_pPiece = new CZ2Piece (3, 3, 17, color);
				m_pPiece -> Turn();
			}
		}
	}

}


/**
	\brief Move a piece after an action of the user
	\param action The action that the user did
	\return An ActionResult object that show the result of the action
 */
ActionResult CTetrisGame::MovePiece(PieceAction action) {

	ActionResult ret = (ActionResult) NULL;

	switch (action)
	{
		case PA_RotateRight :
		{
			m_pPiece -> TurnRight ();
			m_pPiece -> Turn();
			break;
		}

		case PA_RotateLeft :
		{
			m_pPiece -> TurnLeft ();
			m_pPiece -> Turn();
			break;
		}

		case PA_MoveRight :
		{
			m_pPiece -> SetIncDecColIndex(1);
			m_pPiece -> Turn();
			break;
		}

		case PA_MoveLeft :
		{
			m_pPiece -> SetIncDecColIndex(-1);
			m_pPiece -> Turn();
			break;
		}

		case PA_MoveBottom :
		{
			m_pPiece -> SetIncDecRowIndex(-1);
			m_pPiece -> Turn();
			break;
		}

		case PA_MoveBottom2 :
		{
			m_pPiece -> SetIncDecRowIndex(-3);
			m_pPiece -> Turn();
		}

	}

	return ret;
}


/****************************************/

/**
	\brief Insert a piece when he can't going down anymore
**/
void CTetrisGame::InsertPiece() {
	//Get the piece, its table and its color
	TPieceTable& table = m_pPiece->GetTable();
	const CVector3& color = m_pPiece->GetColor();

	//Then gets its row and col index to know where it is
	int colId = m_pPiece->GetColIndex();
	int rowId = m_pPiece->GetRowIndex();

	//Then colors the case by
	//Getting the rows
	vector<TGameRow> rows = this->m_board.GetGameTable();

	//Here, will color all the cases of the piece
	for (int i = colId; i < 3; i++) {
		for (int j = rowId; j < 3; j++) {
			//If it's in the case table
			if (table[colId][rowId] == 1) {
				//Then gets the row of the piece
				vector<Case> pieceRow = rows[rowId];

				//Then gets the case from the row of the piece by its col
				Case c = pieceRow[colId];

				//Then colors it to the color of the piece and make it used
				c.m_color = color;
				c.m_used = true;
			}
		}
	}


	/*
	//Then gets the row of the piece
	vector<Case> pieceRow = rows[rowId];

	//Then gets the case from the row of the piece by its col
	Case c = pieceRow[colId];

	//Then colors it to the color of the piece and make it used
	c.m_color = color;
	c.m_used = true;
	*/
}

/****************************************/

/**
	\brief Search the first full line
	\return The index of this line, -1 if there's no one
**/
int CTetrisGame::GetFullRow() {
	//The var to know if he already found one or not and the index i
	bool found = false;
	unsigned int i = 0;

	//Gets the vector of game table
	vector<TGameRow> vect = this->m_board.GetGameTable();

	//Travels the board
	while ((!(found)) && (i < vect.size())) {
		//Var to store a bool to know if the line is full
		bool lineFull = true;

		//Gets rows one by one
		vector<Case> aRow = vect[i];

		//Then gets cases one by one
		for (unsigned int j = 0; j < aRow.size(); j++) {

			//If a case is empty, so the line isn't full
			if (!(aRow[j].m_used)) {
				lineFull = false;
			}
		}

		//If the row is full
		if (lineFull) {
			found = true;
		}

		//If it isn't
		else {
			//Increments i
			i++;
		}
	}

	//If we didn't found a full row
	if (!(found)) {
		i = -1;
	}

	return i;
}


/****************************************/

/**
	\brief Delete a full row then moving all the rows upper than it
	\param The index of this row
*/
void CTetrisGame::DeleteRow(unsigned int rowIndex) {
	//Gets the vector of game table
	vector<TGameRow> vect = this->m_board.GetGameTable();

	//Gets the high of this board
	unsigned int boardHeight = this->NbBoardRows();

	//Value to increment
	unsigned int i = 0;

	//Move all the upper rows
	while ((i + rowIndex) < (boardHeight - 1)) {
		vect[rowIndex + i] = vect[rowIndex + i + 1];
	}

	//Then, clean the last row (= the highest)
	//Create a blank row
	Case c = Case();
	int nbCols = this->NbBoardCols();
	TGameRow aRow (nbCols, c);

	//Then put it in the highest row
	vect[boardHeight - 1] = aRow;
}


/****************************************/

/**
	\brief Check if the game is over
	\return true if over, false if not
*/
bool CTetrisGame::IsGameOver() { //Peut être à revoir
	bool ret = false;

	//Gets the row index of the piece
	int rowIndex = this->m_pPiece->GetRowIndex();

	//Gets the height of the board
	int nbBoardRows = this->NbBoardRows();

	//Then look if it's upper than the size of the board
	if (rowIndex >= nbBoardRows) {
		ret = true;
	}

	return ret;
}


/****************************************/

/**
	\brief Get the number of colons
	\return A signed int of the width of the table
*/
int CTetrisGame::NbBoardCols() {
	int ret = 0;

	//Gets the vector of game table
	vector<TGameRow> vect = this->m_board.GetGameTable();

	//Then gets a single row (here it's the first one)
	vector<Case> singleRow = vect[0];

	//And gets its number of cases (so it's width)
	ret = singleRow.size();

	return ret;
}


/****************************************/

/**
	\brief Get the number of rows
	\return A signed int of the high of the table
*/
int CTetrisGame::NbBoardRows() {
	int ret = 0;

	//Gets the vector of game table
	vector<TGameRow> vect = this->m_board.GetGameTable();

	//Then gets its size (so the high of the board)
	ret = vect.size();

	//Then returns the result
	return ret;
}


/****************************************/

/**
	\brief Get the current piece
	\return A pointer to the current piece
*/
CPieceAbstract* CTetrisGame::GetPiece() {
	return this->m_pPiece;
}


/****************************************/

/**
	\brief Get the current score
	\return A pointer to the current piece
*/
unsigned int CTetrisGame::GetScore() {
	return this->m_score;
}


ActionResult CTetrisGame::Update(unsigned int step) {

	if (step == 0) {
		this->AddPiece();
	}


	return AR_Ok;
}

bool CTetrisGame::CheckCollision() {
	bool checkcol = false;
	int row = m_pPiece -> GetRowIndex();
	if (row < -1) {
		m_pPiece -> SetRowIndex(-1);
		checkcol = true;
	}
	if (this -> CheckBorderCollision() == true) {
		checkcol = true;
	}

	return checkcol;
}

bool CTetrisGame::CheckBorderCollision() {
	bool checkbordercol = false;
	int col = m_pPiece -> GetColIndex();
	if (col < -1) {
		m_pPiece -> SetColIndex(-1);
		checkbordercol = true;
	}
	if (col > 8) {
		m_pPiece -> SetColIndex(8);
		checkbordercol = true;
	}

	return checkbordercol;
}
