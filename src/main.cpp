/* Created by Kacper Bazan - bazankacper25@gmail.com */

#include <SFML/Graphics.hpp>
#include "MyConstants.hpp"
#include "Knight.hpp"
#include "Board.hpp"
#include <array>  //for std::array
#include <vector> //for std::vector

using vec2_t = std::array<int, 2>;

/* Global Path Variables. */
std::vector<vec2_t> chessboard_path{}; // Vector that holds pairs of integers Format: (Collumn, Row)
std::vector<sf::Vertex> vertex_path{}; // Vector that holds sf::Vertex's. Used to actually draw the knight's path.
sf::Vertex *vertex_start{}; // Pointer to the first element in the vertex_path. window.draw() needs this pointer.

/*	Recursive function that takes a knight, a board, and populates a path with a
	knight's path that traverses each square on the board. Does not find each path,
	and it will return the first such path it finds given the order of knight moves.
	*/
void KnightWalk(Knight &knight, Board &board, std::vector<vec2_t> &path)
{
	static bool found{false}; // Boolean that stops all calculation when a path is found.

	if (found) // If a complete path is found, stop further recursions.
		return;

	/*	Check if the knight can move to each of it's 8 usual squares. If it can, perform the knight's walk on those squares.
		Make sure to undo the move so that the board state is correct for each different branch. Each option is labeled with
		the possible knight moves. */
	if (knight.isMovePossible(-2, -1, board)) // Up 2, Left 1 [Option 0]
	{
		knight.move(-2, -1, board);
		path.push_back(knight.getPos());

		KnightWalk(knight, board, path);

		knight.unmove(-2, -1, board);
		path.pop_back();
	}
	if (knight.isMovePossible(-2, +1, board)) // Up 2, Right 1 [Option 1]
	{
		knight.move(-2, +1, board);
		path.push_back(knight.getPos());

		KnightWalk(knight, board, path);

		knight.unmove(-2, +1, board);
		path.pop_back();
	}
	if (knight.isMovePossible(-1, -2, board)) // Up 1, Left 2 [Option 2]
	{
		knight.move(-1, -2, board);
		path.push_back(knight.getPos());

		KnightWalk(knight, board, path);

		knight.unmove(-1, -2, board);
		path.pop_back();
	}
	if (knight.isMovePossible(-1, +2, board)) // Up 1, Right 2 [Option 3]
	{
		knight.move(-1, +2, board);
		path.push_back(knight.getPos());

		KnightWalk(knight, board, path);

		knight.unmove(-1, +2, board);
		path.pop_back();
	}
	if (knight.isMovePossible(+1, -2, board)) // Down 1, Left 2 [Option 4]
	{
		knight.move(+1, -2, board);
		path.push_back(knight.getPos());

		KnightWalk(knight, board, path);

		knight.unmove(+1, -2, board);
		path.pop_back();
	}
	if (knight.isMovePossible(+1, +2, board)) // Down 1, Right 2 [Option 5]
	{
		knight.move(+1, +2, board);
		path.push_back(knight.getPos());

		KnightWalk(knight, board, path);

		knight.unmove(+1, +2, board);
		path.pop_back();
	}
	if (knight.isMovePossible(+2, -1, board)) // Down 2, Left 1 [Option 6]
	{
		knight.move(+2, -1, board);
		path.push_back(knight.getPos());

		KnightWalk(knight, board, path);

		knight.unmove(+2, -1, board);
		path.pop_back();
	}
	if (knight.isMovePossible(+2, +1, board)) // Down 2, Right 1 [Option 7]
	{
		knight.move(+2, +1, board);
		path.push_back(knight.getPos());

		KnightWalk(knight, board, path);

		knight.unmove(+2, +1, board);
		path.pop_back();
	}

	if (path.size() == board.cols() * board.rows()) // If we travel to all the squares...
	{
		found = true; // ...no further calculation is needed...
		for (int i = 0; i < (int)path.size(); ++i)
		{
			chessboard_path.push_back(path[i]); //...set the global path to the found knight's path.
			if (i != 0)
				chessboard_path.push_back(path[i]);
		}
	}
}

int main()
{
	/* Make the window and set the Anti Aliasing level. */
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(Constants::screen_width, Constants::screen_height), "Knight's Path", sf::Style::Close, settings);

	bool noLoop{false}; // We only want to calculate the knight's path once, and then just draw it each frame.

	/* Entry for main loop */
	while (window.isOpen())
	{
		/* Checks if window is ever closed */
		sf::Event window_event{};
		while (window.pollEvent(window_event))
		{
			if (window_event.type == sf::Event::Closed)
				window.close();
		}

		/* Clears screen buffer to the background color. */
		window.clear(Constants::bg);

		/* Draw the actual chess board. */
		int cols{5}; // Number of vertical collumns.
		int rows{5}; // Number of horizontal rows.
		float w{(float)Constants::screen_width / ((float)cols + 1)}; // Width of each square using screen width and collumns.
		float h{(float)Constants::screen_height / ((float)rows + 1)}; // Height of each square using screen height and rows.

		for (int col = 1; col <= cols; ++col)
		{
			for (int row = 1; row <= rows; ++row)
			{
				sf::RectangleShape s{sf::Vector2f{w, h}}; // Create a chessboard square with width "w" and hegiht "h".
				s.setOrigin(sf::Vector2f{w / 2, h / 2});
				s.setPosition(col * w, row * h);

				if ((col * 9 + row) % 2 == 0)
					s.setFillColor(Constants::chess_white); // Set the chessboard square to white.
				else
					s.setFillColor(Constants::chess_green); // Set the chessboard square to green.
				window.draw(s);
			}
		}

		if (!noLoop) // The "noLoop" variable toggles true within this block.
		{
			Knight knight{0, 0}; // Knight starts on top left corner.
			Board board{cols, rows};
			std::vector<vec2_t> path{};
			board.setState(knight.getPos(), 1); // Starting square needs to be flagged "true".
			path.push_back(knight.getPos()); // Starting square needs to be added to the path.

			KnightWalk(knight, board, path); // Entry point for recursion.
			noLoop = true;

			/* For each chessboard square, find the correct (x,y) coordinates and add it to the vertex path. */
			for (size_t i = 0; i < chessboard_path.size(); i++)
			{
				sf::Vector2f new_pos{(chessboard_path[i][1] + 1) * w, (chessboard_path[i][0] + 1) * h};
				vertex_path.push_back(sf::Vertex(sf::Vector2f{new_pos.x, new_pos.y}, Constants::path_color));
			}
			vertex_start = &vertex_path[0]; // Set that vertex pointer to the first element in the vertex array.
		}

		window.draw(vertex_start, vertex_path.size(), sf::Lines);

		/* Render chessboard and lines to the screen. */
		window.display();
	}
	return 0;
}