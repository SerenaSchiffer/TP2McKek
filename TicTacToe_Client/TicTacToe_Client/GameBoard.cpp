#include "GameBoard.h"



GameBoard::GameBoard()
{
	cases = gcnew array<Symboles>(9);
	for (int i = 0; i < 9; i++)
		cases[i] = Symboles::vide;
}

void GameBoard::AddSymbole(int position, Symboles symb)
{
	cases[position - 1] = symb;
}

Symboles GameBoard::CheckWinner() // Return winning symbol or symbol::empty is no winner
{
	// Horizontal
	if (cases[0] == cases[1] && cases[0] == cases[2] && cases[0] != Symboles::vide)
		return cases[0];
	if (cases[3] == cases[4] && cases[3] == cases[5] && cases[3] != Symboles::vide)
		return cases[3];
	if (cases[6] == cases[7] && cases[6] == cases[8] && cases[6] != Symboles::vide)
		return cases[6];

	//Vertical
	if (cases[0] == cases[3] && cases[0] == cases[6] && cases[0] != Symboles::vide)
		return cases[0];
	if (cases[1] == cases[4] && cases[1] == cases[7] && cases[1] != Symboles::vide)
		return cases[1];
	if (cases[2] == cases[5] && cases[2] == cases[8] && cases[2] != Symboles::vide)
		return cases[2];

	//Diagonal
	if (cases[0] == cases[4] && cases[0] == cases[8] && cases[0] != Symboles::vide)
		return cases[0];
	if (cases[2] == cases[4] && cases[2] == cases[6] && cases[2] != Symboles::vide)
		return cases[2];

	//No Current Winner
	return Symboles::vide;
}

void GameBoard::ResetGame()
{
	for (int i = 0; i < 9; i++)
		cases[i] = Symboles::vide;
}

bool GameBoard::isDraw()
{
	for (int i = 0; i < 9; i++)
	{
		if (cases[i] == Symboles::vide)
			return false;
	}
	return true;
}