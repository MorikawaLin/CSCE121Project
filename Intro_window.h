#include "GUI.h"
#include "Graph.h"

struct Intro_window : Graph_lib::Window {
	Intro_window(Point xy, int w, int h, const string& title);
private:
	Button start_button;

	void start();
};
