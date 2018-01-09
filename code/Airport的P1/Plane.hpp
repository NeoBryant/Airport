#ifndef _Plane
#define _Plane

#include <iostream>
using namespace std;

enum Plane_status{null, arriving, departing};

class Plane
{
public:
	Plane();
	Plane(int flt, int time, Plane_status cur_state);
	Plane& operator=(const Plane& temp);
	void refuse() const;
	void land(int time)const;
	void fly(int time)const;
	int started()const;//用于与runway类沟通达到机场的时间
private:
	int flt_num;
	int clock_start;
	Plane_status state;
};

#endif