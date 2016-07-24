//
//  graphics.cpp
//  splashkit
//
//  Created by Andrew Cain on 23/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "graphics.h"
#include "window_manager.h"
#include "utils.h"
#include "drawing_options.h"
#include "camera.h"

#include "utility_functions.h"

#include "graphics_driver.h"

#include <map>

using namespace std;

extern map<string, window> _windows;

static unsigned int _last_update_time = 0;

void refresh_screen()
{
    refresh_screen(60);
}

void refresh_screen(unsigned int target_fps)
{
    for (const auto& kv : _windows)
    {
        refresh_window(kv.second);
    }

    unsigned int now = current_ticks();
    unsigned int delta = now - _last_update_time;
    unsigned int delay_time;

    //dont sleep if 5ms remaining...
    while ((target_fps > 0) and ((delta + 8) * target_fps < 1000))
    {
        delay_time = (1000 / target_fps) - delta;
        delay(delay_time);
        now = current_ticks();
        delta = now - _last_update_time;
    }

    _last_update_time = now;
}

//----------------------------------------------------------------------------
// Circle drawing
//----------------------------------------------------------------------------


void draw_circle(color clr, float x, float y, float radius, drawing_options opts)
{
    sk_drawing_surface *surface;
    
    surface = to_surface_ptr(opts.dest);
    
    xy_from_opts(opts, x, y);
    
    if (surface)
        sk_draw_circle(surface, clr, x, y, radius);
}

void draw_circle(color clr, float x, float y, float radius)
{
    draw_circle(clr, x, y, radius, option_defaults());
}

void draw_circle(color clr, circle &c, drawing_options opts)
{
    draw_circle(clr, c.center.x, c.center.y, c.radius, opts);
}

void draw_circle(color clr, circle &c)
{
    draw_circle(clr, c.center.x, c.center.y, c.radius, option_defaults());
}


void fill_circle(color clr, float x, float y, float radius, drawing_options opts)
{
    sk_drawing_surface *surface;
    
    surface = to_surface_ptr(opts.dest);
    
    xy_from_opts(opts, x, y);
    
    if (surface)
        sk_fill_circle(surface, clr, x, y, radius);
}

void fill_circle(color clr, float x, float y, float radius)
{
    fill_circle(clr, x, y, radius, option_defaults());
}

void fill_circle(color clr, circle &c,drawing_options opts)
{
    fill_circle(clr, c.center.x, c.center.y, c.radius, opts);
}

void fill_circle(color clr, circle &c)
{
    fill_circle(clr, c.center.x, c.center.y, c.radius, option_defaults());
}

