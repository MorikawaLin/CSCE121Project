 
#include "Game_window.h"

Game_window::Game_window(Point xy, int w, int h, const string& title)
	:Window{ xy, w, h, title },
	lev{ 0 },
	final_score{ 0 },
	num_labels{2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	final_xs{350, 50, 150, 250, 350, 50, 150, 250, 350, 50, 150, 250, 350, 50, 150, 250},
	final_ys{450, 150, 150, 150, 150, 250, 250, 250, 250, 350, 350, 350, 350, 450, 450, 450},
	beginner{ Point{ 75, 50 }, 300, 100, "Beginner", cb_beg },
	intermediate{ Point{ 425, 50 }, 300, 100, "Intermediate", cb_inte },
	advanced{ Point{ 75, 250 }, 300, 100, "Advanced", cb_adv },
	expert{ Point{ 425, 250 }, 300, 100, "Expert", cb_expr },
	choose_difficulty{ Point{ 30, 450 }, 200, 100, "Choose Difficulty", cb_choose },
	show_rule{ Point{ 570, 450 }, 200, 100, "Read The Rules", cb_rule },
	back_to_menu{ Point{ 570, 450 }, 200, 100, "Go Back To Menu", cb_back },
	start_button{ Point{ 260, 430 }, 280, 140, "Start the Game!", cb_start },
	hint_button{ Point{ 0, 0 }, 70, 20, "HINT", cb_hint },
	play_again_button{ Point{ 570, 450 }, 200, 100, "Play Another Game", cb_back },
	final_quit_button{ Point{ 30, 450 }, 200, 100, "Quit The Game", cb_quit },
	quit_button{ Point{ x_max() - 70, 0 }, 70, 20, "Quit", cb_quit },
	shown_rules{false}
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

void Game_window::cb_hint(Address, Address pw)
{
	reference_to<Game_window>(pw).hint();
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

	if(shown_rules)
	{
		for(int i=0;i<rule_text.size();i++)
			detach(*rule_text[i]);
		shown_rules=false;
	}

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

	if(rule_text.size()==0)
	{
		String s1="How to Play: ";
		String s2="The game consists of a grid that holds 16 of boxes.";
		String s3="Each box has numbers positioned out of order.";
		String s4="The goal is to correct the order of numbers in as few moves as possible.";
		String s5="Move the pieces by clicking on the peice you would like to move.";
		String s6="You may not move a numbered peice into a flilled spot. ";
		String s7="Each block moved will be counted as one move.";
		String s8="Good luck!!!";

		Text* t1=new Text(Point(.35*x_max(),100),s1);
		t1->set_font_size(40);
		rule_text.push_back(t1);
		attach(*rule_text[0]);
	
		Text* t2=new Text(Point(.18*x_max(),150),s2);
		rule_text.push_back(t2);
		Text* t3=new Text(Point(.21*x_max(),175),s3);
		rule_text.push_back(t3);
		Text* t4=new Text(Point(.05*x_max(),200),s4);
		rule_text.push_back(t4);
		Text* t5=new Text(Point(.097*x_max(),225),s5);
		rule_text.push_back(t5);
		Text* t6=new Text(Point(.15*x_max(),250),s6);
		rule_text.push_back(t6);
		Text* t7=new Text(Point(.2*x_max(),275),s7);
		rule_text.push_back(t7);
		Text* t8=new Text(Point(.43*x_max(),300),s8);
		rule_text.push_back(t8);
	}
	
	shown_rules=true;

	attach(*rule_text[0]);
	for(int i=1;i<rule_text.size();i++)
	{
		rule_text[i]->set_font_size(20);
		attach(*rule_text[i]);
	}

	attach(back_to_menu);
	attach(choose_difficulty);
	attach(start_button);
	attach(quit_button);

	redraw();

}

void Game_window::back() {
	clear();

	if(shown_rules)
	{
		for(int i=0;i<rule_text.size();i++)
			detach(*rule_text[i]);
		shown_rules=false;
	}

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

		if (numbers.size() == 0) {
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
		}
		else {
			for (int i = 0; i < 16; ++i) {
				numbers[i].move(xs[i] - numbers[i].loc.x, ys[i] - numbers[i].loc.y);
			}
		}

		moves_remain = total_moves + 1;
		valid_label();

		for (int i = 0; i < 16; ++i) {
			attach(numbers[i]);
		}

		attach(hint_button);
		attach(quit_button);
	}

	//DetermineScoreRange(lev);

	redraw();
}

void Game_window::beg()
{
	lev = 1;
	total_moves = 10;
	xs = { 250, 50, 150, 250, 350, 50, 150, 350, 250, 50, 150, 350, 250, 50, 150, 350 };
	ys = { 350, 150, 150, 150, 150, 250, 250, 250, 450, 350, 350, 450, 250, 450, 450, 350 };
}

void Game_window::inte()
{	
	lev = 2;
	total_moves = 20;
	xs = { 150, 50, 250, 250, 350, 50, 150, 350, 350, 50, 150, 350, 250, 50, 250, 150 };
	ys = { 250, 150, 250, 150, 150, 250, 150, 350, 450, 350, 350, 250, 450, 450, 350, 450 };
}

