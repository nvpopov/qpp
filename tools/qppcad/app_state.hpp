#ifndef _QPP_APP_STATE_H
#define _QPP_APP_STATE_H

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <imgui.h>
#include <qppcad/draw_style.hpp>
#include <qppcad/workspace.hpp>
#include <qppcad/mesh.hpp>
#include <qppcad/shader_program.hpp>

namespace qpp {

    class app_state {
    public:
        draw_style* _draw_style;
        shader_program* def_shader;

        workspace_manager* _workspace_manager;

        // sphere mesh with differnet resolutions
        std::vector<mesh*> _sph_meshes;
        mesh* trm;

        vector3<float> camPos;
        vector3<float> camLookAt;
        vector3<float> gUpAxis;

        int wWidth;
        int wHeight;

        app_state(){

            camPos = vector3<float>(-5.0, 0.0, 0.0);
            camLookAt = vector3<float>(0.0, 0.0, 0.0);
            gUpAxis = vector3<float>(0.0, 0.0, 1.0);

            _workspace_manager = new workspace_manager();
            wWidth  = 600;
            wHeight = 600;

            _draw_style = new default_draw_style();
            //unit sphere
            _sph_meshes.push_back(new sphere_mesh(1.0, 12, 12));
            trm = new test_triangle_mesh();
            def_shader = gen_default_program();

            _workspace_manager->init_default_workspace();
        }

    };
}

#endif
