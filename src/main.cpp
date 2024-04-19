#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_draw.h>
#include <FL/Fl_Input.H>

int main(int argc, char **argv) {
  Fl_Window *window = new Fl_Window(600,480, "Chinese Dictionary");

  // Results
  Fl_Box *leftPanel = new Fl_Box(0,0,200,480, "我\n叫\n東\n石");
  leftPanel->box(FL_UP_BOX);
  leftPanel->labelsize(18);
  leftPanel->labelfont(FL_BOLD+FL_ITALIC);
  leftPanel->labeltype(FL_SHADOW_LABEL);

  // Searchbar panel
  Fl_Input *searchBar = new Fl_Input(200,0,400,80, "我\n叫\n東\n石");
  searchBar->box(FL_UP_BOX);
  searchBar->labelsize(18);
  searchBar->labelfont(FL_BOLD+FL_ITALIC);
  searchBar->labeltype(FL_SHADOW_LABEL);
  searchBar->textsize(36);

  // Definition
  Fl_Box *definitionPanel = new Fl_Box(200,80,400,400, "我叫東石");
  definitionPanel->box(FL_UP_BOX);
  definitionPanel->labelsize(18);
  definitionPanel->labelfont(FL_BOLD+FL_ITALIC);
  definitionPanel->labeltype(FL_SHADOW_LABEL);

  window->end();
  window->show(argc, argv);

  std::cout<<"Hola mundo!";

  return Fl::run();
}