void Game_window::adv()
{
	lev = 3;
	total_moves = 40;
}

void Game_window::expr()
{
	lev = 4;
	total_moves = 80;
	xs = {50, 350, 350, 50, 50, 250, 250, 150, 150, 350, 250, 250, 150, 350, 150, 50};
	ys = {150, 450, 350, 350, 450, 450, 350, 350, 450, 250, 250, 150, 150, 150, 250, 250};
}

void Game_window::valid_label() {
	correct_tiles = 0;

	for (int i = 0; i < 16; ++i) {
		if (abs(numbers[i].loc.x - numbers[0].loc.x) + abs(numbers[i].loc.y - numbers[0].loc.y) == 100) {
			num_labels[i] = 1;
		}
		else {
			num_labels[i] = 0;
		}

		if (numbers[i].loc.x == final_xs[i] && numbers[i].loc.y == final_ys[i]) {
			++correct_tiles;
		}
	}

	cout << "Moves Remain: " << --moves_remain << endl;
	cout << "Corect Tiles: " << correct_tiles << endl;
}

void Game_window::display_score() {
	clear();

	final_score = correct_tiles * total_moves;

	// FIX ME!!! DISPLAY IN WINDOW
	cout << "Your final score is " << final_score << endl;

	attach(play_again_button);
	attach(final_quit_button);

	redraw();
}

void Game_window::check_and_move(int k) {
	if (num_labels[k] == 0) {
		// FIX ME!!! DISPLAY IN WINDOW
		cout << "This is not a valid tile to move." << endl;
	}
	else if (num_labels[k] == 1) {
		/*for (int i = 1; i < 16; ++i) {
			if (num_labels[i] == 1) {
				colorPointer = numbers[i];
				colorPointer -> color(Color::invisible);
			}
		}*/
		int tempX = numbers[k].loc.x;
		int tempY = numbers[k].loc.y;
		numbers[k].move(numbers[0].loc.x - tempX, numbers[0].loc.y - tempY);
		numbers[0].move(tempX - numbers[0].loc.x, tempY - numbers[0].loc.y);
		valid_label();
	}
	/*else { // Blank Button
		for (int i = 1; i < 16; ++i) {
			if (num_labels[i] == 1) {
				colorPointer = numbers[i];
				colorPointer -> color(Color::yellow);
			}
		}
	}*/

	if (moves_remain == 0) {
		display_score();
	}
	else {
		redraw();
	}
}

int Game_window::dist_calc(int k) {
	return abs(numbers[k].loc.x - final_xs[0]) + abs(numbers[k].loc.y - final_ys[0]) +
		abs(numbers[0].loc.x - final_xs[k]) + abs(numbers[0].loc.y - final_ys[k]);
}

void Game_window::hint() {
	int suggestion;
	int min_dist = -1;

	for (int i = 1; i < 16; ++i) {
		if (num_labels[i] == 1) {
			if (min_dist == -1 || dist_calc(i) < min_dist) {
				min_dist = dist_calc(i);
				suggestion = i;
			}
		}
	}

	// FIX ME!!! DISPLAY IN WINDOW
	cout << "The recommended tile number is: " << suggestion << endl;
}

void Game_window::WriteFile()
{
	// FIX ME!!! WRITE NEW SCORE IN
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
	ifstream in;
	in.open(FILE_NAME);
	string x = "";
	while(in >> x) 
	{
		if(x == lim)
		{
			vector<Text*> text;
			Text* t = new Text(Point(505, 75), "HIGH SCORES");
			t -> set_font_size(40);
			Text* te = new Text(Point(555, 110), x);
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
				Text* t = new Text(Point(555, place), res);
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

string Game_window::DifficultyString(int l)
{
	switch(l)
	{
		case 1:
			return "Beginner";		
		case 2:
			return "Intermediate";
		case 3:
			return "Advanced"; 
		case 4:
			return "Expert";
		default:
			throw;	
	}

}

bool Game_window::CheckHighScores(int score, int lev)
{
	ifstream in;
	in.open(FILE_NAME);
	string diff = DifficultyString(lev);
	string x = "";
	while(in >> x) {
		if (x == diff) {
			for(int i = 0; i < 5; ++i)
			{
				in >> x >> x;
				if (stoi(x) < score) {
					return true;
				}
			}
			return false;
		}
	}
	return false;
}

void Game_window::NewHighScore()
{
	cout<<"1";
	In_box high(Point(x_max()*.5,y_max()*.5),40,200,"ENTER YOUR 3 CHAR INITIALS");
	cout<<"2";
	attach(high);
	cout<<"3";
	string initials=high.get_string();
	cout<<"4";
	cout<<initials;
	cout<<"5";
	//methodToGetRawScore();
}

void Game_window::quit()
{
	hide();
}

int main() {
	try {
		if (H112 != 201708L) {
			error("Error: incorrect std_lib_facilities_5.h version ", H112);
		}

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