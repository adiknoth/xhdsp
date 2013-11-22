#include "audioclass.h"
#include <cstdio>

int main(void) {
    AudioClass my_card;

    my_card.open();

    printf ("%li\n", my_card.getGain(3, 3));

    return 0;
}
