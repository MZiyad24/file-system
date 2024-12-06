#ifndef QUERYHANDLER_H
#define QUERYHANDLER_H

#include <string>
#include <vector>
#include "primaryIndex.cpp"
#include "secondaryIndex.cpp"
using namespace std;
class QueryHandler {
private:
    SecondaryIndex secondaryIndex;
    PrimaryIndex primaryIndex;

    void printDoctorDetails(int offset);
    void printAppointmentDetails(int offset);

public:
    QueryHandler();
    void handle(const std::string &query);
};

string extractValue(const std::string &query, const std::string &key);

#endif // QUERYHANDLER_H
