#ifndef _FADERCELL_H
#define _FADERCELL_H

#include <gtkmm.h>
#include <glibmm/ustring.h>
#include <iomanip>
#include "audioclass.h"

using Glib::ustring;

class FaderCell : public Gtk::Bin
{
public:
	FaderCell(AudioClass& card, int source, int dest);
	void set_value(double value, bool write_hw = false);
	long int get_value();
	//Signal handlers:
	bool on_fadercell_clicked(GdkEventButton *ev);
	bool on_fadercell_motion(GdkEventMotion *ev);

protected:

private:
	Gtk::EventBox m_eventbox;
	Gtk::Label m_label;
	double m_value;
	int m_source;
	int m_dest;
	AudioClass& m_card;
	Glib::ustring m_string_value;

	bool _dragging = false;
	int m_last_x;
	int m_last_y;
};

#endif /* _FADERCELL_H */
