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
    //View: list customers
    Gtk::MenuItem *menuitem_list_customer = Gtk::manage(new Gtk::MenuItem("_Customer", true));
    menuitem_list_customer->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_list_customer_click));
    viewmenu->append(*menuitem_list_customer);

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
    //Create new: create customer
    Gtk::MenuItem *menuitem_createcustomer = Gtk::manage(new Gtk::MenuItem("_Customer", true));
    menuitem_createcustomer->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_create_customer_click));
    createmenu->append(*menuitem_createcustomer);
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
    Gtk::Dialog *dialog = Gtk::manage(new Gtk::Dialog("Create Java"));
    dialog->set_transient_for(*this);

    //name
    Gtk::HBox b_name;
    Gtk::Label l_name{"Name:"};
    l_name.set_width_chars(15);
    b_name.pack_start(l_name, Gtk::PACK_SHRINK);

    Gtk::Entry e_name;
    e_name.set_max_length(50);
    b_name.pack_start(e_name, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_name, Gtk::PACK_SHRINK);

    //price
    Gtk::HBox b_price;
    Gtk::Label l_price{"Price:"};
    l_price.set_width_chars(15);
    b_price.pack_start(l_price, Gtk::PACK_SHRINK);
    Gtk::Entry e_price;
    e_price.set_max_length(50);
    b_price.pack_start(e_price, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_price, Gtk::PACK_SHRINK);

    //cost
    Gtk::HBox b_cost;
    Gtk::Label l_cost{"Cost:"};
    l_cost.set_width_chars(15);
    b_cost.pack_start(l_cost, Gtk::PACK_SHRINK);
    Gtk::Entry e_cost;
    e_cost.set_max_length(50);
    b_cost.pack_start(e_cost, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_cost, Gtk::PACK_SHRINK);

    //darkness
    Gtk::ComboBoxText c_darkness;
    Gtk::HBox b_darkness;
    Gtk::Label l_darkness{"Darkness:"};
    l_darkness.set_width_chars(15);
    b_darkness.pack_start(l_darkness, Gtk::PACK_SHRINK);
    c_darkness.set_size_request(160);
    c_darkness.append("Blonde");
    c_darkness.append("Light");
    c_darkness.append("Medium");
    c_darkness.append("Dark");
    c_darkness.append("Extra Dark");
    b_darkness.pack_start(c_darkness, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_darkness, Gtk::PACK_SHRINK);

    dialog->add_button("Cancel", 0);
    dialog->add_button("OK", 1);
    dialog->show_all();

    std::regex pricer{"^[0-9]+\\.?[0-9]*$"};
    std::regex costr{"^[0-9]+\\.?[0-9]*$"};

    bool fail = true;
    int result;
    std::string name, price, cost;
    while (fail)
    {
        result = dialog->run();

        name = e_name.get_text();
        price = e_price.get_text();
        cost = e_cost.get_text();
        int darkness = c_darkness.get_active_row_number() + 1;
        if (result == 1 && name == "") //check name
            e_name.set_text("### INVALID ###");
        else if (result == 1 && !std::regex_match(price, pricer)) //check price
            e_price.set_text("### INVALID ###");
        else if (result == 1 && !std::regex_match(cost, costr)) //check cost
            e_cost.set_text("### INVALID ###");
        else
        {
            fail = false;
            if (result == 1)
            {
                double p = std::stod(price);
                double c = std::stod(cost);
                
                auto transformer = new Java(name, p, c, darkness);
                _store.add_product(transformer);
                
                //get shots
                Gtk::Dialog *shotty = Gtk::manage(new Gtk::Dialog("Add shots"));
                Gtk::ComboBoxText c_shotty;
                Gtk::HBox b_shotty;
                Gtk::Label l_shotty{"Shots:"};
                l_shotty.set_width_chars(15);
                b_shotty.pack_start(l_shotty, Gtk::PACK_SHRINK);
                c_shotty.set_size_request(160);
                c_shotty.append("None");
                c_shotty.append("Chocolate");
                c_shotty.append("Vanilla");
                c_shotty.append("Peppermint");
                c_shotty.append("Hazelnut");
                b_shotty.pack_start(c_shotty, Gtk::PACK_SHRINK);
                shotty->get_vbox()->pack_start(b_shotty, Gtk::PACK_SHRINK);

                shotty->add_button("Cancel", 0);
                shotty->add_button("Create", 1);
                shotty->add_button("Add", 2);
                shotty->show_all();

                int result_shot = 3;
                while (result_shot != 1 && result_shot != 0)
                {
                    result_shot = shotty->run();
                    int shot_selected = c_shotty.get_active_row_number();
                    switch (shot_selected)
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
                shotty->close();
            }
            dialog->close();
        }
    }
    
}
void Mainwin::on_create_donut_click()
{
    Gtk::Dialog *dialog = Gtk::manage(new Gtk::Dialog("Create Donut"));
    dialog->set_transient_for(*this);

    //name
    Gtk::HBox b_name;
    Gtk::Label l_name{"Name:"};
    l_name.set_width_chars(15);
    b_name.pack_start(l_name, Gtk::PACK_SHRINK);
    Gtk::Entry e_name;
    e_name.set_max_length(50);
    b_name.pack_start(e_name, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_name, Gtk::PACK_SHRINK);

    //price
    Gtk::HBox b_price;
    Gtk::Label l_price{"Price:"};
    l_price.set_width_chars(15);
    b_price.pack_start(l_price, Gtk::PACK_SHRINK);
    Gtk::Entry e_price;
    e_price.set_max_length(50);
    b_price.pack_start(e_price, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_price, Gtk::PACK_SHRINK);

    //cost
    Gtk::HBox b_cost;
    Gtk::Label l_cost{"Cost:"};
    l_cost.set_width_chars(15);
    b_cost.pack_start(l_cost, Gtk::PACK_SHRINK);
    Gtk::Entry e_cost;
    e_cost.set_max_length(50);
    b_cost.pack_start(e_cost, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_cost, Gtk::PACK_SHRINK);

    //Frosting
    Gtk::ComboBoxText c_frosting;
    Gtk::HBox b_frosting;
    Gtk::Label l_frosting{"Frosting:"};
    l_frosting.set_width_chars(15);
    b_frosting.pack_start(l_frosting, Gtk::PACK_SHRINK);
    c_frosting.set_size_request(160);
    c_frosting.append("Unfrosted");
    c_frosting.append("Chocolate top");
    c_frosting.append("Vanilla top");
    c_frosting.append("Pink top");
    b_frosting.pack_start(c_frosting, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_frosting, Gtk::PACK_SHRINK);

    //Filling
    Gtk::ComboBoxText c_filling;
    Gtk::HBox b_filling;
    Gtk::Label l_filling{"Body style:"};
    l_filling.set_width_chars(15);
    b_filling.pack_start(l_filling, Gtk::PACK_SHRINK);
    c_filling.set_size_request(160);
    c_filling.append("Unfilled");
    c_filling.append("Creme");
    c_filling.append("Bavarian");
    c_filling.append("Strawberry");
    b_filling.pack_start(c_filling, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_filling, Gtk::PACK_SHRINK);

    //sprinkles
    Gtk::CheckButton c_sprinkles{"Sprinkles"};
    dialog->get_vbox()->pack_start(c_sprinkles, Gtk::PACK_SHRINK);

    dialog->add_button("Cancel", 0);
    dialog->add_button("OK", 1);
    dialog->show_all();

    std::regex pricer{"^[0-9]+\\.?[0-9]*$"};
    std::regex costr{"^[0-9]+\\.?[0-9]*$"};

    bool fail = true;
    int result;
    std::string name, price, cost;
    while (fail)
    {
        result = dialog->run();

        name = e_name.get_text();
        price = e_price.get_text();
        cost = e_cost.get_text();
        if (result == 1 && name == "") //check name
            e_name.set_text("### INVALID ###");
        else if (result == 1 && !std::regex_match(price, pricer)) //check price
            e_price.set_text("### INVALID ###");
        else if (result == 1 && !std::regex_match(cost, costr)) //check cost
            e_cost.set_text("### INVALID ###");
        else
        {
            fail = false;
            if (result == 1)
            {
                Frosting frosting;
                double p = std::stod(price);
                double c = std::stod(cost);
                switch (c_frosting.get_active_row_number())
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
                switch (c_filling.get_active_row_number())
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
                bool sprinkles = c_sprinkles.get_active();
                auto transformer = new Donut(name, p, c, frosting, sprinkles, filling);
                _store.add_product(transformer);
            }
            dialog->close();
        }
    }
}
void Mainwin::on_create_customer_click()
{
    Gtk::Dialog *dialog = Gtk::manage(new Gtk::Dialog("Create customer"));
    dialog->set_transient_for(*this);

    //name
    Gtk::HBox b_name;
    Gtk::Label l_name{"Name:"};
    l_name.set_width_chars(15);
    b_name.pack_start(l_name, Gtk::PACK_SHRINK);

    Gtk::Entry e_name;
    e_name.set_max_length(50);
    b_name.pack_start(e_name, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_name, Gtk::PACK_SHRINK);

    //phone number
    Gtk::HBox b_num;
    Gtk::Label l_num{"Phone:"};
    l_name.set_width_chars(15);
    b_num.pack_start(l_num, Gtk::PACK_SHRINK);

    Gtk::Entry e_num;
    e_num.set_max_length(50);
    b_num.pack_start(e_num, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_num, Gtk::PACK_SHRINK);

    //buttons
    dialog->add_button("Cancel", 0);
    dialog->add_button("OK", 1);
    dialog->show_all();

    //check with regex
    std::regex reg{"\\d{3,3}-\\d{3,3}-\\d{4,4}"};
    bool fail = true;
    while (fail)
    {
        int result = dialog->run();
        std::string input = e_num.get_text();
        if (result == 1 && !std::regex_match(input, reg)) //check if phone number is same
            e_num.set_text("### INVALID ###");
        else
        {
            fail = false;
            dialog->close();
        }
    }
    std::string name = e_name.get_text(), num = e_num.get_text();
    Customer cust{name, num};
    _store.add_customer(cust);
}
void Mainwin::on_list_customer_click()
{
    std::string view_string = "List of Customers from " + _store.name() + ":\n";
    for (int i{0}; i < _store.number_of_customers(); i++)
        view_string += _store.customer_to_string(i) + "\n";
    Gtk::MessageDialog *view_all = Gtk::manage(new Gtk::MessageDialog(view_string));
    view_all->set_transient_for(*this);
    view_all->run();
    view_all->close();
}