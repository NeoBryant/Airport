#include "Plane.hpp"
using namespace std;

Plane::Plane()
{
    flt_num = -1;
    clock_start = -1;
    state = null;
}

Plane::Plane( int flt, int time, Plane_status cur_state )
{
    flt_num = flt;
    clock_start = time;
    state = cur_state;

    cout << "Plane number " << flt << " ready to";
    if ( state == arriving ) {
        cout << " land." << endl;
    } else {
        cout << " take off." << endl;
    }
}

Plane& Plane::operator=( const Plane& other )
{
    flt_num = other.flt_num;
    clock_start = other.clock_start;
    state = other.state;
    return ( *this );
}

void Plane::refuse() const
{
    cout << "Plane number " << flt_num;
    if ( state == arriving ) {
        cout << " directed to another airport" << endl;
    } else {
        cout << " told to try taking off again later" << endl;
    }
}

void Plane::fly( int time, int idx ) const
{
    int wait = time - clock_start;
    cout << "At time " << time << ": Plane number " << flt_num << " takes off in No. " << idx 
         << " runway after " << wait << " time unit" << ( wait == 1 ? "" : "s" ) 
         << " in the takeoff queue." << endl;
}

void Plane::land( int time, int idx ) const
{
    int wait = time - clock_start;
    cout << "At time " << time << ": Plane number " << flt_num << " landed in No. " << idx
         << " runway after " << wait << " time unit" << ( wait == 1 ? "" : "s" ) 
         << " in the landing queue." << endl;
}

//用于与runway类沟通达到机场的时间
int Plane::started() const
{
    return clock_start;
}