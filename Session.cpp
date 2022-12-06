#include "Session.h"

Session::Session(int n, string fr, string cm) {
    id = n;
    frequencyRange = fr;
    cesMode = cm;
}

string Session::getFrequency() {
    return frequencyRange;
}
