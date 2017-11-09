#include "std_lib_facilities_5.h"
#include "FL/Fl_JPEG_Image.H"
#include "Simple_window.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"

struct Game_window : Graph_lib::Window {
	Game_window(Point xy, int w, int h, const string& title);
	int level() { return lev; }
private:
	int lev;
	Vector<int> xs;
	Vector<int> ys;
	Vector_ref<Button> numbers;
	const vector<string> num_labels;

	Button beginner;
	Button intermediate;
	Button advanced;
	Button expert;

	Button choose_difficulty;
	Button show_rule;
	Button back_to_menu;
	Button start_button;
	Button quit_button;

	void clear();

	static void cb_choose(Address, Address);
	void choose();
	static void cb_rule(Address, Address);
	void rule();
	static void cb_back(Address, Address);
	void back();
	static void cb_start(Address, Address);
	void start();

	static void cb_beg(Address, Address);
	void beg();
	static void cb_inte(Address, Address);
	void inte();
	static void cb_adv(Address, Address);
	void adv();
	static void cb_expr(Address, Address);
	void expr();

	void check_and_move(int);

	static void cb_quit(Address, Address);
	void quit();
};

Game_window::Game_window(Point xy, int w, int h, const string& title)
	:Window{ xy, w, h, title },
	lev{ 0 },
	/*num_labels{ "", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"},*/
	choose_difficulty{ Point{ 30, 450 }, 200, 100, "Choose Difficulty", cb_choose },
	start_button{ Point{ 260, 430 }, 280, 140, "Start the Game!", cb_start },
	show_rule{ Point{ 570, 450 }, 200, 100, "Read The Rules", cb_rule },
	back_to_menu{ Point{ 570, 450 }, 200, 100, "Go Back To Menu", cb_back },
	beginner{ Point{ 75, 50 }, 300, 100, "Beginner", cb_beg },
	intermediate{ Point{ 425, 50 }, 300, 100, "Intermediate", cb_inte },
	advanced{ Point{ 75, 250 }, 300, 100, "Advanced", cb_adv },
	expert{ Point{ 425, 250 }, 300, 100, "Expert", cb_expr },
	quit_button{ Point{ x_max() - 70, 0 }, 70, 20, "Quit", cb_quit }
{
	attach(choose_difficulty);
	attach(start_button);
	attach(show_rule);
	attach(quit_button);
}

void Game_window::cb_choose(Address, Address pw)
{
	reference_to<Game_window>(pw).choose();
}

void Game_window::cb_rule(Address, Address pw)
{
	reference_to<Game_window>(pw).rule();
}

void Game_window::cb_back(Address, Address pw)
{
	reference_to<Game_window>(pw).back();
}

void Game_window::cb_start(Address, Address pw)
{
	reference_to<Game_window>(pw).start();
}

void Game_window::cb_beg(Address, Address pw)
{
	reference_to<Game_window>(pw).beg();
}

void Game_window::cb_inte(Address, Address pw)
{
	reference_to<Game_window>(pw).inte();
}

void Game_window::cb_adv(Address, Address pw)
{
	reference_to<Game_window>(pw).adv();
}

void Game_window::cb_expr(Address, Address pw)
{
	reference_to<Game_window>(pw).expr();
}

void Game_window::cb_quit(Address, Address pw)
{
	reference_to<Game_window>(pw).quit();
}

void Game_window::clear() {
	for (int i = 0; i < children(); ++i) {
		child(i)->hide();
	}
}

void Game_window::choose() {
	clear();

	attach(beginner);
	attach(intermediate);
	attach(advanced);
	attach(expert);

	show_rule.move(30 - show_rule.loc.x, 0);
	attach(back_to_menu);
	attach(show_rule);
	attach(start_button);
	attach(quit_button);

	redraw();
}

void Game_window::rule() {
	clear();

	attach(back_to_menu);
	attach(choose_difficulty);
	attach(start_button);
	attach(quit_button);

	redraw();
}

void Game_window::back() {
	clear();

	show_rule.move(570 - show_rule.loc.x, 0);
	attach(choose_difficulty);
	attach(show_rule);
	attach(start_button);
	attach(quit_button);

	redraw();
}

