#include <iostream>
#include "Plane.hpp"
#include "Runway.hpp"
#include "Random.hpp"

using namespace std;

void run_idle (int current_time);
void intro_and_ini (int& end_time, int& queue_limit, double& arrival_rate, double& departure_rate);

int main () {
	int end_time = 0;
	int queue_limit = 0;
	int flight_number = 0;
	double arrival_rate = 0, departure_rate = 0;
	intro_and_ini(end_time, queue_limit, arrival_rate, departure_rate);

	Random variable;
	Runway small_airport(queue_limit);
	for (int current_time = 0; current_time < end_time; ++current_time)
	{
		int number_arrivals = variable.poisson(arrival_rate);
		for (int i = 0; i < number_arrivals; ++i)
		{
			Plane current_plane(flight_number++, current_time, arriving);
			if (small_airport.can_land(current_plane) != success) {
				current_plane.refuse();
			}
		}	
		int number_departures = variable.poisson(departure_rate);
		for (int i = 0; i < number_departures; ++i)
		{
			Plane current_plane(flight_number++, current_time, departing);
			if (small_airport.can_depart(current_plane) != success) {
				current_plane.refuse();
			}
		}
		Plane moving_plane;
		switch (small_airport.activity(current_time,moving_plane)) {
		case land:
			moving_plane.land(current_time);
			break;
		case takeoff:
			moving_plane.fly(current_time);
			break;
		case idle:
			run_idle(current_time);
		}
	}
	small_airport.shut_down(end_time);
	getchar();
	getchar();
	return 0;
}

void intro_and_ini (int& end_time, int& queue_limit, double& arrival_rate, double& departure_rate) {
//（这里可以优化UI）
//introduction：
	cout << "This programe simulates an airport with only one runway." << endl;
//initialization：
	cout << "Up to what number of planes can be waiting to land or take off at any time?    " << flush;
	cin >> queue_limit;
	cout << "How many units of time will the simulation run?                                " << flush;
	cin >> end_time;
	bool acceptable = false;
	do {
		cout << "Expected number of arrivals per unit time?                                     " << flush;
		cin >> arrival_rate;
		cout << "Expected number of departures per unit time?                                   " << flush;
		cin >> departure_rate;
		if (arrival_rate<0.0 || departure_rate<0.0) {
			cerr << "These rates must not be negative! Please input again:                          " << endl;
		} else {
			acceptable = true;
		}
		if (arrival_rate + departure_rate > 1) {
			cerr << "Safe warning: the airport must be very saturated!                              " << endl;
		}
		// if (test_input())
		// //在这里对输入进行测试，如果输入正确，返回1，否则返回0；
		// 	acceptable = true;
		//下面仅仅是把acceptable记为true；
		//acceptable = true;
	} while (!acceptable);
}

void run_idle (int current_time) {
	cout << "At time " << current_time << ": the runway is idle" << endl;
}