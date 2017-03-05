#pragma once

public enum Symboles {
	vide,
	x,
	o
};

ref class GameBoard
{
public:
	array<Symboles> ^cases;
	GameBoard();
	void AddSymbole(int position, Symboles symb);
	Symboles CheckWinner();
	void ResetGame();
	bool isDraw();
};

