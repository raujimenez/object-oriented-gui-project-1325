#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include <gtkmm.h>
#include "store.h"

class Mainwin : public Gtk::Window
{
  public:
    Mainwin();
    ~Mainwin();

  protected:
    void on_quit_click();
    void on_view_all_click();
    void on_create_coffee_click();
    void on_create_donut_click();

  private:
    Store _store;
    Gtk::Label *msg;
    Gtk::MenuItem *menuitem_new_coffee;
    Gtk::MenuItem *menuitem_new_donut;
};

#endif