#ifndef _QPP_APP_STATE_H
#define _QPP_APP_STATE_H

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <imgui.h>


namespace qpp {

    class app_state {
    public:

        int wWidth;
        int wHeight;

        app_state(){
            wWidth  = 600;
            wHeight = 600;
        }

    };
}

#endif
