#include "Session.h"

Session::Session(int n, string fr, string cm, int d) {
    id = n;
    frequencyRange = fr;
    cesMode = cm;
    duration = d;
}

string Session::getFrequency() {
    return frequencyRange;
}
