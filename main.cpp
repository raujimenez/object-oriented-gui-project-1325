#include <iostream>
#include "mainwin.h"
#include <stdlib.h>
#include <time.h>
int main(int argc, char *argv[])
{
    srand(time(NULL));
    auto app = Gtk::Application::create(argc, argv, "edu.uta.cse1325.rauljava");
    Mainwin win;
    win.set_title("Java and Donuts");
    return app->run(win);
}