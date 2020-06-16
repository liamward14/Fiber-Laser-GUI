#include "g-header.h"

int main(int argc, char *argv[])
{
    //Create Application instance
    auto app = Gtk::Application::create(argc, argv, "com.github.Fiber-Laser-GUI");

    //create window object
    MWindow window;

    //Begin event loop process
    return app->run(window);
}
