#ifndef BACKGROUND_WIDGET_H_INCLUDED
#define BACKGROUND_WIDGET_H_INCLUDED

#include "widget.h"
#include "graphics.hpp"
#include <sstream>

struct Background_Widget : public Widget
{
protected:
    int margin = 3;
    int r = 0;
    int g = 0;
    int b = 0;
    void draw();
    std::string get_value();

public:
    Background_Widget(int _beg_x, int _beg_y, int _end_x, int _end_y, bool _focusable,int _id,int margin, int _r, int _g, int _b);
    void event_handler(genv::event &e);
};

#endif // WIDGET_H_INCLUDED
