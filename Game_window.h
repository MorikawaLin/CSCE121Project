#include "std_lib_facilities_5.h"
#include "FL/Fl_JPEG_Image.H"
#include "Simple_window.h"
#include "Window.h"
#include "Graph.h"
#include "GUI.h"

struct Game_window : public Graph_lib::Window
{
	Game_window(Point xy, int w, int h, const string& title);
	int level() { return lev; }
	const string FILE_NAME {"highScores.txt"};
	vector<Text*> rule_text;
	vector<Text*> highs;
	vector<Text*> stats;
	vector<Text*> statics;
	vector<Text*> move_counter;
	vector<Text*> names;

private:
	int lev {1};
	int total_moves;
	int moves_remain;
	int correct_tile {0};
	int incorrect_tile {0};
	int final_score {0};
	vector<int> num_labels {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	vector<int> xs;
	vector<int> ys;
	vector<int> final_xs {350, 50, 150, 250, 350, 50, 150, 250, 350, 50, 150, 250, 350, 50, 150, 250};
	vector<int> final_ys {450, 150, 150, 150, 150, 250, 250, 250, 250, 350, 350, 350, 350, 450, 450, 450};
	Vector_ref<Button> numbers;

	Button beginner;
	Button intermediate;
	Button advanced;
	Button expert;

	Button choose_difficulty;
	Button show_rule;
	Button back_to_menu;
	Button start_button;
	Button hint_button;
	Button play_again_button;
	Button final_quit_button;
	Button quit_button;
	Button enter_high;
	In_box high;

	bool shown_rules {false};
	bool shown_highs {false};
	bool shown_names {false};
	bool button_exist {false};

	void ShowTheTeam();
	void removeRules();
	void removeNames();
	void removeHighs();
	void clear();

	static void cb_choose(Address, Address);
	void choose();
	static void cb_rule(Address, Address);
	void rule();
	static void cb_back(Address, Address);
	void back();

	void create_button();
	static void cb_start(Address, Address);
	void start();

	static void cb_enter_high(Address, Address);
	void EnterScore();

	static void cb_beg(Address, Address);
	void beg();
	static void cb_inte(Address, Address);
	void inte();
	static void cb_adv(Address, Address);
	void adv();
	static void cb_expr(Address, Address);
	void expr();

	void valid_label();
	void display_score();
	void check_and_move(int);

	int dist_calc(int);
	static void cb_hint(Address, Address);
	void hint();

	void WriteFile();
	void DrawScores(String);
	void NewHighScore();
	string DifficultyString(int);
	int CheckHighScores(int,int);
	void makeTheSwitch();

	static void cb_quit(Address, Address);
	void quit();
};
