#include "mainwin.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
Mainwin::Mainwin() : _store{Store("Raul's Java and Donut Joint")}
{

    //SET UP GUI
    set_default_size(600, 400);
    Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*vbox);

    //set up menu bar
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar());
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);

    //File
    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);
    //File: quit
    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_quit_click));
    filemenu->append(*menuitem_quit);

    //View
    Gtk::MenuItem *menuitem_view = Gtk::manage(new Gtk::MenuItem("_View", true));
    menubar->append(*menuitem_view);
    Gtk::Menu *viewmenu = Gtk::manage(new Gtk::Menu());
    menuitem_view->set_submenu(*viewmenu);
    //View: list products
    Gtk::MenuItem *menuitem_list = Gtk::manage(new Gtk::MenuItem("_List", true));
    menuitem_list->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_view_all_click));
    viewmenu->append(*menuitem_list);

    //Create new
    Gtk::MenuItem *menuitem_create = Gtk::manage(new Gtk::MenuItem("_Create", true));
    menubar->append(*menuitem_create);
    Gtk::Menu *createmenu = Gtk::manage(new Gtk::Menu());
    menuitem_create->set_submenu(*createmenu);
    //Create new: create coffee
    Gtk::MenuItem *menuitem_createcoffee = Gtk::manage(new Gtk::MenuItem("_Coffee", true));
    menuitem_createcoffee->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_create_coffee_click));
    createmenu->append(*menuitem_createcoffee);
    //Create new: create donut
    Gtk::MenuItem *menuitem_createdonut = Gtk::manage(new Gtk::MenuItem("_Donut", true));
    menuitem_createdonut->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_create_donut_click));
    createmenu->append(*menuitem_createdonut);

    vbox->show_all();
}

void Mainwin::on_quit_click()
{
    hide();
}
void Mainwin::on_view_all_click()
{
    std::string view_string = "List of Products from " + _store.name() + ":\n";
    for (int i{0}; i < _store.number_of_products(); i++)
        view_string += _store.product_to_string(i) + "\n";
    
    Gtk::MessageDialog *view_all = Gtk::manage(new Gtk::MessageDialog(view_string));
    view_all->set_transient_for(*this);
    view_all->run();
    view_all->close();
}
void Mainwin::on_create_coffee_click()
{
    std::vector<std::string> names{"Cappucino", "flat white", "Affogato", "Irish Coffee", "Caffe Mocha", "Long Black", "Latte", "Ristretto", "Doppio", "Espresso", "Caffe Americano", "Iced Coffee", "Turkish Coffee"}; //testing purposes
    std::vector<double> prices{5.13, 5.12, 4.11, 1.00, 14.23, 2.50, 3.29, 1.29, 10.00};
    std::vector<double> costs{2.32, 1.32, 2.00, 5.98, 3.23, 1.90, .50, 1.40};
    auto transformer = (new Java(names[rand() % names.size()], prices[rand() % prices.size()], costs[rand() % costs.size()], (rand() % 5) + 1));
    for (int i{0}; i < 10; ++i) //diversify some of the shots
    {
        switch (rand() % 5)
        {
        case (0):
            transformer->add_shot(Shot::None);
            break;
        case (1):
            transformer->add_shot(Shot::Chocolate);
            break;
        case (2):
            transformer->add_shot(Shot::Vanilla);
            break;
        case (3):
            transformer->add_shot(Shot::Peppermint);
            break;
        case (4):
            transformer->add_shot(Shot::Hazelnut);
            break;
        }
    }
    _store.add_product(transformer);
}
void Mainwin::on_create_donut_click()
{
    std::vector<std::string> names{
        "Bavarian Kreme-Filled Donut",
        "Chocolate Kreme-Filled Donut",
        "Blueberry Donut",
        "Apple-Crumb Donut",
        "Marble-Frosted Donut",
        "Jelly Donut",
        "Cinnamon-Sugar Donut",
        "Strawberry-Frosted Donut"}; //testing purposes
    std::vector<double> prices{5.13, 5.12, 4.11, 1.00, 14.23, 2.50, 3.29, 1.29, 10.00};
    std::vector<double> costs{2.32, 1.32, 2.00, 5.98, 3.23, 1.90, .50, 1.40};

    Frosting frosting;
    switch (rand() % 4)
    {
    case (0):
        frosting = Frosting::Unfrosted;
        break;
    case (1):
        frosting = Frosting::Chocolate_top;
        break;
    case (2):
        frosting = Frosting::Vanilla_top;
        break;
    case (3):
        frosting = Frosting::Pink_top;
        break;
    }
    Filling filling;
    switch (rand() % 4)
    {
    case (0):
        filling = Filling::Unfilled;
        break;
    case (1):
        filling = Filling::Creme;
        break;
    case (2):
        filling = Filling::Bavarian;
        break;
    case (3):
        filling = Filling::Strawberry;
        break;
    }
    bool sprinkles;
    switch (rand() % 2)
    {
    case (0):
        sprinkles = true;
        break;
    case (1):
        sprinkles = false;
        break;
    }
    auto transformer = (new Donut(names[rand() % names.size()], prices[rand() % prices.size()], costs[rand() % costs.size()], frosting, sprinkles, filling));
    _store.add_product(transformer);
}