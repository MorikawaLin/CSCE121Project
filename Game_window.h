// This file is not complete!

// #include "Game_Difficulty.h"
#include "GUI.h"
#include "Graph.h"

struct Game_window : Graph_lib::Window {
	Game_window(Point xy, int w, int h, const string& title);
private:
	Vector_ref<Button> numbers;
	Button quit_button;

	const vector<string> num_labels;

	void check_and_move();
	void quit();
};
