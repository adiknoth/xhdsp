#include "fadercell.h"

FaderCell::FaderCell(AudioClass& card, int source, int dest) :
	m_label("")
	, m_card(card)
{
	m_string_value = "";
	m_source = source;
	m_dest = dest;

	set_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::BUTTON_MOTION_MASK | Gdk::POINTER_MOTION_HINT_MASK);
	add(m_eventbox);
	m_eventbox.add(m_label);

	m_eventbox.signal_button_press_event().connect(sigc::mem_fun(*this,
				&FaderCell::on_fadercell_clicked), false);

	m_eventbox.signal_button_release_event().connect(sigc::mem_fun(*this,
				&FaderCell::on_fadercell_clicked), false);

	m_eventbox.signal_motion_notify_event().connect(sigc::mem_fun(*this,
				&FaderCell::on_fadercell_motion), false);

	m_label.set_tooltip_text ("source: " + m_card.getSourceName(m_source) + " -> dest: " + m_card.getDestName(m_dest));
}

long int FaderCell::get_value()
{
	return m_value;
}

void FaderCell::set_value(double value, bool write_hw) {
	m_value = value;

	if (DBL_MAX != value) {
		m_string_value = "<span size=\"x-small\">" + ustring::format(std::fixed, std::setprecision(1), value) +
			"</span>";
	} else {
		m_string_value = "";
	}

	m_label.set_markup(m_string_value);

	std::string color;

	/* green */
	if (0.0 == value) {
		color = "#00ff00";
	} else if (6.0 > value) {
		color = "yellow";
	} else {
		if (0 == (m_source % 2)) {
			color="darkgrey";
		} else {
			//m_label.unset_background_color();
			color = "lightgrey";
		}
	}

	m_label.override_background_color(Gdk::RGBA(color));

	if (write_hw) {
		m_card.setGaindB(m_source, m_dest, m_value);
	}
}

bool FaderCell::on_fadercell_clicked(GdkEventButton *ev)
{
	double new_value;

	if (GDK_BUTTON_RELEASE == ev->type) {
		_dragging = false;
		return true;
	}

	if (GDK_2BUTTON_PRESS == ev->type) {
		if (m_value <= 6.0) {
			new_value = DBL_MAX;
		} else {
			new_value = 0.0;
		}
		set_value(new_value, true);
	}

	if (GDK_BUTTON_PRESS == ev->type) {
		_dragging = true;

		_last_x = ev->x;
		_last_y = ev->y;
		_last_value = m_value;

	}

	printf ("ev %i on %i: %i\n", ev->type, m_source, m_dest);

	/* true == fully handled */
	return true;
}

bool FaderCell::on_fadercell_motion(GdkEventMotion *ev)
{
	if (! _dragging ) {
		return false;
	}

	double gain_delta = (_last_y - ev->y);
	gain_delta *= 10.0;

	gain_delta = round(gain_delta) / 10.0;

	double new_gain = _last_value + gain_delta;

	if (new_gain > 6.0)
		new_gain = 6.0;

	if (new_gain < -100.0)
		new_gain = DBL_MAX;

	printf ("ak-adjust: %g\n", new_gain);

	set_value(new_gain, true);



	return false;
}
