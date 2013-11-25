#include <glibmm/ustring.h>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include "examplewindow.h"
#include "multiface.h"
#include "raydat.h"
#include "fadercell.h"

using Glib::ustring;

ExampleWindow::ExampleWindow()
    : m_Button_Close("Close")
{
    set_border_width(0);
    //set_size_request(300, 300);

    m_ScrolledWindow.set_border_width(10);

    /* the policy is one of Gtk::POLICY AUTOMATIC, or Gtk::POLICY_ALWAYS.
     * Gtk::POLICY_AUTOMATIC will automatically decide whether you need
     * scrollbars, whereas Gtk::POLICY_ALWAYS will always leave the scrollbars
     * there.  The first one is the horizontal scrollbar, the second,
     * the vertical. */
    m_ScrolledWindow.set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_NEVER);

#if 0
    m_ScrolledWindow.set_halign(Gtk::ALIGN_FILL);
    m_ScrolledWindow.set_valign(Gtk::ALIGN_FILL);
#endif
    m_ScrolledWindow.set_vexpand(true);

    get_content_area()->add(m_ScrolledWindow);

    /* set the spacing to 10 on x and 10 on y */
    m_Grid.set_row_spacing(0);
    m_Grid.set_column_spacing(1);

    m_Grid.set_row_homogeneous(true);
    m_Grid.set_column_homogeneous(true);

    /* pack the grid into the scrolled window */
    m_ScrolledWindow.add(m_Grid);

    /* Detect audio interface
     * FIXME: Should probably be somewhere else
     */
    {
	    int card = -1;
	    char *shortname, *name;
	    while (snd_card_next(&card) >= 0) {
		    if (card < 0) {
			    break;
		    }
		    snd_card_get_longname(card, &name);
		    snd_card_get_name(card, &shortname);
		    printf("Card %d: %s\n", card, name);
		    if (!strncmp(name, "RME Hammerfall DSP + Multiface", 30)) {
			    printf("Multiface found: %s\n",
					    shortname);

			    my_card = new MultiFace(shortname, card);
		    } else if (!strncmp(name, "RME RayDAT", 10)) {
			    printf("RME RayDAT found!\n");

			    my_card = new RayDat(shortname, card);
		    }


		    free(shortname);
		    free(name);
	    }
    }

    set_title("xhdsp " + my_card->getCardname());



    my_card->open();

    /* this simply creates a grid of toggle buttons
     * to demonstrate the scrolled window. */
    for(int dest = 0; dest < my_card->getDestChannels(); dest++)
    {
        for(int source = 0; source < my_card->getSourceChannels(); source++)
        {
		FaderCell* pButton = Gtk::manage(new FaderCell(*my_card, source, dest));


		double value = my_card->getGaindB(source, dest);
		pButton->set_value(value);

		m_Grid.attach(*pButton, dest, source, 1, 1);

		/* Labels for Input/Playback */
		if (0 == dest) {
			Gtk::Label* newlabel = Gtk::manage(new Gtk::Label());
			Glib::ustring chlabel = "<b><span size=\"x-small\">" +
					my_card->getSourceName(source) +
				"</span></b>";
			newlabel->set_markup(chlabel);
			m_Grid.attach(*newlabel, -1, source, 1, 1);
		}
	}
        Gtk::Label* pButton = Gtk::manage(new Gtk::Label());
	Glib::ustring chlabel = "<b><span size=\"x-small\">" + my_card->getDestName(dest) + "</span></b>";
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

    pBox->set_vexpand(false);

    show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_close()
{
    hide();
}

