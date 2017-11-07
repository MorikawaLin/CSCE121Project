// This file is not complete!

#include "Game_window.h"

Game_window::Game_window(Point xy, int w, int h, const string& title)
	:Window{ xy, w, h, title },
	quit_button{ Point{ x_max() - 70, 0 }, 70, 20, "Quit", [](Address, Address pw) {reference_to<Game_window>(pw).quit();} }
{
	num_labels.push_back("");
	for (int i = 0; i < 16; ++i) {
		if (i != 0) {
			num_labels.push_back(to_string(i));
		}
		// xs and ys comes from Game_Difficulty.h
		numbers.push_back(new Button{ Point{ xs.at(i), ys.at(i) }, 100, 100, num_labels.at(i), [](Address, Address pw) {reference_to<Game_window>(pw).check_and_move();} });
		attach(numbers.at(numbers.size() - 1);
	}

	attach(quit_button);
}

void Game_window::quit() {
	hide();
}

void Game_window::check_and_move() {
	// Check which button is clicked

	// If the blank button numbers.at(1) is clicked
	// Hightlight buttons that may move
	// Act as a hint button
	
	// Otherwise
	// Check valid moves for corresponding button
	// Move the button and the blank button

	redraw();
}