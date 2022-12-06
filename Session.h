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
        //Session(int n, string fr, string cm, int d); // Constructor to create a Session object (include all 4 member variables)

        Session(int n, string fr, string cm); // Constructor to create a Session object (include all 4 member variables)
        string getFrequency();
};

#endif // SESSION
