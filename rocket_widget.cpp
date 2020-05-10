
#include "rocket_widget.h"
Rocket_Widget::Rocket_Widget(int _beg_x, int _beg_y, int _deg, int speed, bool enemy, std::string _inputkep):Widget(_beg_x, _beg_y)
{
    type = "Rocket";
    inputkep = _inputkep;
    enemy = _enemy;
    angle = _deg;
    Vo = _speed;
    inputkep = _inputkep;


    ifstream f("rocket.kep");
    if(!f.good())
    {
        genv::gout<<genv::text("rocket.kep beolvasása sikertelen!")<<endl;
    }
    f>>X_kep>>Y_kep;
    RocketPicture rocket;
    for(int i = 0; i<Y_kep; ++i)
    {
        for(int y = 0; y<X_kep; ++y)
        {
            rocket.x=y;
            rocket.y=i;
            f>>r>>g>>b;
            rocket.r=r;
            rocket.g=g;
            rocket.b=b;
            RocketMatrix.push_back(rocket);
        }
    }
}


RocketPicture::void draw(int x_offset, int y_offset, double degt)
    {
        double deg = -degt-pi/2;
        double tmpx = cos(deg)*x+x_offset+sin(deg)*y;
        double tmpy = -sin(deg)*x+cos(deg)*y+y_offset;
        gout<<move_to(tmpx,tmpy);
        gout<<color(r,g,b);
        gout<<dot;
    }

std::string Preview_Widget::get_value()
{
    return "ROCKET VAGYOK";
}
void Preview_Widget::event_handler(genv::event &e)
{
    if (ev.type == ev_timer && ev.type !=ev_key)
        {
            if(fire && y<=y_offset)
            {
                double oldy;
                double oldx;
                int x = time-bg_time;
                double rad = angle*pi/180;
                double tmp1 = x * tan(rad);
                double tmp2 = gravity/(2*pow(Vo,2)*pow(cos(rad),2));
                double tmp3 = pow(x,2);
                y=Y-(tmp1-tmp2*tmp3)-(Y-y_offset);
                double degree = sin((y-oldy)/(sqrt(pow(x-oldx,2)+pow(y-oldy,2))));
                oldy = y;
                oldx = x;
                for(size_t i = 0; i<RocketMatrix.size(); ++i)
                {
                    RocketMatrix[i].draw(x+x_offset,y,degree);
                }
            }
            gout<<refresh;
            cclear();
            time=time+10;
        }
        if(ev.type==ev_key && ev.keycode==key_space)
        {
            fire = true;
            bg_time = time;
        }
    }
}