void Game_window::start() {
	if (lev == 0) {
		throw;
	}
	else {
		clear();

		/*for (int i = 0; i < 16; ++i) {
			numbers.push_back(new Button{ Point{ xs.at(i), ys.at(i) }, 100, 100, num_labels.at(i), [](Address, Address pw) {reference_to<Game_window>(pw).check_and_move();} });
			attach(numbers[numbers.size() - 1]);
		}*/

		numbers.push_back(new Button{ Point{ xs.at(0), ys.at(0) }, 100, 100, "", [](Address, Address pw) {reference_to<Game_window>(pw).check_and_move(0);} });
		numbers.push_back(new Button{ Point{ xs.at(1), ys.at(1) }, 100, 100, "1", [](Address, Address pw) {reference_to<Game_window>(pw).check_and_move(1);} });
		numbers.push_back(new Button{ Point{ xs.at(2), ys.at(2) }, 100, 100, "2", [](Address, Address pw) {reference_to<Game_window>(pw).check_and_move(2);} });
		numbers.push_back(new Button{ Point{ xs.at(3), ys.at(3) }, 100, 100, "3", [](Address, Address pw) {reference_to<Game_window>(pw).check_and_move(3);} });
		numbers.push_back(new Button{ Point{ xs.at(4), ys.at(4) }, 100, 100, "4", [](Address, Address pw) {reference_to<Game_window>(pw).check_and_move(4);} });
		numbers.push_back(new Button{ Point{ xs.at(5), ys.at(5) }, 100, 100, "5", [](Address, Address pw) {reference_to<Game_window>(pw).check_and_move(5);} });
		numbers.push_back(new Button{ Point{ xs.at(6), ys.at(6) }, 100, 100, "6", [](Address, Address pw) {reference_to<Game_window>(pw).check_and_move(6);} });
		numbers.push_back(new Button{ Point{ xs.at(7), ys.at(7) }, 100, 100, "7", [](Address, Address pw) {reference_to<Game_window>(pw).check_and_move(7);} });
		numbers.push_back(new Button{ Point{ xs.at(8), ys.at(8) }, 100, 100, "8", [](Address, Address pw) {reference_to<Game_window>(pw).check_and_move(8);} });
		numbers.push_back(new Button{ Point{ xs.at(9), ys.at(9) }, 100, 100, "9", [](Address, Address pw) {reference_to<Game_window>(pw).check_and_move(9);} });
		numbers.push_back(new Button{ Point{ xs.at(10), ys.at(10) }, 100, 100, "10", [](Address, Address pw) {reference_to<Game_window>(pw).check_and_move(10);} });
		numbers.push_back(new Button{ Point{ xs.at(11), ys.at(11) }, 100, 100, "11", [](Address, Address pw) {reference_to<Game_window>(pw).check_and_move(11);} });
		numbers.push_back(new Button{ Point{ xs.at(12), ys.at(12) }, 100, 100, "12", [](Address, Address pw) {reference_to<Game_window>(pw).check_and_move(12);} });
		numbers.push_back(new Button{ Point{ xs.at(13), ys.at(13) }, 100, 100, "13", [](Address, Address pw) {reference_to<Game_window>(pw).check_and_move(13);} });
		numbers.push_back(new Button{ Point{ xs.at(14), ys.at(14) }, 100, 100, "14", [](Address, Address pw) {reference_to<Game_window>(pw).check_and_move(14);} });
		numbers.push_back(new Button{ Point{ xs.at(15), ys.at(15) }, 100, 100, "15", [](Address, Address pw) {reference_to<Game_window>(pw).check_and_move(15);} });

		for (int i = 0; i < 16; ++i) {
			attach(numbers[i]);
		}

		attach(quit_button);
	}
	redraw();
}

void Game_window::beg()
{
	lev = 1;
	xs = { 250, 50, 150, 250, 350, 50, 150, 350, 250, 50, 150, 350, 250, 50, 150, 350 };
	ys = { 350, 150, 150, 150, 150, 250, 250, 250, 450, 350, 350, 450, 250, 450, 450, 350 };
}

void Game_window::inte()
{
	lev = 2;
	xs = { 150, 50, 250, 250, 350, 50, 150, 350, 350, 50, 150, 350, 250, 50, 250, 150 };
	ys = { 250, 150, 250, 150, 150, 250, 150, 350, 450, 350, 350, 250, 450, 450, 350, 450 };
}

void Game_window::adv()
{
	lev = 3;
}

void Game_window::expr()
{
	lev = 4;
}

void Game_window::check_and_move(int i) {
	// Check which button is clicked

	// If the blank button numbers.at(0) is clicked
	// Hightlight buttons that may move
	// Act as a hint button

	// Otherwise
	// Check valid moves for corresponding button
	// Move the button and the blank button

	redraw();
}

void Game_window::quit()
{
	hide();
}

int main() {
	try {
		if (H112 != 201708L)error("Error: incorrect std_lib_facilities_5.h version ",
			H112);

		Game_window win{ Point(200, 200), 800, 600, "Game" };

		return gui_main();
	}
	catch (exception& e) {
		cerr << "exception: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		cerr << "Some exception\n";
		return 2;
	}
}
