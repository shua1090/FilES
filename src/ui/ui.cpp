#include<FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Bar.H>

#include <iostream>

void onPress(Fl_Widget *w, void *data){
  int * i = static_cast<int*>( data );
  std::cout << "Pressed " << *i << std::endl;
//  std::cout << (int) data[0] << std::endl;
}

int main(int argc, char **argv) {
  Fl_Window *window = new Fl_Window(340,180);
  Fl_Menu_Bar * men = new Fl_Menu_Bar(0, 0, 340, 20);
  window->end();
  Fl_Button *but = new Fl_Button(20,40,20,20,"Hello, World!");
  but->callback(onPress);

  int i = 1;

  men->add("File/Butter",0, onPress, (void*) &i);
  men->add("File/Test2", 0, onPress, (void*) &i);

  window->resizable(window);
  window->show(argc, argv);
  return Fl::run();
}