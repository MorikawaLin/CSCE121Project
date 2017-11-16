#include "std_lib_facilities_5.h"
#include "FL/Fl_JPEG_Image.H"
#include "Simple_window.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"

struct Game_window : Graph_lib::Window
{
	Game_window(Point xy, int w, int h, const string& title);
	int level() { return lev; }
	const string FILE_NAME{"HighScores.txt"};
private:
	int lev;
	bool checked;
	Vector<int> xs;
	Vector<int> ys;
	Vector_ref<Button> numbers;
	vector<int> num_labels;

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

	void valid_label();
	void check_and_move(int);

	static void cb_quit(Address, Address);
	void quit();

	void WriteFile();
	
	void DetermineScoreRange(int);
	void DrawScores(String);


};

