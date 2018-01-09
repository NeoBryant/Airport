#include "Plane.hpp"
#include "Runway.hpp"
#include "Random.hpp"

using namespace std;

void run_idle( int current_time );
void intro_and_ini( int& end_time, int& queue_limit, double& arrival_rate, double& departure_rate );

int main() {
    int end_time = 0;
    int queue_limit = 0;
    int flight_number = 0;
    double arrival_rate = 0, departure_rate = 0;
    intro_and_ini( end_time, queue_limit, arrival_rate, departure_rate );
    Random variable;
    Runway small_airport( queue_limit );
    bool emergency_situation = false; 
    for ( int current_time = 0; current_time < end_time; ++current_time )
    {
        int number_arrivals = variable.poisson( arrival_rate );
        Plane moving_plane;
        for ( int i = 0; i < number_arrivals; ++i )
        {	
            Plane current_plane( flight_number++, current_time, arriving );
            if(!emergency_situation && current_plane.get_status() == emergency){
				moving_plane = current_plane;
				emergency_situation = true;
			}
            else if ( small_airport.can_land( current_plane ) != success ) {
                current_plane.refuse();
            }
        }
        int number_departures = variable.poisson( departure_rate );
        for ( int i = 0; i < number_departures; ++i )
        {
            Plane current_plane( flight_number++, current_time, departing );
            if ( small_airport.can_depart( current_plane ) != success ) {
                current_plane.refuse();
            }
        }
    	switch ( small_airport.activity( current_time, moving_plane ) ) {
        case land:
            moving_plane.land( current_time );
            if(moving_plane.crashed(current_time)){
            	cout << "Persentage of time Runway idle: " << small_airport.busy(current_time) << endl;
			}
            break;
        case takeoff:
            moving_plane.fly( current_time );
            break;
        case emergency_land:
        	moving_plane.land( current_time);
        	emergency_situation = false;
        	break;
        case idle:
            run_idle( current_time );
        }
    }
    small_airport.shut_down( end_time );
    return 0;
}

void intro_and_ini( int& end_time, int& queue_limit, double& arrival_rate, double& departure_rate ) {
//（这里可以优化UI）
//introduction：
    cout << "This programe simulates an airport with only one runway." << endl;
//initialization：
    bool acceptable = false;
    do {
        cout << "Up to what number of planes can be waiting to land"
             << "or take off at any time?" << flush;
        cin >> queue_limit;
        cout << "How many units of time will the simulation run?" << flush;
        cin >> end_time;
        cout << "Expected number of arrivals per unit time?" << flush;
        cin >> arrival_rate;
        cout << "Expected number of departures per unit time?" << flush;
        cin >> departure_rate;
        // if (test_input())
        // //在这里对输入进行测试，如果输入正确，返回1，否则返回0；
        //  acceptable = true;
        //下面仅仅是把acceptable记为true；
        acceptable = true;
    } while ( !acceptable );
}

void run_idle( int current_time ) {
    cout << "At time " << current_time << ": the runway is idle" << endl;
}
