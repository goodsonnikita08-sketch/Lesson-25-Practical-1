#include <iostream>
#include <Windows.h>
#include <iomanip>

using namespace std;

class Time {
private:
	int hours;
	int minutes;
	int seconds;

	void normalize() {
		if (seconds >= 60) {
			minutes += seconds / 60;
			seconds %= 60;
		}
		if (minutes >= 60) {
			hours += minutes / 60;
			minutes %= 60;
		}
		if (seconds < 0) {
			seconds = 0;
		}
		if (minutes < 0) {
			minutes = 0;
		}
		if (hours < 0) {
			hours = 0;
		}
	}

public:
	Time() {
		hours = 0;
		minutes = 0;
		seconds = 0;
	}

	Time(int h, int m, int s) {
		hours = h;
		minutes = m;
		seconds = s;
		normalize();
	}

	Time operator+(const Time& other) const {
		int h = hours + other.hours;
		int m = minutes + other.minutes;
		int s = seconds + other.seconds;
		return Time(h, m, s);
	}

	Time operator-(const Time& other) const {
		int total1 = hours * 3600 + minutes * 60 + seconds;
		int total2 = other.hours * 3600 + other.minutes * 60 + other.seconds;
		int diff = total1 - total2;

		if (diff < 0) {
			return Time(0, 0, 0);
		}

		int h = diff / 3600;
		int m = (diff % 3600) / 60;
		int s = diff % 60;

		return Time(h, m, s);
	}

	friend ostream& operator<<(ostream& os, const Time& t) {
		os << setfill('0') << setw(2) << t.hours << ":"
			<< setfill('0') << setw(2) << t.minutes << ":"
			<< setfill('0') << setw(2) << t.seconds;
		return os;
	}

	friend istream& operator>>(istream& is, Time& t) {
		is >> t.hours;
		if (is.peek() == ':' || is.peek() == ' ') is.ignore();
		is >> t.minutes;
		if (is.peek() == ':' || is.peek() == ' ') is.ignore();
		is >> t.seconds;
		t.normalize();
		return is;
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Time t1(2, 65, 75);
	Time t2;
	Time t3;

	cout << t1 << '\n';

	cin >> t2;
	cout << t2 << '\n';

	t3 = t1 + t2;
	cout << t3 << '\n';

	Time t4 = t1 - t2;
	cout << t4 << '\n';
}