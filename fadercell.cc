#include "fadercell.h"

FaderCell::FaderCell(AudioClass& card, int source, int dest) :
	m_frame("")
	, m_card(card)
{
	m_string_value = "";
	m_source = source;
	m_dest = dest;

	m_frame.set_label_align(Gtk::ALIGN_FILL,
			Gtk::ALIGN_FILL);

	m_frame.set_border_width(0);

	set_events(Gdk::BUTTON_PRESS_MASK);
	add(m_eventbox);
	m_eventbox.add(m_frame);

	m_eventbox.signal_button_press_event().connect(sigc::mem_fun(*this,
				&FaderCell::on_fadercell_clicked), false);
}

long int FaderCell::get_value()
{
	return m_value;
}

void FaderCell::set_value(double value) {
	m_value = value;

	if (DBL_MAX != value) {
		m_string_value = "<span size=\"x-small\">" + ustring::format(std::fixed, std::setprecision(1), value) +
			"</span>";
	} else {
		m_string_value = "";
	}

	Gtk::Label *tmp = static_cast<Gtk::Label*> (m_frame.get_label_widget());
	tmp->set_markup(m_string_value);

	/* green */
	if (0.0 == value) {
		m_frame.override_background_color(Gdk::RGBA("#00ff00"));
	} else if (6.0 > value) {
		m_frame.override_background_color(Gdk::RGBA("yellow"));
	} else {
		m_frame.unset_background_color();
	}
}

bool FaderCell::on_fadercell_clicked(GdkEventButton *ev)
{
	double new_value;
	printf ("%i: %i\n", m_source, m_dest);

	if (ev->button != 1) {
		new_value = -6.0;
	} else if (m_value != 0.0) {
		new_value = 0.0;
	} else {
		new_value = DBL_MAX;
	}

	set_value(new_value);

	m_card.setGaindB(m_source, m_dest, new_value);

	/* true == fully handled */
	return true;
}
