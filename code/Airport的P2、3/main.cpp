#include "Plane.hpp"
#include "Runway.hpp"
#include "Random.hpp"

using namespace std;

void run_idle( int current_time, int idx );      //idx为跑道编号
void intro_and_ini( int& end_time, int& queue_limit, double& arrival_rate, double& departure_rate );

int main() 
{
    int end_time = 0;
    int queue_limit = 0;
    int flight_number = 0;
    double arrival_rate = 0, departure_rate = 0;
    intro_and_ini( end_time, queue_limit, arrival_rate, departure_rate );
    Random variable;
    // Runway small_airport( queue_limit );
    Runway landing_runway( queue_limit, landing ), takingoff_runway( queue_limit, takingoff );

    for ( int current_time = 0; current_time < end_time; ++current_time ) {

        int number_arrivals = variable.poisson( arrival_rate );
        bool saturatedLanding = false;              //标记着陆队列是否过满

        for ( int i = 0; i < number_arrivals; ++i ) {

            Plane current_plane( flight_number++, current_time, arriving );
            if ( landing_runway.can_land( current_plane ) != success ) {
                saturatedLanding = true;

                //若起飞跑道的着陆队列也已满，则拒绝
                if ( takingoff_runway.can_land( current_plane ) != success )
                    current_plane.refuse();
            }

        }

        int number_departures = variable.poisson( departure_rate );

        for ( int i = 0; i < number_departures; ++i ) {
            Plane current_plane( flight_number++, current_time, departing );
            if ( takingoff_runway.can_depart( current_plane ) != success ) {
                current_plane.refuse();
            }
        }

        Plane moving_plane;

        if ( saturatedLanding ) {

            cout << "=== Stop the takeoffs and both runways are used to"
                 << " clear the backlog of landing planes. ===" << endl;

            landing_runway.activity( current_time, moving_plane );
            moving_plane.land( current_time );

            //用起飞的跑道着陆
            takingoff_runway.activity( current_time, moving_plane );
            moving_plane.land( current_time, 2 );           //用于起飞的跑道编号为 2

        } else if ( landing_runway.empty() || takingoff_runway.empty() ) {

            if ( landing_runway.empty() ) {

                for ( int i = 2; i >= 1; --i ) {            //可以将着陆跑道用于起飞
                    switch ( takingoff_runway.activity( current_time, moving_plane ) ) {
                        case takeoff:
                            moving_plane.fly( current_time, i );
                            break;
                        case idle:
                            run_idle( current_time, i );
                    }
                }

            } else {

                for ( int i = 1; i <= 2; ++i ) {            //可以将起飞跑道用于着陆
                    switch ( landing_runway.activity( current_time, moving_plane ) ) {
                        case takeoff:
                            moving_plane.fly( current_time, i );
                            break;
                        case idle:
                            run_idle( current_time, i );
                    }
                }

            }

        } else {

            switch ( landing_runway.activity( current_time, moving_plane ) ) {
                case land:
                    moving_plane.land( current_time );
                    break;
                case idle:
                    run_idle( current_time, 1 );
            }

            switch ( takingoff_runway.activity( current_time, moving_plane ) ) {
                case takeoff:
                    moving_plane.fly( current_time );
                    break;
                case idle:
                    run_idle( current_time, 2 );
            }

        }
    }

    cout << endl << "================================================" << endl << endl; 
    landing_runway.shut_down( end_time );
    cout << endl << "================================================" << endl << endl;
    takingoff_runway.shut_down( end_time );

    getchar();
    getchar();
    return 0;
}

void intro_and_ini( int& end_time, int& queue_limit, double& arrival_rate, double& departure_rate ) {

//introduction：
    cout << "This programe simulates an airport with two runways, one is for landing, " 
         << "the other is for taking off." << endl;

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

        acceptable = true;

    } while ( !acceptable );

}

void run_idle( int current_time, int idx ) {
    cout << "At time " << current_time << ": the No. " << idx << " runway is idle." << endl;
}