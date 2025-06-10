#include "registro.hpp"
#include <sstream>
#include <cstring>

void trim(string& s) {
    // Remove espaços do começo
    while (!s.empty() && (s.front() == ' ' || s.front() == '\t' || s.front() == '\r' || s.front() == '\n')) {
        s.erase(0, 1);
    }
    // Remove espaços do fim
    while (!s.empty() && (s.back() == ' ' || s.back() == '\t' || s.back() == '\r' || s.back() == '\n')) {
        s.pop_back();
    }
}

void Registro::fromCSVLine(const string& line) {
    stringstream ss(line);
    string token;

    // ID
    getline(ss, token, ',');
    trim(token);
    id = stoi(token);

    // Name
    getline(ss, token, ',');
    trim(token);
    strncpy(name, token.c_str(), sizeof(name));
    name[sizeof(name) - 1] = '\0';

    // City
    getline(ss, token, ',');
    trim(token);
    strncpy(city, token.c_str(), sizeof(city));
    city[sizeof(city) - 1] = '\0';

    // Sport
    getline(ss, token, ',');
    trim(token);
    strncpy(sport, token.c_str(), sizeof(sport));
    sport[sizeof(sport) - 1] = '\0';

    // Event (pode conter vírgulas dentro das aspas)
    if (!ss.eof()) {
        getline(ss, token, ',');
        trim(token);
        if (!token.empty() && token.front() == '"') {
            string eventStr = token.substr(1); // remove a primeira aspas
            string rest;
            while (getline(ss, rest, ',')) {
                eventStr += "," + rest;
                if (!rest.empty() && rest.back() == '"') break;
            }
            if (!eventStr.empty() && eventStr.back() == '"') {
                eventStr.pop_back(); // remove a última aspas
            }
            trim(eventStr);
            strncpy(event, eventStr.c_str(), sizeof(event));
            event[sizeof(event) - 1] = '\0';
        } else {
            strncpy(event, token.c_str(), sizeof(event));
            event[sizeof(event) - 1] = '\0';
        }
    }

    // NOC
    getline(ss, token);
    trim(token);
    strncpy(noc, token.c_str(), sizeof(noc));
    noc[sizeof(noc) - 1] = '\0';
}

void Registro::print() const {
    cout << id << ", " << name << ", " << city << ", " << sport << ", " << event << ", " << noc << endl;
}
