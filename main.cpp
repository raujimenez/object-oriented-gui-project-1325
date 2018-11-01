#include <iostream>
#include "mainwin.h"

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "edu.uta.cse1325.rauljava");
    Mainwin win;
    win.set_title("Java and Donuts");
    return app->run(win);
}