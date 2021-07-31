/* Member functions for the class "Board". */

#include "Board.hpp"
#include "Knight.hpp"
#include <cassert>	//for assert()

using vec2_t = std::array<int, 2>;

/* Constructor */
Board::Board(int cols, int rows)
	: m_cols{ cols }, m_rows{ rows }
{
	/* Dynamically create all boolean squares. */
	m_grid = new bool* [m_cols];
	for (size_t col = 0; col < m_cols; ++col)
	{
		m_grid[col] = new bool[m_rows];
	}

	/* Set each square to false (not stepped on). */
	for (size_t col = 0; col < m_cols; ++col)
	{
		for (size_t row = 0; row < m_rows; ++row)
			m_grid[col][row] = false;
	}
}

/* Set the state at pos to a particular boolean value. */
void Board::setState(vec2_t pos, bool b)
{
	m_grid[pos[0]][pos[1]] = b;
}

/* Returns the boolean state at pos. */
bool& Board::operator()(vec2_t pos)
{
	assert(pos[0] >= 0 && pos[0] < m_cols);
	assert(pos[1] >= 0 && pos[1] < m_rows);
	return m_grid[pos[0]][pos[1]];
}

/* Destructor */
Board::~Board()
{
	for (size_t col = 0; col < m_cols; ++col)
	{
		delete[] m_grid[col];
	}
	delete[] m_grid;
}