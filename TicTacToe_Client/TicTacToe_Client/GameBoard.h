#pragma once

public enum Symboles {
	vide,
	x,
	o
};

ref class GameBoard
{
public:
	array<int> ^cases;
	GameBoard();
	void AddSymbole(int position, Symboles symb);
};

