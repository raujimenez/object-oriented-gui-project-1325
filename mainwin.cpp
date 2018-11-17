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
    //View: list orders
    Gtk::MenuItem *menuitem_list_orders = Gtk::manage(new Gtk::MenuItem("_Orders", true));
    menuitem_list_orders->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_view_order_click));
    viewmenu->append(*menuitem_list_orders);

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
    //Create new: create order
    Gtk::MenuItem *menuitem_createorder = Gtk::manage(new Gtk::MenuItem("_Order", true));
    menuitem_createorder->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_create_order_click));
    createmenu->append(*menuitem_createorder);

    //Help
    Gtk::MenuItem *menuitem_help = Gtk::manage(new Gtk::MenuItem("_Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);
    //Help: about
    Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("_About", true));
    menuitem_about->signal_activate().connect(sigc::mem_fun(*this, &Mainwin::on_about_click));
    helpmenu->append(*menuitem_about);

    Gtk::Image *p_list = Gtk::manage(new Gtk::Image("p_list.png"));
    Gtk::Image *list = Gtk::manage(new Gtk::Image("list.png"));
    Gtk::Image *donut = Gtk::manage(new Gtk::Image("donut.png"));
    Gtk::Image *java = Gtk::manage(new Gtk::Image("coffee.png"));
    Gtk::Image *customer = Gtk::manage(new Gtk::Image("customer.png"));

    //toolbar
    Gtk::Toolbar *toolbar = Gtk::manage(new Gtk::Toolbar());
    vbox->add(*toolbar);

    //list products
    Gtk::ToolButton *listproduct = Gtk::manage(new Gtk::ToolButton(*p_list));
    listproduct->set_tooltip_markup("List of all Products");
    listproduct->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_view_all_click));
    toolbar->append(*listproduct);
    //add java
    Gtk::ToolButton *addjava = Gtk::manage(new Gtk::ToolButton(*java));
    addjava->set_tooltip_markup("Create Coffee");
    addjava->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_create_coffee_click));
    toolbar->append(*addjava);
    //add coffee
    Gtk::ToolButton *adddonut = Gtk::manage(new Gtk::ToolButton(*donut));
    adddonut->set_tooltip_markup("Create Donut");
    adddonut->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_create_donut_click));
    toolbar->append(*adddonut);
    //list customers
    Gtk::ToolButton *listcustomer = Gtk::manage(new Gtk::ToolButton(*list));
    listcustomer->set_tooltip_markup("List Customers");
    listcustomer->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_list_customer_click));
    toolbar->append(*listcustomer);
    //Create customers
    Gtk::ToolButton *addcustomer = Gtk::manage(new Gtk::ToolButton(*customer));
    addcustomer->set_tooltip_markup("Add customer");
    addcustomer->signal_clicked().connect(sigc::mem_fun(*this, &Mainwin::on_create_customer_click));
    toolbar->append(*addcustomer);

    vbox->show_all();
}

