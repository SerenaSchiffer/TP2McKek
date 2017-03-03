#include "GameBoard.h"



GameBoard::GameBoard()
{
	cases = gcnew array<int>(9);
	for (int i = 0; i < 9; i++)
		cases[i] = Symboles::vide;
}

void GameBoard::AddSymbole(int position, Symboles symb)
{
	cases[position - 1] = symb;
}
