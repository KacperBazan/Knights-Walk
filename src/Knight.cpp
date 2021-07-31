/* Member functions for the class "Knight". */

#include "Knight.hpp"
#include "Board.hpp"

using vec2_t = std::array<int, 2>;

/* Constructor */
Knight::Knight(int col, int row)
{
	m_pos[0] = col;
	m_pos[1] = row;
}


/* Returns true if a move is possible given the change in each direction. */
bool Knight::isMovePossible(int col_change, int row_change, Board& board)
{
	vec2_t newpos{ m_pos[0] + col_change, m_pos[1] + row_change };

	/* Check first if the new position is off the physical board. */
	if (newpos[0] < 0 || newpos[0] > board.cols() - 1 ||
		newpos[1] < 0 || newpos[1] > board.rows() - 1)
	{
		return false;
	}

	/* Then check if that spot has already been stepeed on. */
	if (board(newpos))
	{
		return false;
	}

	/*	If those tests fail, that means the move is on the board, and hasn't
		been stepped on previously. */
	return true;
}

/* Changes the knight's position and sets the square on the board to a stepped state. */
void Knight::move(int col_change, int row_change, Board& board)
{
	m_pos[0] += col_change;
	m_pos[1] += row_change;
	board.setState(m_pos, 1); // 1 = stepped.
}
/* The opposite of the move function. Returns the knight and reverts the squares state. */
void Knight::unmove(int col_change, int row_change, Board& board)
{
	board.setState(m_pos, 0); // 0 = un-stepped.
	m_pos[0] -= col_change;
	m_pos[1] -= row_change;
}

/* Set the position of the knight using a vector. */
void Knight::setPos(vec2_t pos)
{
	m_pos = pos;
}