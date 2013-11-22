#include "fadercell.h"

FaderCell::FaderCell(Glib::ustring label) :
	Gtk::Frame(label)
{
	m_string_value = label;
}

void FaderCell::set_value(double value) {
	m_value = value;

	if (DBL_MAX != value) {
		m_string_value = ustring::format(std::fixed, std::setprecision(1), value);
	} else {
		m_string_value = "";
	}

	set_label(m_string_value);

	/* green */
	if (0.0 == value) {
		override_background_color(Gdk::RGBA("#00ff00"));
	} else if (6.0 > value) {
		override_background_color(Gdk::RGBA("yellow"));
	}
}
