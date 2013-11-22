#include "audioclass.h"

int main(void) {
    AudioClass my_card;

    my_card.open();

    return my_card.getGain(0, 0);
}
