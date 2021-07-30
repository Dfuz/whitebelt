#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <sstream>
#include <queue>
#include <cmath>
#include <map>
#include <set>
using namespace std;
using strVec = vector<string>;

struct Day
{
	explicit Day(int newDay)
	{
		if (newDay > 31 || newDay < 0) throw invalid_argument("Day value is invalid: " + to_string(newDay));
		else day = newDay;
	}
	int day;
};
struct Month
{
	explicit Month(int newMonth)
	{
		if (newMonth < 1 || newMonth > 12) throw invalid_argument("Month value is invalid: " + to_string(newMonth));
		month = newMonth;
	}
	int month;
};
struct Year
{
	explicit Year(int newYear) : year(newYear) {}
	int year;
};

class Date 
{
private:
	int day = 0, month = 0, year = 0;
	static inline int formatChecker(istream& in)
	{
		int dashCount = 0;
		while (in.peek() == '-')
		{
			in.ignore(1);
			++dashCount;
		}
		return dashCount;
	}
public:
	Date(Day newDay, Month newMonth, Year newYear) 
	{
		day = newDay.day;
		month = newMonth.month;
		year = newYear.year;
	}
	Date()
	{
		day = 1;
		month = 1;
		year = 0;
	}
	int GetYear() const { return year; }
	int GetMonth() const { return month; }
	int GetDay() const { return day; }
	friend bool operator<(const Date&, const Date&);
	friend istream& operator>>(istream& in, Date& date)
	{
		queue<int> dateValues;
		string fullDate;
		in >> fullDate;
		stringstream tempStream;
		tempStream << fullDate;
		int dashCount = 1, tempValue = 0;
		bool good = false;
		while (tempStream >> tempValue)
		{
			if (dashCount == 2) dateValues.push(-tempValue);
			else if (dashCount == 1) 
				dateValues.push(tempValue);
			else throw invalid_argument(string("Wrong date format: ") + fullDate);
			if (dateValues.size() == 3)
			{
				auto year = Year(dateValues.front()); dateValues.pop();
				auto month = Month(dateValues.front()); dateValues.pop();
				auto day = Day(dateValues.front()); dateValues.pop();
				date = Date(day, month, year);
				good = true;
			}
			dashCount = formatChecker(tempStream);
		}
		if ((tempStream.fail() && !tempStream.eof()) || !good) throw invalid_argument(string("Wrong date format: ") + fullDate);
        return in;
	}
};

bool operator<(const Date& lhs, const Date& rhs)
{
	if (lhs.year != rhs.year) return lhs.year < rhs.year;
    if (lhs.month != rhs.month) return lhs.month < rhs.month;
	return lhs.day < rhs.day;
}

class Database 
{
private:
	map<Date, strVec> dayAndEvents;
public:
	void AddEvent(const Date& date, const string& event)
	{
		auto& events = dayAndEvents[date];
		events.push_back(event);
		if (events.size() > 1) sort(begin(events), end(events));
	}
	bool DeleteEvent(const Date& date, const string& event)
	{
		auto& dayEvents = dayAndEvents[date];
		auto founded = find(begin(dayEvents), end(dayEvents), event);
		if (founded == end(dayEvents))
		{
			cout << "Event not found" << endl;
			return false;
		}
		else
		{
			dayEvents.erase(founded); 
			cout << "Deleted successfully" << endl;
			return true;
		}
	}
	int DeleteDate(const Date& date)
	{
		if (dayAndEvents.count(date) > 0)
		{
			auto& dayEvents = dayAndEvents.at(date);
			const auto eventsSize = dayEvents.size();
			dayEvents.clear(); 
			dayAndEvents.erase(date);
			return static_cast<int>(eventsSize);
		}
		else return 0;
	}
	int Find(const Date& date) const
	{
		if (dayAndEvents.count(date) > 0)
		{
			auto& events = dayAndEvents.at(date);
			auto eventCount = events.size();
			for (auto event = begin(events); event != end(events); ++event)
			{
				cout << *event;
				if (event != end(events) - 1) cout << ' ';
			}
			cout << endl;
			return static_cast<int>(eventCount);
		}
		return 0;
	}
	void Print() const
	{
		if (dayAndEvents.empty() == false)
		{
			for (auto& [date, events] : dayAndEvents)
			{
				PrintDate(date);
				for (const auto& it : events)
					cout << ' ' << it;
				cout << endl;
			}
		}
	}
	inline void PrintDate(const Date& date) const
	{
		cout << setfill('0') << setw(4) << date.GetYear() << '-';
		cout << setfill('0') << setw(2) << date.GetMonth() << '-';
		cout << setfill('0') << setw(2) << date.GetDay();
	}
};

int main() 
{
	Database db;
	const set<string> commandSet = {"Add", "Find", "Del", "Print"};
	string commandLine;
	while (getline(cin, commandLine)) 
	{
		stringstream commandStream(commandLine);
		string command;
		commandStream >> command;
		if (commandSet.count(command) < 1 && !command.empty())
		{
			cout << "Unknown command: " << command << endl;
			continue;
		}
		else
		{
			try
			{
				if (command == "Add")
				{
					Date date;
					string event;
					commandStream >> date;
					commandStream >> event;
					db.AddEvent(date, event);
				}
				else if (command == "Del")
				{
					Date date;
					commandStream >> date;
					string event;
					if (commandStream) commandStream >> event;
					if (event.empty())
						cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
					else db.DeleteEvent(date, event);
				}
				else if (command == "Find")
				{
					Date date;
					commandStream >> date;
					db.Find(date);
				}
				else if (command == "Print") db.Print();
			}
			catch (invalid_argument& ex)
			{
				cout << ex.what();
				cout << endl;
			}
		}
	}
	return 0;
}
