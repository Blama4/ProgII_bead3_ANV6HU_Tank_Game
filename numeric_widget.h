#ifndef NUMERIC_WIDGET_H_INCLUDED
#define NUMERIC_WIDGET_H_INCLUDED

#include "widget.h"
#include "graphics.hpp"
#include <sstream>
struct Num_Widget : public Widget
{
protected:
    int value;
    int max_value;
    int min_value;
    int margin = 3;
    double rate = 0.2;
    int up_c = 210;
    int do_c = 210;

    void valuesetter(bool inc, int ext);
    bool inc(int pos_x, int pos_y);
    bool dec(int pos_x, int pos_y);
    void on_click(int pos_x, int pos_y);
    void draw();
    std::string get_value();


public:
    Num_Widget(int _beg_x, int _beg_y, int _end_x, int _end_y, bool _focusable, int _id, int _value, int _max_value, int _min_value);
    void event_handler(genv::event &e);
    bool getfocused();
    void setrangemax(int inx);
    void setrangemin(int inx);
    void setvaluecenter();
};

#endif // WIDGET_H_INCLUDED
