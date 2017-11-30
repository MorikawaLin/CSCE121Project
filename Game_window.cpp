#include "Game_window.h"

Game_window::Game_window(Point xy, int w, int h, const string& title) //22
	:Window{ xy, w, h, title },
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
	enter_high{ Point{ 600, 240}, 70, 30, "Enter", cb_enter_high },
	high{Point{600,200},70,30,"ENTER YOUR INITIALS"}
{
	ShowTheTeam();
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

void Game_window::cb_enter_high(Address, Address pw)
{
	reference_to<Game_window>(pw).EnterScore();
}


void Game_window::clear() { //3
	for (int i = 0; i < children(); ++i) {
		child(i)->hide();
	}
}

void Game_window::ShowTheTeam() { //13
	shown_names=true;
	string s="Pengchuan Lin  Eraj Mohiuddin  Cody Maffucci";
	Text* t1=new Text(Point(200,200),"4x4 Square");
	Text* t2=new Text(Point(375,250),"By");
	Text* t3=new Text(Point(60,300),s);
	Text* t4=new Text(Point(345,350),"Team 32");
	t1->set_font_size(70);
	t2->set_font_size(20);
	t3->set_font_size(30);
	t4->set_font_size(20);
	names.push_back(t1);
	names.push_back(t2);
	names.push_back(t3);
	names.push_back(t4);
	for(int i=0;i<names.size();i++) 
		attach(*names[i]);
}

void Game_window::choose() { //13
	clear();

	removeRules();
	removeNames();
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

void Game_window::makeRules() { //21
	String s2 = "Each level consists of a grid that holds randomly positioned tiles.";
 	String s3 = "The goal is to correct the order of numbers in as few moves as possible.";
 	String s4 = "Tile colors: Green = correct. Red = incorrect. Yellow = possible move.";
 	String s5 = "Move pieces into blank by clicking on the intended tile. ";
 	String s6 = "You may not move a numbered tile into a numbered spot. ";
 	String s7 = "Each block moved will be counted as one move. Use 'Hint' to get help.";
 	String s8 = "Good luck!!!";
	Text* t2=new Text(Point(.097*x_max(),150),s2);
	rule_text.push_back(t2);
	Text* t3=new Text(Point(.05*x_max(),175),s3);
	rule_text.push_back(t3);
	Text* t4=new Text(Point(.073*x_max(),200),s4);
	rule_text.push_back(t4);
	Text* t5=new Text(Point(.15*x_max(),225),s5);
	rule_text.push_back(t5);
	Text* t6=new Text(Point(.135*x_max(),250),s6);
	rule_text.push_back(t6);
	Text* t7=new Text(Point(.06*x_max(),275),s7);
	rule_text.push_back(t7);
	Text* t8=new Text(Point(.43*x_max(),300),s8);
	rule_text.push_back(t8);
}

void Game_window::rule() { //21
	clear();
	removeNames();
	if(rule_text.size()==0) {
		String s1="How to Play: ";
		Text* t1=new Text(Point(.35*x_max(),100),s1);
		t1->set_font_size(40);
		rule_text.push_back(t1);
		attach(*rule_text[0]);
		makeRules();
	}
	shown_rules=true;
	attach(*rule_text[0]);
	for(int i=1;i<rule_text.size();i++) {
		rule_text[i]->set_font_size(20);
		attach(*rule_text[i]);
	}
	attach(back_to_menu);
	attach(choose_difficulty);
	attach(start_button);
	attach(quit_button);
	redraw();
}

void Game_window::removeRules() { //5
	if(shown_rules) {
		for(auto i: rule_text) //range based for and auto  features from c++11
			detach(*i);
		shown_rules=false;
	}
}

void Game_window::removeHighs() { //6
	if(shown_highs) {
		for(int i=0;i<highs.size();i++)
			detach(*highs[i]);
		shown_highs=false;
		highs.erase(highs.begin(),highs.end());
	}
}

void Game_window::removeNames() { //5
	if(shown_names)	{
		for(int i=0;i<names.size();i++)
			detach(*names[i]);
		shown_names=false;
	}
}

void Game_window::back() { //10
	clear();
	ShowTheTeam();
	removeRules();
	removeHighs();
	show_rule.move(570 - show_rule.loc.x, 0);
	attach(choose_difficulty);
	attach(show_rule);
	attach(start_button);
	attach(quit_button);
	redraw();
}

void Game_window::create_button() { //23
	if (!button_exist) {
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
		button_exist = true;
	}
	else {
		for (int i = 0; i < 16; ++i)
			numbers[i].move(xs[i] - numbers[i].loc.x, ys[i] - numbers[i].loc.y);
	}
}

void Game_window::fillStatics() { //12
	Text* hint=new Text(Point(50,50),"HINT");
	hint->set_font_size(20);
	statics.push_back(hint);
	Text* move_count=new Text(Point(500,400),"MOVE COUNTER");
	move_count->set_font_size(30);
	statics.push_back(move_count);
	Text* incorrect_count=new Text(Point(500,200),"INCORRECT TILES");
	incorrect_count->set_font_size(30);
	statics.push_back(incorrect_count);

	attach(*statics[0]);
	attach(*statics[1]);
	attach(*statics[2]);
}

void Game_window::start() { //16	
	removeNames();
	removeRules();
	fillStatics();
	clear();
	final_score = 0;
	moves_remain = total_moves + 1;
	create_button();
	move_counter.clear();
	fillMovesRemaining();
	fillIncorrects();
		for (int i = 0; i < 16; ++i)
			attach(numbers[i]);
	attach(hint_button);
	attach(quit_button);
	valid_label();
	redraw();
}

void Game_window::fillMovesRemaining() { //5
	for(int i=0;i<=total_moves;++i) {
		Text* move=new Text(Point(500,475),""+to_string(i));
		move->set_font_size(100);
		move_counter.push_back(move);
	}
}

void Game_window::fillIncorrects() { //5
	for(int i=1;i<=15;i++) {
		Text* incor=new Text(Point(500,275),""+to_string(i));
		incor->set_font_size(100);
		incorrects.push_back(incor);
	}
}
	
void Game_window::beg() { //19
	lev = 1;
	total_moves = 10;
	random_puzzle = rand() % 4 + 1;
	switch (random_puzzle) {
		case 1:
			xs = { 250, 50, 150, 250, 350, 50, 150, 350, 250, 50, 150, 350, 250, 50, 150, 350 };
			ys = { 350, 150, 150, 150, 150, 250, 250, 250, 450, 350, 350, 450, 250, 450, 450, 350 };
			break;
		case 2:
			xs = { 50, 150, 250, 250, 350, 50, 150, 150, 350, 50, 250, 350, 350, 50, 150, 250 };
			ys = { 350, 150, 150, 250, 150, 150, 350, 250, 250, 250, 350, 350, 450, 450, 450, 450 };
			break;
		case 3:
			xs = { 150, 50, 150, 250, 350, 50, 250, 250, 350, 150, 150, 50, 350, 50, 250, 350 };
			ys = { 250, 150, 150, 150, 150, 350, 250, 350, 250, 350, 450, 250, 350, 450, 450, 450 };
			break;
		case 4:
			xs = { 150, 50, 150, 250, 350, 50, 250, 250, 350, 50, 150, 350, 350, 150, 50, 250 };
			ys = { 250, 150, 150, 150, 150, 250, 250, 350, 250, 450, 350, 350, 450, 450, 350, 450 };
	}
}

void Game_window::inte() { //19
	lev = 2;
	total_moves = 20;
	random_puzzle = rand() % 4 + 1;
	switch (random_puzzle) {
		case 1:
			xs = { 150, 50, 250, 250, 350, 50, 150, 350, 350, 50, 150, 350, 250, 50, 250, 150 };
			ys = { 250, 150, 250, 150, 150, 250, 150, 350, 450, 350, 350, 250, 450, 450, 350, 450 };
			break;
		case 2:
			xs = { 250, 50, 250, 350, 350, 150, 150, 50, 150, 150, 250, 350, 350, 50, 50, 250 };
			ys = { 350, 250, 150, 150, 250, 150, 350, 150, 250, 450, 250, 350, 450, 350, 450, 450 };
			break;
		case 3:
			xs = { 250, 50, 50, 150, 350, 50, 150, 350, 350, 150, 250, 250, 350, 50, 250, 150 };
			ys = { 350, 150, 250, 150, 150, 350, 450, 250, 350, 350, 450, 150, 450, 450, 250, 250 };
			break;
		case 4:
			xs = { 50, 50, 250, 150, 350, 150, 50, 250, 250, 50, 150, 250, 350, 150, 350, 350 };
			ys = { 350, 150, 350, 150, 150, 350, 250, 150, 250, 450, 250, 450, 250, 450, 350, 450 };
	}
}

void Game_window::adv() { //19
	lev = 3;
	total_moves = 40;
	random_puzzle = rand() % 4 + 1;
	switch (random_puzzle) {
		case 1:
			xs = { 150, 250, 150, 50, 50, 250, 350, 250, 150, 50, 350, 350, 250, 50, 150, 350 };
			ys = { 250, 350, 350, 250, 150, 450, 450, 250, 150, 350, 350, 250, 150, 450, 450, 150 };
			break;
		case 2:
			xs = { 50, 50, 250, 250, 350, 50, 350, 150, 150, 50, 250, 350, 350, 150, 150, 250 };
			ys = { 150, 350, 250, 150, 150, 250, 450, 150, 250, 450, 450, 250, 350, 450, 350, 350 };
			break;
		case 3:
			xs = { 250, 350, 50, 350, 350, 250, 150, 50, 250, 150, 50, 350, 150, 150, 250, 50 };
			ys = { 350, 250, 250, 150, 350, 150, 150, 150, 450, 250, 350, 450, 450, 350, 250, 450 };
			break;
		case 4:
			xs = { 50, 150, 350, 350, 50, 50, 350, 250, 150, 250, 150, 150, 350, 250, 250, 50 };
			ys = { 350, 150, 250, 150, 250, 150, 350, 150, 350, 250, 450, 250, 450, 450, 350, 450 };
	}
}

void Game_window::expr() { //19
	lev = 4;
	total_moves = 80;
	switch (random_puzzle) {
		case 1:
			xs = { 50, 350, 350, 50, 50, 250, 250, 150, 150, 350, 250, 250, 150, 350, 150, 50 };
			ys = { 150, 450, 350, 350, 450, 450, 350, 350, 450, 250, 250, 150, 150, 150, 250, 250 };
			break;
		case 2:
			xs = { 50, 350, 350, 150, 50, 250, 250, 50, 150, 250, 250, 150, 150, 350, 350, 50 };
			ys = { 150, 450, 350, 450, 450, 450, 350, 350, 350, 150, 250, 250, 150, 150, 250, 250 };
			break;
		case 3:
			xs = { 50, 350, 350, 150, 50, 250, 250, 150, 150, 250, 250, 50, 150, 350, 350, 50 };
			ys = { 150, 450, 350, 450, 450, 450, 350, 350, 250, 150, 250, 350, 150, 150, 250, 250 };
			break;
		case 4:
			xs = { 50, 350, 350, 150, 50, 250, 250, 150, 50, 250, 350, 150, 150, 350, 250, 50 };
			ys = { 150, 450, 350, 350, 450, 450, 350, 450, 350, 250, 250, 250, 150, 150, 150, 250 };
	}
}

void Game_window::valid_label() { //23
	correct_tile = 0;
	incorrect_tile = 0;
	for (int i = 0; i < 16; ++i) {
		if (abs(numbers[i].loc.x - numbers[0].loc.x) + abs(numbers[i].loc.y - numbers[0].loc.y) == 100) {
			num_labels[i] = 1;
		}
		else {
			num_labels[i] = 0;
		}
		if (numbers[i].loc.x == final_xs[i] && numbers[i].loc.y == final_ys[i]) {
			++correct_tile;
			numbers[i].pw->color(Color::green);
		}
		else {
			++incorrect_tile;
			numbers[i].pw->color(fl_rgb_color(255,36,0)); 
		}
	}
	attach(*incorrects[incorrect_tile-2]);
	cout << "Number of correct tiles: " << correct_tile << endl; // GO ON SCREEN
	cout << "Number of incorrect tiles: " << incorrect_tile << endl; // GO ON SCREEN
	num_labels[0] = -1;
	--moves_remain;
	attach(*move_counter[moves_remain]);
}

void Game_window::dettachStatics() { //3
	detach(*statics[0]);
	detach(*statics[1]);
	detach(*statics[2]);
}

void Game_window::display_score() { //23
	clear();
	dettachStatics();
	for (int i = 0; i < 16; ++i) {
		if (numbers[i].loc.x == final_xs[i] && numbers[i].loc.y == final_ys[i]) 
			final_score += total_moves;
	}
	string x="Your final score is ";
	Text* score=new Text(Point(50,170),x);
	score->set_font_size(40);
	highs.push_back(score);
	Text* scores=new Text(Point(75,350),to_string(final_score)+"");
	scores->set_font_size(150);
	highs.push_back(scores);
	attach(*highs[0]);
	attach(*highs[1]);
	if(CheckHighScores(final_score,lev)>0) 
		NewHighScore();
	else 
		DrawScores(DifficultyString(lev));
	redraw();
}

void Game_window::dettachNums() { //4
	for(int i=0;i<move_counter.size();i++) 
		detach(*move_counter[i]);
	for(int i=0;i<incorrects.size();i++)
		detach(*incorrects[i]);
}

void Game_window::dettachStats() {
	for(int i=0;i<stats.size();i++)
		detach(*stats[i]);
	stats.erase(stats.begin(),stats.end());
}

void Game_window::check_and_move(int k) { //32 still too long and I will break it
	detach(*incorrects[incorrect_tile-2]);
	dettachStats();
	if (num_labels[k] == 0) {
		string x="This is not a valid tile to move.";
		Text* t=new Text(Point(100,100),x);
		t->set_font_size(30);
		stats.push_back(t);
		attach(*t);
	}
	else if (num_labels[k] == 1) {
		int tempX = numbers[k].loc.x;
		int tempY = numbers[k].loc.y;
		numbers[k].move(numbers[0].loc.x - tempX, numbers[0].loc.y - tempY);
		numbers[0].move(tempX - numbers[0].loc.x, tempY - numbers[0].loc.y);
		dettachNums();		
		valid_label();
	}
	else {
		for (int i = 1; i < 16; ++i) {
			if (num_labels[i] == 1) {
				numbers[i].pw->color(Color::yellow);
			}
		}
	}
	if (moves_remain == 0) {
		dettachNums();
		display_score();
	}
	else {
		detach(*move_counter[moves_remain-1]);
		redraw();
	}
}

int Game_window::dist_calc(int k) { //2
	return abs(numbers[k].loc.x - final_xs[0]) + abs(numbers[k].loc.y - final_ys[0]) +
		abs(numbers[0].loc.x - final_xs[k]) + abs(numbers[0].loc.y - final_ys[k]);
}

void Game_window::hint() { //19
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
	for(int i=0;i<stats.size();i++)
		detach(*stats[i]);
	stats.erase(stats.begin(),stats.end());
	string x="The recommended tile number is: "+to_string(suggestion);
	Text* t=new Text(Point(100,100),x);
	t->set_font_size(30);
	stats.push_back(t);
	attach(*t);
	redraw();
}

void Game_window::WriteFile() { //13
	ofstream o;
	o.open(FILE_NAME, ios::trunc);
	vector<string> diffs = {"Beginner", "Intermediate", "Advanced", "Expert"};
	for(int i = 0; i < 4; i++) {
		o<<diffs[i]<<endl;
		for(int j = 0; j < 5; ++j) {
			o<<"----"<<endl; //Dont add spaces. 
			o<<"----"<<endl;
		}
		o<<endl;
	}
	o.close();
}

void Game_window::DrawScores(string lim) { //21
	shown_highs=true;
	ifstream in(FILE_NAME);
	string x,one,two,res;
	while(in>>x) {
		if(x==lim) {
			addTheTop();
			int place = 200;
			for(int i = 0; i < 5; ++i) {
				in >> one >> two;
				res = one + "             " + two;
				Text* t = new Text(Point(420, place), res);
				t -> set_font_size(40);
				highs.push_back(t);
				place += 50;
			}
			for(int i = 2; i < highs.size(); ++i) 
				attach(*highs[i]);
		}
	}
	attach(play_again_button);
	attach(final_quit_button);
	redraw();
}

void Game_window::addTheTop() { //6
	Text* t = new Text(Point(350, 75), "HIGH SCORES");
	t -> set_font_size(60);
	Text* te = new Text(Point(450, 130), DifficultyString(lev));
	te -> set_font_size(50);
	highs.push_back(t);
	highs.push_back(te);
}

string Game_window::DifficultyString(int l) { //10
	switch(l) {
		case 1:
			return "Beginner";		
		case 2:
			return "Intermediate";
		case 3:
			return "Advanced"; 
		case 4:
			return "Expert";	
	}
}

int Game_window::CheckHighScores(int score, int lev) { //20
	ifstream in;
	in.open(FILE_NAME);
	string diff=DifficultyString(lev);
	string x="";
	while(in>>x) {
		if(x==diff) {
			for(int i=1;i<=5;i++) {
				in>>x>>x;
				int comp=atoi(x.c_str());
				if(comp<score) {
					in.close();
					return i;
				}
			}
			in.close();
			return -1;
		}
	}
	in.close();
	return -1;
}

void Game_window::NewHighScore() { //2
	attach(high);
	attach(enter_high);
}

void Game_window::EnterScore() { //24
	detach(high);
	detach(enter_high);
	string initials=high.get_string();
	int stop=CheckHighScores(final_score,lev);
	ifstream in(FILE_NAME);
	ofstream out("TEMP.txt");
	string diff=DifficultyString(lev);
	string x,y;
	while(in>>x) {
		if(x==diff) {
				out<<x<<endl;
			for(int i=1;i<=5;i++) {
				if(stop==i)
					out<<initials<<endl<<to_string(final_score)<<endl;
				else {
					in>>x>>y;
					out<<x<<endl<<y<<endl;
				}
			}
		}
		else
			out<<x<<endl;
	}
	makeTheSwitch();
}

void Game_window::makeTheSwitch() { //5
	rename("TEMP.txt","highScores.txt");
	std::remove("TEMP.txt");
	DrawScores(DifficultyString(lev));
	attach(play_again_button);
	attach(final_quit_button);
}

void Game_window::quit() { //1
	hide();
}

int main() { //15
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

