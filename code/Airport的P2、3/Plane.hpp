#ifndef _Plane
#define _Plane

#include <iostream>
using namespace std;

enum Plane_status {null, arriving, departing};

class Plane
{
public:
    Plane();
    Plane( int flt, int time, Plane_status cur_state );
    Plane& operator=( const Plane& temp );
    void refuse() const;
    void land( int time, int idx = 1 ) const;        //idx表示默认用于着陆的跑道编号为 1
    void fly( int time, int idx = 2 ) const;         //idx表示默认用于起飞的跑道编号为 2
    int started() const;                             //用于与runway类沟通达到机场的时间

private:
    int flt_num;
    int clock_start;
    Plane_status state;
};

#endif