#include <exception>
#include <system_error>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

string AskTimeServer(void);

class TimeServer {
public:
	string GetCurrentTime()
	{
		try
		{
			last_fetched_time = AskTimeServer();
		} 
		catch (system_error& ex)
		{}
		return last_fetched_time;
	}
private:
	string last_fetched_time = "00:00:00";
};


int main() {
	TimeServer ts;
	try {
		cout << ts.GetCurrentTime() << endl;
	}
	catch (exception& e) {
		cout << "Exception got: " << e.what() << endl;
	}
	return 0;
}