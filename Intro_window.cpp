#include "Intro_window.h"

Intro_window::Intro_window(Point xy, int w, int h, const string& title)
	:Window{ xy, w, h, title },
	start_button{ Point{ x_max() / 2 - 100, y_max() - 200 }, 200, 100, "Start the Game!", [](Address, Address pw) {reference_to<Intro_window>(pw).start();} }
{
	attach(start_button);
}

void Intro_window::start() {
	hide();
}