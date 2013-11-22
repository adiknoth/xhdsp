#include <gtkmm.h>
#include "examplewindow.h"

int main(int argc, char *argv[])
{
  Glib::RefPtr<Gtk::Application> app =
    Gtk::Application::create(argc, argv,
      "org.gtkmm.examples.base");

  ExampleWindow window;

  return app->run(window);
}
