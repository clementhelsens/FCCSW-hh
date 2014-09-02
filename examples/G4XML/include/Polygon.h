#ifndef Polygon_H
#define Polygon_H

class Polygon {
public:
	Polygon(double polygon1, double polygon2):_polygon1(polygon1),_polygon2(polygon2) {;}
	double extract1() {return _polygon1;}
    double extract2() {return _polygon2;}
	void fill(std::vector<double> vvv) {_polygon1= vvv[0],_polygon2=vvv[1];}
	private:

    double _polygon1;
    double _polygon2;
};

#endif
