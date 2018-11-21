#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include <gtkmm.h>
#include "store.h"
#include <regex>

class Mainwin : public Gtk::Window
{
public:
  Mainwin();
  //~Mainwin();

protected:
  void on_quit_click();
  void on_view_all_click();
  void on_create_order_click();
  void on_create_coffee_click();
  void on_create_donut_click();
  void on_create_customer_click();
  void on_list_customer_click();
  void on_view_order_click();
  void on_about_click();

  void on_fill_click();
  void on_pay_click();
  void on_discard_click();
private:
  Store _store;
  Gtk::Label *msg;
  Gtk::MenuItem *menuitem_new_coffee;
  Gtk::MenuItem *menuitem_new_donut;
};

#endif