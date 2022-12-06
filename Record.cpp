#include "Record.h"

Record::Record(Session s, int d, int il) {
    session = &s;
    duration = d;
    intensityLevel = il;
}
