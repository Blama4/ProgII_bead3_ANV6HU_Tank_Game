#ifndef WIDGET_H_INCLUDED
#define WIDGET_H_INCLUDED

#include "graphics.hpp"
#include <string>
class Widget
{
protected:
    int beg_x;
    int beg_y;
    int end_x;
    int end_y;
    bool focusable;
    bool focused;
    std::string type;

public:
    Widget(int _beg_x, int _beg_y, int _end_x, int _end_y, bool _focusable);
    std::string get_type();
    void setfocused(bool sb);
    bool infocus(int pos_x, int pos_y);
    bool get_focusable();
    void draw();
    virtual std::string get_value() = 0;
    void on_click(int pos_x, int pos_y);
    virtual void event_handler(genv::event &e) = 0;
};



#endif // WIDGET_H_INCLUDED

