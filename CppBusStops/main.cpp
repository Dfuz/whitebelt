#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
using namespace std;

// **************** FUNCTIONS ****************************************************
void AllBuses
(const map<string, vector<string>>& busMap) 
{ 
    if (busMap.size() == 0)
    {
        cout << "No buses" << endl;
        return;
    }
    for (const auto& [bus, stops] : busMap)
    {
        cout << "Bus " << bus << ":";
        for (const auto& stop : stops)
            cout << " " << stop;
        cout << endl;
    }
}

void BusesForStop
(const string& stopKey, const map<string, vector<string>>& busMap, const vector<string>& busm) 
{ 
    bool found = false;
    set<string> buses;
    for (auto const& [bus, stops] : busMap)
    {
        if (find(begin(stops), end(stops), stopKey) != end(stops))
            buses.insert(bus);
    }
    if (buses.size() == 0)
    {
        cout << "No stop" << endl;
        return;
    }
    for (auto const& bus : busm)
    {
        if (buses.find(bus) != end(buses))
            cout << bus << " ";
    }
    cout << endl;
}
void StopsForBus
(const string& busKey, const map<string, vector<string>>& busMap, const vector<string>& busm)
{
    if (busMap.find(busKey) == end(busMap))
    {
        cout << "No bus" << endl;
        return;
    }
    for (const auto& stop : busMap.at(busKey))
    {
        cout << "Stop " << stop << ":";
        vector<string> alternativeBuses;
        for (const auto& [bus, stops] : busMap)
        {
            if (bus != busKey)
            {
                if (find(begin(stops), end(stops), stop) != end(stops))
                {
                    alternativeBuses.push_back(bus);
                }
            }
        }
        if (alternativeBuses.size() == 0) cout << " no interchange";
        else
        {
            for (auto const& bus : busm)
            {
                if (find(begin(alternativeBuses), end(alternativeBuses), bus) 
                    != end(alternativeBuses))
                {
                    cout << " " << bus;
                }
            }
        }
        cout << endl;
    }
}

// **************** MAIN ***********************************************************
int main()
{
    int commandCount;
    cin >> commandCount;
    map<string, vector<string>> bsmap;
    vector<string> busm;
    for (; commandCount > 0; --commandCount) 
    { 
        string command, bus, stop; 
        cin >> command; 
        if (command == "NEW_BUS") 
        { 
            int stopCount; 
            cin >> bus >> stopCount; 
            busm.push_back(bus);
            for (; stopCount > 0; --stopCount) 
            { 
                cin >> stop; 
                bsmap[bus].push_back(stop); 
            }
        }
        else if (command == "BUSES_FOR_STOP") 
        {
            cin >> stop;
            BusesForStop(stop, bsmap, busm);
        }
        else if (command == "ALL_BUSES")
        {
            AllBuses(bsmap);
        }
        else if (command == "STOPS_FOR_BUS") 
        {
            cin >> bus;
            StopsForBus(bus, bsmap, busm);
        }
    }
    return 0;
}