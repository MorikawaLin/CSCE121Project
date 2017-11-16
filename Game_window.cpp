
#include "Game_window.h"

Game_window::Game_window(Point xy, int w, int h, const string& title)
	:Window{ xy, w, h, title },
	lev{ 0 },
	checked{ false },
	num_labels{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	beginner{ Point{ 75, 50 }, 300, 100, "Beginner", cb_beg },
	intermediate{ Point{ 425, 50 }, 300, 100, "Intermediate", cb_inte },
	advanced{ Point{ 75, 250 }, 300, 100, "Advanced", cb_adv },
	expert{ Point{ 425, 250 }, 300, 100, "Expert", cb_expr },
	choose_difficulty{ Point{ 30, 450 }, 200, 100, "Choose Difficulty", cb_choose },
	show_rule{ Point{ 570, 450 }, 200, 100, "Read The Rules", cb_rule },
	back_to_menu{ Point{ 570, 450 }, 200, 100, "Go Back To Menu", cb_back },
	start_button{ Point{ 260, 430 }, 280, 140, "Start the Game!", cb_start },
	quit_button{ Point{ x_max() - 70, 0 }, 70, 20, "Quit", cb_quit }/*,
	Out_box rule_text{ Point{ 0, 0 }, 600, 500, "How to Play:\n\n"
		"The game consists of a grid that holds a specific number of boxes depending on the difficulty chosen.\n"
	    "Each box has numbers positioned out of order except for one that is empty.\n"
		"The goal of the game is to correct the order of numbers by sliding boxes into the empty slot in as few moves as possible.\n"
		"You can move the pieces by clicking on the peice you would like to move and then clicking on the space you would like to move the selected piece to.\n"
		"You may not move a numbered peice into a flilled spot.\n"
		"Each block moved will be counted as a move.\n"
		"Good luck!!!"}
	*/
{
	attach(choose_difficulty);
	attach(start_button);
	attach(show_rule);
	attach(quit_button);
	
	WriteFile();
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
	//attach(rule_text);

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
	if (lev < 1 || lev > 4) {
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
	DetermineScoreRange(lev);
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

void Game_window::valid_label() {
	for (int i = 1; i < 16; ++i) {
		if (abs(numbers[i].loc.x + numbers[i].loc.y - numbers[0].loc.x - numbers[0].loc.y) == 100) {
			num_labels[i] = 1;
		}
		else {
			num_labels[i] = 0;
		}
	}
	checked = true;
}

void Game_window::check_and_move(int k) {
	if (!checked) {
		valid_label();
	}

	if (num_labels[k] == 0) {
		throw;
	}
	else if (num_labels[k] == 1) {
		/*
		for (int i = 1; i < 16; ++i) {
			if (num_labels[i] == 1) {
				numbers[i].set_fill_color(Color::invisible);
			}
		}
		*/
		int tempX = numbers[k].loc.x;
		int tempY = numbers[k].loc.y;
		numbers[k].move(numbers[0].loc.x - tempX, numbers[0].loc.y - tempY);
		numbers[0].move(tempX - numbers[0].loc.x, tempY - numbers[0].loc.y);
		checked = false;
	}
	/*
	else { // Blank Button

		for (int i = 1; i < 16; ++i) {
			if (num_labels[i] == 1) {
				numbers[i].set_fill_color(Color::yellow);
			}
		}
	}
	*/

	redraw();
}

void Game_window::WriteFile()
{
	ofstream o;
	o.open(FILE_NAME, ios::trunc);
	vector<string> diffs = {"Beginner", "Intermediate", "Advanced", "Expert"};
	for(int i = 0; i < 4; ++i)
	{
		o << diffs[i] << endl;
		for(int j = 0; j < 5; ++j)
		{
			o << "___" << endl;
			o << "____" << endl;
		}
		o << endl;
	}
	o.close();
}

void Game_window::DetermineScoreRange(int l)
{
	switch(l)
	{
		case 1:
			DrawScores("Beginner"); //fallthrough
			break;
		case 2:
			DrawScores("Intermediate"); //fallthrough
			break;
		case 3:
			DrawScores("Advanced"); //fallthrough
			break;
		case 4:
			DrawScores("Expert"); //fallthrough
			break;
		default:
			throw;
	}
}

void Game_window::DrawScores(String lim)
{
	cout << lim << endl;
	ifstream in;
	in.open(FILE_NAME);
	string x = "";
	while(in >> x) 
	{
		if(x == lim)
		{
			cout << x << endl;
			vector<Text*> text;
			Text* t = new Text( Point(505, 75), "HIGH SCORES");
			t -> set_font_size(40);
			Text* te = new Text( Point(555, 110), x);
			te -> set_font_size(30);
			text.push_back(t);
			text.push_back(te);
			string one = "";
			string two = "";
			string res = "";
			int place = 150;
			for(int i = 0; i < 5; ++i)
			{
				in >> one >> two;
				res = one + "              " + two;
				cout << res << endl;
				Text* t = new Text( Point(555, place), res);
				t -> set_font_size(20);
				text.push_back(t);
				place += 50;
			}
			for(int i = 0; i < text.size(); ++i)
			{
				attach(*text[i]);
			}
			break;
		}
	}
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
