#include "UserProfile.h"


UserProfile::UserProfile(string un) {
    username = un;
}

void UserProfile::addRecord(Record r) {
    savedRecords.push_back(r);
}

string UserProfile::getUsername(){return username;}
