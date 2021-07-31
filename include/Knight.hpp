#pragma once
#include <array>
#include "Board.hpp"

class Board; // Forward declaration of the "Board" class.

using vec2_t = std::array<int, 2>;

class Knight
{
private:
	vec2_t m_pos{}; // The chessboard coordinates of the knight.

public:
	Knight(int col = 0, int row = 0);

	/* Checks if a move is possible. */
	bool isMovePossible(int col_change, int row_change, Board& board);

	/* Moves the knight and changes the state on the board. */
	void move(int col_change, int row_change, Board& board);

	/* Reverts the knight. Essentially the opposite of the move function. */
	void unmove(int col_change, int row_change, Board& board);

	void setPos(vec2_t pos);                      // Set knight's position.
	const vec2_t getPos() const { return m_pos; } // Return knight's position.
};