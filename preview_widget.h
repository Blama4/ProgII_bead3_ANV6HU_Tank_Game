
#ifndef PREVIEW_WIDGET_H_INCLUDED
#define PREVIEW_WIDGET_H_INCLUDED

#include "widget.h"
#include "graphics.hpp"
#include <sstream>
#include <fstream>
struct Preview_Widget : public Widget
{
protected:
    int margin = 3;
    int r,g,b;
    bool enemy;
    std::string inputkep;
    void draw();
    std::string get_value();

public:
    Preview_Widget(int _beg_x, int _beg_y, int _end_x, int _end_y, bool _focusable, std::string _inputkep,int _r, int _g, int _b, bool enemy);
    void event_handler(genv::event &e);
    void inputkepsetter(std::string newkep);
};

#endif // WIDGET_H_INCLUDED

