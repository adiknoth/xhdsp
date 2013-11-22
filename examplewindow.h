#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>
#include "audioclass.h"

class ExampleWindow : public Gtk::Dialog
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();

protected:
  //Signal handlers:
  void on_button_close();

  //Child widgets:
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::Grid m_Grid;
  Gtk::Button m_Button_Close;

private:
  AudioClass my_card;
};

#endif //GTKMM_EXAMPLEWINDOW_H
