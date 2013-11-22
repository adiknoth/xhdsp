#include <gtkmm.h>
#include <cstdio>
#include "examplewindow.h"
#include "audioclass.h"

int main(int argc, char *argv[])
{
  Glib::RefPtr<Gtk::Application> app =
    Gtk::Application::create(argc, argv,
      "org.gtkmm.examples.base");

#if 0
  AudioClass my_card;
  my_card.open();
  for(int dest = 0; dest < my_card.getDestChannels(); dest++)
  {
      for(int source = 0; source < my_card.getSourceChannels(); source++)
          if (-1 == my_card.getGain(source, dest)) {
              printf ("error\n");
          }
  }
  my_card.close();
#endif

  ExampleWindow window;

  return app->run(window);
}
