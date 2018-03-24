#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>
using namespace std;
namespace hull{
    typedef int uint;
    const uint FF=256;
    const uint FE=255;
    const uint eight=8;

    class Point {
        public:
            uint x,y;
            Point(uint x=0,uint y=0) { this->x=x; this->y=x; }
             friend std::istream& operator >> ( std::istream& os, Point& obj);
             friend std::ostream& operator << ( std::ostream& os, Point& obj);
    };

    std::istream& operator >> ( std::istream& os, Point& obj)
    {
    os>>obj.x>>obj.y;
    return os;
    }

    std::ostream& operator << ( std::ostream& os, Point& obj)
    {
    os<<obj.x<<std::endl<<obj.y;
    return os;
    }

    bool ClockWise (const Point& a,const Point& b,const Point& c)
    {
	return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
    }

    bool CounterClockWise (const Point& a,const Point& b,const Point& c)
    {
        return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
    }

    void convex_hull (std::vector<Point> & a)
    {
        int n=a.size();
        std::vector<uint> mid(n);
        for(int i=0;i<n;++i)
        {
            mid[i]=a[i].x*10000+a[i].y;
        }
        std::vector<int> buf(FF);
        std::vector<int> point(FF);
        std::vector<uint> bufer(n);
        if (a.size() == 1)  return;

        for (int i = 0; i < 32; i+=eight)
        {
            point[0] = 0;
            for (int k = 0; k < FF; ++k) buf[k] = 0;
            for (int k = 0; k < n; ++k) ++buf[mid[k] >> i & FE];
            for (int k = 1; k < FF; ++k) point[k] = point[k - 1] + buf[k - 1];
            for (int k = 0; k < n; ++k) bufer[point[mid[k] >> i & FE]++] = mid[k];
            mid.swap(bufer);
        }
        for(size_t i=0;i<mid.size();++i)
        {
            a[i].x=mid[i]/10000;
            a[i].y=mid[i]%10000;
        }
        Point p1 = a[0],  p2 = a.back();
        std::vector<Point> up, down;
        up.push_back (p1);
        down.push_back (p1);
        for (size_t i=1; i<a.size(); ++i)
        {
            if (i==a.size()-1 || ClockWise(p1, a[i], p2))
            {
                while (up.size()>=2 && !ClockWise(up[up.size()-2], up[up.size()-1], a[i])) up.pop_back();
                up.push_back (a[i]);
            }
            if (i==a.size()-1 || CounterClockWise(p1, a[i], p2))
            {
                while (down.size()>=2 && !CounterClockWise(down[down.size()-2], down[down.size()-1], a[i])) down.pop_back();
                down.push_back (a[i]);
            }
        }
        a.clear();
        for (size_t i=0; i<up.size(); ++i) a.push_back (up[i]);
        for (size_t i=down.size()-2; i>0; --i) a.push_back (down[i]);
    }

//---------------------------------------------------------------------
bool cmp (Point& a, Point& b) {
	return (a.x < b.x) || ((a.x == b.x) && a.y < b.y);
}

bool cw (Point& a, Point& b, Point& c) {
	return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}

bool ccw (Point& a, Point& b, Point& c) {
	return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}

void convex_hull_2 (std::vector<Point> & a) {
	if (a.size() == 1)  return;
	std::sort (a.begin(), a.end(), &cmp);
	Point p1 = a[0],  p2= a.back();
	std::vector<Point> up, down;
	up.push_back (p1);
	down.push_back (p1);
	for (size_t i=1; i<a.size(); ++i) {
		if (i==a.size()-1 || cw (p1, a[i], p2)) {
			while (up.size()>=2 && !cw (up[up.size()-2], up[up.size()-1], a[i]))
				up.pop_back();
			up.push_back (a[i]);
		}
		if (i==a.size()-1 || ccw (p1, a[i], p2)) {
			while (down.size()>=2 && !ccw (down[down.size()-2], down[down.size()-1], a[i]))
				down.pop_back();
			down.push_back (a[i]);
		}
	}
	a.clear();
	for (size_t i=0; i<up.size(); ++i)
		a.push_back (up[i]);
	for (size_t i=down.size()-2; i>0; --i)
		a.push_back (down[i]);
}

}

using namespace hull;
int main()
{
    int n=55000000;
    vector<Point> a,b;
    Point c;
    int c1,c2;
    for(int i=0;i<n;++i)
    {
        c1=rand()%10000;
        c2=rand()%10000;
        c.x=c1;
        c.y=c2;
        a.push_back(c);
        b.push_back(c);
    }
    clock_t start1 = clock();
    convex_hull(a);
    clock_t end1 = clock();
    clock_t start2 = clock();
    convex_hull_2(b);
    clock_t end2 = clock();
    printf("Amount of points : %d\n",n);
    printf("MyAlgorithm:\nTime O(N) = %.4f\nGrekhem:\nTime O(N*logN) = %.4f\n",(double)(end1 - start1) / CLOCKS_PER_SEC,(double)(end2 - start2) / CLOCKS_PER_SEC);
    system("pause");
    return 0;
}
