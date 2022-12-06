#ifndef RECORD
#define RECORD

#include <string>
#include "Session.h"

using namespace std;

class Record {
    private:
        Session *session;
        int duration;
        int intensityLevel; // Intensity level, 1 - 8

    public:
        Record(Session s, int d, int il);
};

#endif // RECORD
