#include "std_lib_facilities_5.h"
#include "Simple_window.h"
#include "Graph.h"
#include "FL/Fl_JPEG_Image.H"
#include "GUI.h"
#include "Window.h"



struct Difficulty : Graph_lib::Window
{
	Difficulty(Point xy,int width,int height,const string& title);
	int lev;
	vector<Buttons>
private:
	Button beginner;
	Button intermediate;
	Button advanced;
	Button expert;
	Button exit; //remove later

	static void cb_beg(Address, Address);
	void beg();
	static void cb_inte(Address, Address);
	void inte();
	static void cb_adv(Address, Address);
	void adv();
	static void cb_expr(Address, Address);
	void expr();
	static void cb_quit(Address, Address);
	void quit();


};

Difficulty::Difficulty(Point xy,int width,int height,const string& title)
	:Window{xy,width,height,title},
	lev{0},
	beginner{Point(100,100),300,100,"Beginner",cb_beg},
	intermediate{Point(100,250),300,100,"Intermediate",cb_inte},
	advanced{Point(100,400),300,100,"Advanced",cb_adv},
	expert{Point(100,550),300,100,"Expert",cb_expr},
	exit{Point(x_max()-50,10),40,40,"exit",cb_quit}
{	
	attach(beginner);
	attach(intermediate);
	attach(advanced);
	attach(expert);
	attach(exit);
}
void Difficulty::cb_beg(Address, Address pw)
{
	reference_to<Difficulty>(pw).beg();
}

void Difficulty::cb_inte(Address, Address pw)
{
	reference_to<Difficulty>(pw).inte();
}

void Difficulty::cb_adv(Address, Address pw)
{
	reference_to<Difficulty>(pw).adv();
}

void Difficulty::cb_expr(Address, Address pw)
{
	reference_to<Difficulty>(pw).expr();
}

void Difficulty::cb_quit(Address, Address pw)
{
	reference_to<Difficulty>(pw).quit();
}


void Difficulty::quit()
{
	delete beginner;
}

void Difficulty::beg()
{
	lev=1;
}

void Difficulty::inte()
{
	lev=2;
}

void Difficulty::adv()
{
	lev=3;
}	

void Difficulty::expr()
{
	lev=4;
}

int level(int lev)
{
	return lev;
}

int main()
try 
{
   Difficulty win(Point(100,200),800,800,"Choose your difficulty");
   return gui_main();

}
catch(exception& e) 
{
	cerr << "exception: " << e.what() << '\n';
	return 1;
}
catch (...) 
{
	cerr << "Some exception\n";
	return 2;
}

