#ifndef Component_H
#define Component_H

class Component {
public:
	Component(std::string volume, double x_pos, double y_pos, double z_pos, double alpha, double beta, double gamma):_volume(volume),_x_pos(x_pos),_y_pos(y_pos),_z_pos(z_pos),_alpha(alpha),_beta(beta),_gamma(gamma) {;}

	
    std::string volume() {return _volume;}
	double x_pos() {return _x_pos;}
	double y_pos() {return _y_pos;}
	double z_pos() {return _z_pos;}
    double alpha() {return _alpha;}
    double beta() {return _beta;}
    double gamma() {return _gamma;}

    void volume(std::string v) {_volume = v;}
    void z_pos(double v) {_z_pos=v;}
    void x_pos(double v) {_x_pos=v;}
	void y_pos(double v) {_y_pos=v;}
    void alpha(double v) {_alpha = v;}
    void beta(double v) {_beta = v;}
    void gamma(double v) {_gamma = v;}

    
private:
    std::string _volume;
	double _x_pos;
	double _y_pos;
	double _z_pos;
    double _alpha;
    double _beta;
    double _gamma;
};

#endif
