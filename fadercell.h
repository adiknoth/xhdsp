#ifndef _FADERCELL_H
#define _FADERCELL_H

#include <gtkmm.h>
#include <glibmm/ustring.h>
#include <iomanip>

using Glib::ustring;

class FaderCell : public Gtk::Frame
{
public:
	FaderCell(Glib::ustring label);
	void set_value(double value);
private:
	double m_value;
	Glib::ustring m_string_value;
};

#endif /* _FADERCELL_H */
