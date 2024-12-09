#ifndef QUERYHANDLER_H
#define QUERYHANDLER_H

#include <string>
#include <vector>
#include "App.h"
#include "Doc.h"
using namespace std;
class QueryHandler {
private:
    Doc doctor;
    App appointment;

public:
    QueryHandler();
    void handle(const std::string &query);
};
string extractValue(const std::string &query, const std::string &key);

#endif // QUERYHANDLER_H