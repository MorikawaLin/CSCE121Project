#include "std_lib_facilities_5.h"
#include "Simple_window.h"
#include "Graph.h"
#include "FL/Fl_JPEG_Image.H"
int main()
try {
  if(H112 != 201708L)error("Error: incorrect std_lib_facilities_5.h version ",
		  	   H112);
  Simple_window win1(Point(100,200),600,400,"two lines");

  /*Line horizontal(Point(100,100),Point(200,100));  // make a horizontal line
  Line vertical(Point(150,50),Point(150,150));     // make a vertical line
//  vertical.set_style(Line_style(Line_style::solid, 1));
  win1.attach(horizontal);
  win1.attach(vertical);
  vertical.set_color(Color::magenta);*/

  Rectangle left(Point{ 0,0 }, 200, 400);
  Rectangle top(Point{ 200,0 }, 400, 200);
  Rectangle bottom(Point{ 200,200 }, 400, 200);
  //Polygon star = {{50,100},{75,125},{100,125},{75,150},{100,200},{85,160},{25,}}

  win1.attach(left);
  win1.attach(top);
  win1.attach(bottom);

  left.set_color(Color::blue);
  top.set_color(Color::white);
  bottom.set_color(Color::red);


  win1.wait_for_button();
  return 0;
}
catch(exception& e) {
	cerr << "exception: " << e.what() << '\n';
	return 1;
}
catch (...) {
	cerr << "Some exception\n";
	return 2;
}
