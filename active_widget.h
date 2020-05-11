#ifndef ACTIVE_WIDGET_H_INCLUDED
#define ACTIVE_WIDGET_H_INCLUDED

#include "widget.h"
#include "graphics.hpp"
struct Active_Widget : public Widget
{
protected:
    int margin = 3;
    int r,g,b;
    bool active;
    void draw();
    std::string get_value();

public:
    Active_Widget(int _beg_x, int _beg_y, int _end_x, int _end_y, bool _focusable, int _id, bool _active, int _r, int _g, int _b);
    void event_handler(genv::event &e);
    bool getfocused();
    int getid();
    bool getactive();
    void setactive(bool inac);
};

#endif // WIDGET_H_INCLUDED

