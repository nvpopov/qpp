#include <qppcad/ui_manager.hpp>
#include <qppcad/app.hpp>

using namespace qpp;

ui_manager::ui_manager(){
  iObjInspWidth = 250;
  iWorkPanelHeight = 35;
  iWorkPanelYOffset = 28;
}

void ui_manager::render_ui(){
  render_main_menu();
  render_task_panel();
  if(c_app::get_state().cur_task == app_task_type::TASK_WORKSPACE_EDITOR){
      render_work_panel();
      render_object_inspector();
    }

  if(c_app::get_state().cur_task == app_task_type::TASK_MENDELEY_TABLE){
      render_mtable_big();
    }
}

void ui_manager::render_main_menu(){

  //
  //ImGui::PushStyleVar(, ImVec2(0.85, 2.85));
  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8,8));

  if (ImGui::BeginMainMenuBar()){

      if (ImGui::BeginMenu("File")){
          ImGui::MenuItem("New");
          ImGui::MenuItem("Open");
          ImGui::MenuItem("Save");
          ImGui::MenuItem("Save as");

          if (ImGui::MenuItem("Exit")){

              qpp::c_app::log("Menu -> File -> Exit clicked");
              ImGui::OpenPopup("Warning");
              bool _show_exit_md = true;
              if (ImGui::BeginPopupModal("Warning",
                                         nullptr,
                                         ImGuiWindowFlags_AlwaysAutoResize)){
                  ImGui::Text("Do you want to quit?");
                  if (ImGui::Button("Yes", ImVec2(120, 40))){
                      //ImGui::CloseCurrentPopup();
                      exit(0);
                    }
                  if (ImGui::Button("No", ImVec2(120, 40))){
                      //ImGui::CloseCurrentPopup();
                    }

                  ImGui::SetItemDefaultFocus();
                  ImGui::EndPopup();
                }

            }

          ImGui::EndMenu();
        }


      if (ImGui::BeginMenu("Edit")){
          ImGui::MenuItem("Undo");
          ImGui::MenuItem("Redo");
          ImGui::EndMenu();
        }

      if (ImGui::BeginMenu("Tools")){
          ImGui::MenuItem("Tool1");
          ImGui::MenuItem("Tool2");
          ImGui::EndMenu();
        }

      if (ImGui::BeginMenu("Help")){
          ImGui::MenuItem("Help1");
          ImGui::MenuItem("Help2");
          ImGui::EndMenu();
        }

      int e_task = c_app::get_state().cur_task;
      ImGui::SameLine();
      ImGui::RadioButton("Workspace editor", &e_task,
                         int(app_task_type::TASK_WORKSPACE_EDITOR));
      ImGui::SameLine();
      ImGui::RadioButton("Node editor", &e_task,
                         int(app_task_type::TASK_NODE_EDITOR));
      ImGui::SameLine();
      ImGui::RadioButton("Mendeley table", &e_task,
                         int(app_task_type::TASK_MENDELEY_TABLE));
      c_app::get_state().cur_task = app_task_type(e_task);
      ImGui::SameLine();
      ImGui::Text(fmt::format("| FPS : {} |", c_app::get_state().FPS).c_str());


      ImGui::EndMainMenuBar();

    }
  ImGui::PopStyleVar();
  //
}

