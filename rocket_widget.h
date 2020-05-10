#ifndef ROCKET_WIDGET_H_INCLUDED
#define ROCKET_WIDGET_H_INCLUDED

#include "widget.h"
#include "graphics.hpp"
#include <sstream>
#include <fstream>

struct RocketPicture
{
    int x,y;
    int r,g,b;
    void draw(int x_offset, int y_offset, double degt);
};

struct Rocket_Widget : public Widget
{
protected:
    int r,g,b;
    int x,y;
    int gravity = 10;
    int time = 0;
    int bg_time = 0;
    int y_offset;
    int x_offset;
    int X_kep,Y_kep;
    double angle;
    double Vo;
    double x = 0;
    double y = 0;
    bool enemy;
    bool fire = false;
    std::string inputkep;
    vector<RocketPicture>RocketMatrix;

    void draw();
    std::string get_value();

public:
    Rocket_Widget(int _beg_x, int _beg_y, int _deg, int speed, bool enemy, std::string _inputkep);
    void event_handler(genv::event &e);
    bool hit(int beg_x int beg_y, int end_x, int end_y);
};

#endif // WIDGET_H_INCLUDED


