#ifndef _FADERCELL_H
#define _FADERCELL_H

#include <gtkmm.h>
#include <glibmm/ustring.h>
#include <iomanip>

using Glib::ustring;

class FaderCell : public Gtk::Bin
{
public:
	FaderCell(int source, int dest);
	void set_value(double value);
	//Signal handlers:
	bool on_fadercell_clicked(GdkEventButton *ev);

protected:

private:
	Gtk::Frame m_frame;
	Gtk::EventBox m_eventbox;
	double m_value;
	int m_source;
	int m_dest;
	Glib::ustring m_string_value;
};

#endif /* _FADERCELL_H */
