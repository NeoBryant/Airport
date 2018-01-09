#ifndef _Plane
#define _Plane

#include <iostream>
using namespace std;

enum Plane_status {null, arriving, departing, emergency};

class Plane
{
public:
    Plane();
    Plane( int flt, int time, Plane_status cur_state );
    Plane& operator=( const Plane& temp );
    void refuse() const;
    void land( int time )const;
    void fly( int time )const;
    Plane_status get_status() const;
    int started()const;//用于与runway类沟通达到机场的时间
    int get_fuel()const;
    bool crashed(int current_time);
private:
    int flt_num;
    int clock_start;
    Plane_status state;
    int fuel;
};

#endif
