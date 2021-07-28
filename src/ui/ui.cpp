#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>


#include <iostream>

void onPress(Fl_Widget *w, void *data){
  std::cout << "Pressed" << std::endl;
//  std::cout << (int) data[0] << std::endl;
}

int main(int argc, char **argv) {
  Fl_Window *window = new Fl_Window(340,180);
  auto g = new Fl_Group(0, 0, 340, 180, "Complex Resizing");
  Fl_Box *box = new Fl_Box(20,40,100,100,"Hello, World!");

  Fl_Button *but = new Fl_Button(140, 40, 100, 100, "Hello Aditya. I am "
                                                    "Computer.");

  g->add(box);
  g->add(but);

  but->when(FL_WHEN_RELEASE);
  int data = 1;
  but->callback(onPress, &data);

  box->box(FL_UP_BOX);
  box->labelfont(FL_BOLD+FL_ITALIC);
  box->labelsize(12);
  box->labeltype(FL_SHADOW_LABEL);
  window->resizable(g);

  window->end();
  window->show(argc, argv);
  return Fl::run();
}