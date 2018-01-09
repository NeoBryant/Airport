#ifndef _Runway
#define _Runway

#include <queue>
#include <iostream>
#include "Plane.hpp"
using namespace std;

enum Runway_activity { idle, land, takeoff, emergency_land};

enum Error_code { success, fail };

class Runway
{
public:
    Runway( int limit );
    Error_code can_land( const Plane &current );
    Error_code can_depart( const Plane &current );
    Runway_activity activity( int time, Plane &moving );
    double busy(int current_time)const;
    void shut_down( int time ) const;
private:
    queue<Plane> landings;
    /*飞机场的着陆队列？？？为什么这里必须有一个换行？？？*/
    queue<Plane> takeoffs;
    /*飞机场的起飞队列？？？为什么这里必须有一个换行？？？*/
    int queue_limit;
    int num_land_requests;                  //请求着陆的飞机
    int num_takeoff_requests;               //请求起飞的飞机
    int num_land_finished;                  //已经在这个机场完成着陆的飞机
    int num_takeoff_finished;               //已经在这个机场完成起飞的飞机
    int num_land_accepted;                  //已经被接受但是在等待着陆的飞机
    int num_takeoff_accepted;               //已经被接受但是在等待起飞的飞机
    int num_land_refused;                   //被拒绝着陆要求的飞机
    int num_takeoff_refused;                //被拒绝起飞要求的飞机
    int num_emergency;
    int num_crashed;
    int land_wait_total;                    //所有飞机等待着陆的总时间
    int takeoff_wait_total;                 //所有飞机等待起飞的总时间
    int idle_time_total;                    //跑道闲置的总时间

};

#endif