void ui_manager::render_work_panel(){
  ImGui::SetNextWindowSize(ImVec2( c_app::get_state().wWidth, iWorkPanelHeight));
  ImGui::SetNextWindowPos(ImVec2(0, iWorkPanelYOffset));
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  //ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.1f);
  ImGui::Begin("task_panel", NULL,
               ImGuiWindowFlags_NoTitleBar |
               ImGuiWindowFlags_NoMove |
               ImGuiWindowFlags_NoResize |
               ImGuiWindowFlags_NoScrollbar |
               ImGuiWindowFlags_NoBringToFrontOnFocus);

  ImGui::Button("a" , ImVec2(20,20));

  ImGui::SameLine();
  ImGui::Button("b" , ImVec2(20,20));

  ImGui::SameLine();
  ImGui::Button("c" , ImVec2(20,20));

  ImGui::SameLine();
  ImGui::Spacing();

  ImGui::SameLine();
  ImGui::Button("Rx" , ImVec2(20,20));

  ImGui::SameLine();
  ImGui::Button("Ry" , ImVec2(20,20));

  ImGui::SameLine();
  ImGui::Button("Rz" , ImVec2(20,20));

  ImGui::SameLine();
  ImGui::Spacing();

  ImGui::SameLine();
  ImGui::Button("Tx" , ImVec2(20,20));

  ImGui::SameLine();
  ImGui::Button("Ty" , ImVec2(20,20));

  ImGui::SameLine();
  ImGui::Button("Tz" , ImVec2(20,20));

  ImGui::SameLine();
  ImGui::Spacing();

  int e_camera_proj = c_app::get_state().cur_proj;
  ImGui::SameLine();
  ImGui::RadioButton("Persp", &e_camera_proj,
                     int(app_camera_proj_type::CAMERA_PROJ_PERSP));
  ImGui::SameLine();
  ImGui::RadioButton("Ortho", &e_camera_proj,
                     int(app_camera_proj_type::CAMERA_PROJ_ORTHO));
  c_app::get_state().cur_proj = app_camera_proj_type(e_camera_proj);

  ImGui::SameLine();
  if (ImGui::Button("Reset cam" , ImVec2(80,20))){
      c_app::get_state().reset_camera();
    }

  bool bCartAxis = c_app::get_state().bDrawAxis;
  ImGui::SameLine();
  ImGui::Checkbox("Cart. Axis" , &bCartAxis);
  c_app::get_state().bDrawAxis = bCartAxis;

  ImGui::End();
  ImGui::PopStyleVar();
}

void ui_manager::render_task_panel(){

}

void ui_manager::render_object_inspector(){

  app_state* astate = &(c_app::get_state());

  ImGui::SetNextWindowSize(ImVec2(iObjInspWidth , astate->wHeight*0.95));
  ImGui::SetNextWindowPos(ImVec2(astate->wWidth - iObjInspWidth,
                                 iWorkPanelYOffset + iWorkPanelHeight));


  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::Begin("Object inspector", NULL,
               ImGuiWindowFlags_NoMove |
               ImGuiWindowFlags_NoResize |
               ImGuiWindowFlags_NoCollapse);

  //  ImGui::BeginGroup();
  //      ImGui::Button("Workspace\neditor" , ImVec2(75,40));
  //      ImGui::Button("Node\neditor" , ImVec2(75,40));
  //      ImGui::Button("Mendeley\ntable" , ImVec2(75,40));
  //  ImGui::EndGroup();
  int iCurWs = astate->_workspace_manager->iCurrentWorkSpace;
  workspace* cur_ws = astate->_workspace_manager->ws[iCurWs];
  if (cur_ws != NULL)
    for (int i = 0; i < cur_ws->ws_items.size(); i++){
      if (ImGui::CollapsingHeader(cur_ws->ws_items.at(i)->name.c_str()))
          cur_ws->ws_items.at(i)->render_ui();
    }


  ImGui::End();
  ImGui::PopStyleVar();

}

void ui_manager::render_mtable_big(){
  float mendFrm = 0.85;
  ImGui::SetNextWindowSize(ImVec2(c_app::get_state().wWidth*mendFrm ,
                                  c_app::get_state().wHeight*mendFrm));
  ImGui::SetNextWindowPos(ImVec2(c_app::get_state().wWidth*(1-mendFrm)*0.5,
                                 c_app::get_state().wHeight*(1-mendFrm)*0.5));

  ImGui::Begin("Mendeley table", NULL,
               ImGuiWindowFlags_NoMove |
               ImGuiWindowFlags_NoResize |
               ImGuiWindowFlags_NoCollapse);

  //  ImGui::BeginGroup();
  //      ImGui::Button("Workspace\neditor" , ImVec2(75,40));
  //      ImGui::Button("Node\neditor" , ImVec2(75,40));
  //      ImGui::Button("Mendeley\ntable" , ImVec2(75,40));
  //  ImGui::EndGroup();


  ImGui::End();
}
