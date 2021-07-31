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
		if (newDay > 31 || newDay < 1) throw invalid_argument("Day value is invalid: " + to_string(newDay));
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
	static inline void formatChecker(char dash, string date)
	{
		if (dash != '-')
		{
			stringstream stream;
			stream << "Wrong date format: " << date;
			throw invalid_argument(stream.str());
		}
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
		string fullDate;
		in >> fullDate;
		stringstream tempStream;
		tempStream << fullDate;
		int yearInt, monthInt, dayInt; char dash1, dash2;
		if (tempStream >> yearInt >> dash1 >> monthInt >> dash2 >> dayInt && tempStream.peek() == EOF)
		{
			auto year = Year(yearInt);
			formatChecker(dash1, fullDate);
			auto month = Month(monthInt);
			formatChecker(dash2, fullDate);
			auto day = Day(dayInt); 
			date = Date(day, month, year);
		}
		else
		{
			stringstream stream;
			stream << "Wrong date format: " << fullDate;
			throw invalid_argument(stream.str());
		}
        return in;
	}
	static Date ParseDate(string date)
	{
		stringstream stream(date);

		int year;
		stream >> year;
		if (stream.peek() != '-')
			throw invalid_argument("Wrong date format: " + date);

		int month;
		stream.ignore(1);
		stream >> month;
		if (stream.peek() != '-')
			throw invalid_argument("Wrong date format: " + date);

		int day;
		stream.ignore(1);
		stream >> day;
		if (!stream.eof() || stream.fail())
			throw invalid_argument("Wrong date format: " + date);

        Month monthStruct{month};
        Year yearStruct{year};
        Day dayStruct{day};
        return (Date(dayStruct, monthStruct, yearStruct));
	}
};

bool operator<(const Date& lhs, const Date& rhs)
{
	if (lhs.year != rhs.year) return lhs.year < rhs.year;
    if (lhs.month != rhs.month) return lhs.month < rhs.month;
	return lhs.day < rhs.day;
}

ostream& operator<<(ostream& out, const Date& date)
{
	out << setfill('0') << setw(4) << date.GetYear() << '-';
	out << setfill('0') << setw(2) << date.GetMonth() << '-';
	out << setfill('0') << setw(2) << date.GetDay();
	return out;
}

class Database 
{
private:
	map<Date, strVec> dayAndEvents;
public:
	void AddEvent(const Date& date, const string& event)
	{
		auto& events = dayAndEvents[date];
		if (find(begin(events), end(events), event) != end(events))
			return;
		events.push_back(event);
		if (events.size() > 1) sort(begin(events), end(events));
	}
	bool DeleteEvent(const Date& date, const string& event)
	{
		if (dayAndEvents.count(date) > 0)
		{
			auto& dayEvents = dayAndEvents.at(date);
			auto founded = find(begin(dayEvents), end(dayEvents), event);
			if (founded == end(dayEvents))
			{
				cout << "Event not found" << endl;
				return false;
			}
			else
			{
				dayEvents.erase(founded);
				if (dayEvents.size() == 0) dayAndEvents.erase(date);
				cout << "Deleted successfully" << endl;
				return true;
			}
		}
		else
		{
			cout << "Event not found" << endl;
			return false;
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
				cout << *event << endl;
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
				for (const auto& it : events)
					cout << date << ' ' << it << endl;
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

//*********************************************
//*************** MAIN ************************
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
		try
		{
			if (commandSet.count(command) < 1 && !command.empty())
			{
				throw invalid_argument("Unknown command: " + command);
			}
			else if (command == "Add")
			{
				string dateStr;
				string event;
				commandStream >> dateStr;
				commandStream >> event;
				const Date date = Date::ParseDate(dateStr);
				if (!event.empty()) db.AddEvent(date, event);
			}
			else if (command == "Del")
			{
				string dateStr;
				string event;
				commandStream >> dateStr;
				const Date date = Date::ParseDate(dateStr);
				if (!commandStream.eof()) commandStream >> event;
				if (event.empty())
					cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
				else db.DeleteEvent(date, event);
			}
			else if (command == "Find")
			{
				string dateStr;
				commandStream >> dateStr;
				const Date date = Date::ParseDate(dateStr);
				db.Find(date);
			}
			else if (command == "Print") db.Print();
		}
		catch (invalid_argument& ex)
		{
			cout << ex.what() << endl;
			return 0;
		}
	}
	return 0;
}
