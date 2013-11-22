#include "examplewindow.h"
#include "audioclass.h"
#include <glibmm/ustring.h>
#include <cstdio>
#include <iostream>


ExampleWindow::ExampleWindow()
    : m_Button_Close("Close")
{
    set_title("xhdsp - Multiface");
    set_border_width(0);
    //set_size_request(300, 300);

    m_ScrolledWindow.set_border_width(10);

    /* the policy is one of Gtk::POLICY AUTOMATIC, or Gtk::POLICY_ALWAYS.
     * Gtk::POLICY_AUTOMATIC will automatically decide whether you need
     * scrollbars, whereas Gtk::POLICY_ALWAYS will always leave the scrollbars
     * there.  The first one is the horizontal scrollbar, the second,
     * the vertical. */
    m_ScrolledWindow.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_NEVER);

    get_content_area()->pack_start(m_ScrolledWindow);

    /* set the spacing to 10 on x and 10 on y */
    m_Grid.set_row_spacing(0);
    m_Grid.set_column_spacing(0);

    /* pack the grid into the scrolled window */
    m_ScrolledWindow.add(m_Grid);

    AudioClass my_card;
    my_card.open();

#if 0
    for(int dest = 0; dest < my_card.getDestChannels(); dest++) {
	    for(int source = 0; source < my_card.getSourceChannels(); source++)
		    if (-1 == my_card.getGain(source, dest)) {
			    printf ("error\n");
		    }
    }
#endif



    /* this simply creates a grid of toggle buttons
     * to demonstrate the scrolled window. */
    for(int dest = 0; dest < my_card.getDestChannels(); dest++)
    {
        for(int source = 0; source < my_card.getSourceChannels(); source++)
        {
		long int value= my_card.getGain(source, dest);
		Glib::ustring s_value = Glib::ustring::compose("%1", value);

		Gtk::Label* pButton = Gtk::manage(new Gtk::Label(s_value));
		m_Grid.attach(*pButton, dest, source, 1, 1);

		/* Labels for Input/Playback */
		if (0 == dest) {
			Gtk::Label* newlabel = Gtk::manage(new Gtk::Label());
#if 0
			Glib::ustring chlabel = "<b>" + my_card.getSourceName(source) + "</b>";
#else
			Glib::ustring chlabel = "<b>" +
				Glib::ustring::compose("%1",
					my_card.getSourceName(source)) +
				"</b>";
#endif
			newlabel->set_markup(chlabel);
			m_Grid.attach(*newlabel, -1, source, 1, 1);
		}
	}
        Gtk::Label* pButton = Gtk::manage(new Gtk::Label());
	Glib::ustring chlabel = "<b>" + Glib::ustring::compose("%1", my_card.getDestName(dest)) + "</b>";
	//Glib::ustring chlabel = "<b>out " + Glib::ustring::compose("%1",dest) + "</b>";
        pButton->set_markup(chlabel);
        m_Grid.attach(*pButton, dest, -1, 1, 1);
    }

    /* Add a "close" button to the bottom of the dialog */
    m_Button_Close.signal_clicked().connect( sigc::mem_fun(*this,
                &ExampleWindow::on_button_close));

    /* this makes it so the button is the default. */
    m_Button_Close.set_can_default();

    Gtk::Box* pBox = get_action_area();
    if(pBox)
        pBox->pack_start(m_Button_Close);

    /* This grabs this button to be the default button. Simply hitting
     * the "Enter" key will cause this button to activate. */
    m_Button_Close.grab_default();

    show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_close()
{
    hide();
}

