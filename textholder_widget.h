
#ifndef TEXTHOLDER_WIDGET_H_INCLUDED
#define TEXTHOLDER_WIDGET_H_INCLUDED

#include "widget.h"
#include "graphics.hpp"
#include <sstream>
struct TextHolder_Widget : public Widget
{
protected:
    int margin = 3;
    int r,g,b;
    std::string textin;

    void textsetter(std::string newtext);
    void draw();
    std::string get_value();

public:
    TextHolder_Widget(int _beg_x, int _beg_y, int _end_x, int _end_y, bool _focusable, std::string _textin, int _r, int _g, int _b, int _margin);
    void event_handler(genv::event &e);
};

#endif // WIDGET_H_INCLUDED

