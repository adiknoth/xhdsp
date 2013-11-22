#include "fadercell.h"

FaderCell::FaderCell(int source, int dest) :
	m_frame("")
{
	m_string_value = "";
	m_source = source;
	m_dest = dest;

	m_frame.set_label_align(Gtk::ALIGN_FILL,
			Gtk::ALIGN_FILL);

	set_events(Gdk::BUTTON_PRESS_MASK);
	add(m_eventbox);
	m_eventbox.add(m_frame);

	m_eventbox.signal_button_press_event().connect(sigc::mem_fun(*this,
				&FaderCell::on_fadercell_clicked), false);
}


void FaderCell::set_value(double value) {
	m_value = value;

	if (DBL_MAX != value) {
		m_string_value = ustring::format(std::fixed, std::setprecision(1), value);
	} else {
		m_string_value = "";
	}

	m_frame.set_label(m_string_value);

	/* green */
	if (0.0 == value) {
		m_frame.override_background_color(Gdk::RGBA("#00ff00"));
	} else if (6.0 > value) {
		m_frame.override_background_color(Gdk::RGBA("yellow"));
	}
}

bool FaderCell::on_fadercell_clicked(GdkEventButton *ev)
{
	printf ("%i: %i\n", m_source, m_dest);
	return false;
}
