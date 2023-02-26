#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Window.H>
#include <iostream>
char filename[256] = "";
Fl_Text_Buffer *textbuf = 0;

void save_file(char *newfile);
void saveas_cb();
void save_cb();
void load_cb();

void saveas_cb() {
  char *newfile;

  newfile = fl_file_chooser("Save File As?", "*", filename);
  if (newfile != NULL) {
    textbuf->savefile(newfile);
    strcpy(filename, newfile);
  }
};

void save_cb() {
  if (filename[0] == '\0') {
    saveas_cb();
  } else {
    textbuf->savefile(filename);
  }
};

void load_cb() {
  char *newfile = fl_file_chooser("Open File?", "*", filename);
  if (newfile != NULL) {
    textbuf->loadfile(newfile);
    strcpy(filename, newfile);
  }
};
class IDE {
public:
  Fl_Window *window;
  Fl_Menu_Bar *menubar;
  Fl_Text_Editor *texteditor;
  Fl_Box *box;

public:
  void init_default() {
    window = new Fl_Window(460, 320);

    window->begin();

    // menu bar
    Fl_Menu_Item menu_items[] = {{"&File", 0, 0, 0, FL_SUBMENU},
                                 {"Save", 0, (Fl_Callback *)save_cb},
                                 {"Load", 0, (Fl_Callback *)load_cb},
                                 {"Saveas", 0, (Fl_Callback *)saveas_cb},
                                 {0}};
    menubar = new Fl_Menu_Bar(0, 0, 340, 25);
    menubar->copy(menu_items);

    // file name label
    filename[0] = '\0';
    box = new Fl_Box(20, 40, 300, 100, filename);
    box->box(FL_UP_BOX);
    box->labelfont(FL_BOLD + FL_ITALIC);
    box->labelsize(36);
    box->labeltype(FL_SHADOW_LABEL);

    // text editor
    textbuf = new Fl_Text_Buffer();
    texteditor = new Fl_Text_Editor(20, 200, 300, 100);
    texteditor->buffer(textbuf);

    window->end();
    window->show();
  }
};

int main() {
  IDE ide;
  ide.init_default();
  return Fl::run();
}
