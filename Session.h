#ifndef SESSION
#define SESSION

#include <string>

using namespace std;

class Session {
    private:
        int id; // Unique identifier for each Session
        string frequencyRange; // Session Frequency Range (Page 12 Manual) - 4 available based on specs
        string cesMode; // CES Mode (page 11 Manual) - 2 available

    public:
        static int baseID; // starting id which is incremented by 1 for each instance

        Session(string fr, string cm);
        string getFrequency();
};

#endif // SESSION
