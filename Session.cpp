#include "Session.h"

int Session::baseID = 1000;

Session::Session(string fr, string cm) {
    baseID++;
    id = baseID;
    frequencyRange = fr;
    cesMode = cm;
}

string Session::getFrequency() {
    return frequencyRange;
}