void Mainwin::on_about_click()
{
    Gtk::AboutDialog dialog{};
    dialog.set_transient_for(*this);
    dialog.set_program_name("JADE");
    auto logo = Gdk::Pixbuf::create_from_file("logo.png");
    dialog.set_logo(logo);
    dialog.set_version("Version 1.0.0");
    dialog.set_copyright("Copyright 2018-2019");
    dialog.set_license_type(Gtk::License::LICENSE_GPL_3_0);
    std::vector<Glib::ustring> authors = {"Raul Jimenez"};
    dialog.set_authors(authors);
    std::vector<Glib::ustring> artists = {"Raul Jimenez"}; // vector redacted for space
    dialog.set_artists(artists);
    dialog.run();
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
    l_num.set_width_chars(15);
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
        std::string name = e_name.get_text();
        std::string input = e_num.get_text();
        if (result == 1 && name == "")
            e_name.set_text("### INVALID ###");
        else if (result == 1 && !std::regex_match(input, reg)) //check if phone number is same
            e_num.set_text("### INVALID ###");
        else if (result == 0)
        {
            fail = false;
            dialog->close();
        }
        else
        {
            fail = false;
            std::string namer = e_name.get_text(), num = e_num.get_text();
            Customer cust{namer, num};
            _store.add_customer(cust);
            dialog->close();
        }
    }
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
void Mainwin::on_create_order_click()
{
    Gtk::Dialog *dialog = Gtk::manage(new Gtk::Dialog("Create order"));
    dialog->set_transient_for(*this);
    Order ord = Order();
    std::string ord_num{"Order #"};
    ord_num += std::to_string(ord.order_number()) + "\n";
    //name
    Gtk::HBox b_order;
    Gtk::Label l_order{ord_num};
    b_order.pack_start(l_order, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_order, Gtk::PACK_SHRINK);
    //product
    Gtk::ComboBoxText c_product;
    Gtk::HBox b_product;
    Gtk::Label l_product{"Product:"};
    l_product.set_width_chars(15);
    b_product.pack_start(l_product, Gtk::PACK_SHRINK);
    c_product.set_size_request(160);
    for (auto p : _store.products())
        c_product.append(p->to_string());
    b_product.pack_start(c_product, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_product, Gtk::PACK_SHRINK);

    dialog->add_button("Cancel", 0);
    dialog->add_button("Add", 1);
    dialog->add_button("Next", 2);

    bool not_done = true;
    while (not_done)
    {
        dialog->show_all();
        int result = dialog->run();
        if (result == 0)
        {
            dialog->close();
            not_done = false;
        }
        else if (result == 1) //adds product to order
        {
            int product_selected = c_product.get_active_row_number();
            ord.add_product(_store.products()[product_selected]);
            ord_num += _store.products()[product_selected]->to_string() + "\n";
            l_order.set_text(ord_num);
        }
        else if (result == 2)
        {
            Gtk::Dialog *custo = Gtk::manage(new Gtk::Dialog("Select Customer"));
            custo->set_transient_for(*dialog);
            Gtk::ComboBoxText c_custo;
            Gtk::HBox b_custo;
            Gtk::Label l_custo{"Customer:"};
            b_custo.pack_start(l_order, Gtk::PACK_SHRINK);
            l_custo.set_width_chars(15);
            b_custo.pack_start(l_custo, Gtk::PACK_SHRINK);
            c_custo.set_size_request(160);
            for (int i = 0; i < _store.number_of_customers(); i++)
                c_custo.append(_store.customer_to_string(i));
            b_custo.pack_start(c_custo, Gtk::PACK_SHRINK);
            custo->get_vbox()->pack_start(b_custo, Gtk::PACK_SHRINK);

            std::string order_num = "Place order " + ord.order_number();
            custo->add_button("Cancel", 0);
            custo->add_button(order_num, 1);

            custo->show_all();
            int customer_result = custo->run();
            if (customer_result == 0)
                custo->close();
            else if (customer_result == 1)
            {
                int customer_select = c_custo.get_active_row_number();
                _store.place_order(ord, customer_select);
                custo->close();
                dialog->close();
                not_done = false;
            }
        }
    }
}
void Mainwin::on_view_order_click()
{
    Gtk::Dialog *dialog = Gtk::manage(new Gtk::Dialog("Select an Order"));
    dialog->set_transient_for(*this);
    std::string order_string{""};
    Gtk::HBox disp_order;
    Gtk::Label label_order{order_string};
    disp_order.pack_start(label_order, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(disp_order, Gtk::PACK_SHRINK);


    Gtk::ComboBoxText c_order;
    Gtk::HBox b_order;
    Gtk::Label l_order{"Order:"};
    b_order.pack_start(l_order, Gtk::PACK_SHRINK);
    l_order.set_width_chars(15);
    b_order.pack_start(l_order, Gtk::PACK_SHRINK);
    c_order.set_size_request(160);
    for (int i = 0; i < _store.number_of_orders(); i++)
        c_order.append(std::to_string(i));
    b_order.pack_start(c_order, Gtk::PACK_SHRINK);
    dialog->get_vbox()->pack_start(b_order, Gtk::PACK_SHRINK);

    dialog->add_button("Cancel", 0);
    dialog->add_button("Show", 1);

    int is_viewing = true;
    while(is_viewing)
    {
        dialog->show_all();
        int result = dialog->run();
        if(result == 0)
        {
            dialog->close();
            is_viewing = false;
        }
        else if (result == 1)
        {
            int get_order = c_order.get_active_row_number();
            order_string = _store.order_to_string(get_order);
            label_order.set_text(order_string);
        }
    }

}
