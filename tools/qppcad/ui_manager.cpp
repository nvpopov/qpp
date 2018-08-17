#include <qppcad/ui_manager.hpp>
#include <qppcad/app.hpp>

using namespace qpp;

ui_manager::ui_manager(){
  iObjInspWidth = 300;
  iWorkPanelHeight = 35;
  iWorkPanelYOffset = 28;
}

void ui_manager::render_ui(){
  render_main_menu();
  render_task_panel();
  if(c_app::get_state().cur_task == app_task_type::TASK_WORKSPACE_EDITOR){
      render_work_panel();
      render_ws_tabs();
      render_object_inspector();
    }

  if(c_app::get_state().cur_task == app_task_type::TASK_MENDELEY_TABLE){
      render_mtable_big();
    }
}

void ui_manager::render_main_menu(){
  bool bShowExitDialog = false;
  app_state* astate = &(c_app::get_state());
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
              bShowExitDialog = true;
            }

          ImGui::EndMenu();
        }


      if (ImGui::BeginMenu("Edit")){
          ImGui::MenuItem("Undo");
          ImGui::MenuItem("Redo");
          ImGui::EndMenu();
        }

      if (ImGui::BeginMenu("View")){
          if(ImGui::BeginMenu("Debug")){
              bool bShowRTree = c_app::get_state().bDebugDrawRTree;
              static float fRTreeSize = 0.1f;
              ImGui::Checkbox("Show R-Tree", &bShowRTree);
              c_app::get_state().bDebugDrawRTree = bShowRTree;
              ImGui::SliderFloat("RTree line size", &fRTreeSize, 0.1, 2.0);
              ImGui::EndMenu();
            }
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
      ImGui::Separator();
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
      ImGui::Separator();
      ImGui::SameLine();

      //
      int iCurWS = astate->_workspace_manager->iCurrentWorkSpace;
      std::vector<std::string>  vStr;
      std::vector<char*>  vChar;
      for (int i = 0; i < astate->_workspace_manager->ws.size(); i++)
        vStr.push_back(astate->_workspace_manager->ws[i]->ws_name);
      std::transform(vStr.begin(), vStr.end(),
                     std::back_inserter(vChar),
                     vec_str_to_char);
      ImGui::PushItemWidth(150);
      ImGui::Combo("Workspace", &iCurWS, vChar.data(),
                   astate->_workspace_manager->ws.size());
      ImGui::PopItemWidth();

      for ( size_t i = 0 ; i < vChar.size() ; i++ ) delete [] vChar[i];
      astate->_workspace_manager->iCurrentWorkSpace = iCurWS;
      //

      if (ImGui::Button("New")){

        }

      if (ImGui::Button("Del")){

        }

      if (ImGui::Button("Ren")){

        }

      ImGui::Separator();
      ImGui::SameLine();
      ImGui::Text(fmt::format("| FPS : {} |", c_app::get_state().FPS).c_str());

      ImGui::EndMainMenuBar();

    }

  ImGui::PopStyleVar();

  if (bShowExitDialog) ImGui::OpenPopup("Quit?");
  if (ImGui::BeginPopupModal("Quit?")){
      ImGui::Text("Do you want to quit?");
      if (ImGui::Button("Yes", ImVec2(120, 40))){
          //ImGui::CloseCurrentPopup();
          exit(0);
        }
      ImGui::SameLine();
      if (ImGui::Button("No", ImVec2(120, 40))){
          ImGui::CloseCurrentPopup();
        }
      ImGui::SetItemDefaultFocus();
      ImGui::EndPopup();
    }
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
  ImGui::Button("Rx" , ImVec2(20,20));

  ImGui::SameLine();
  ImGui::Button("Ry" , ImVec2(20,20));

  ImGui::SameLine();
  ImGui::Button("Rz" , ImVec2(20,20));

  ImGui::SameLine();
  ImGui::Button("Tx" , ImVec2(20,20));

  ImGui::SameLine();
  ImGui::Button("Ty" , ImVec2(20,20));

  ImGui::SameLine();
  ImGui::Button("Tz" , ImVec2(20,20));

  ImGui::SameLine();
  ImGui::Spacing();

  if (c_app::get_state()._camera != NULL){
      int e_camera_proj = c_app::get_state()._camera->cur_proj;
      ImGui::SameLine();
      ImGui::RadioButton("Persp", &e_camera_proj,
                         int(
                           app_camera_proj_type::CAMERA_PROJ_PERSP));
      ImGui::SameLine();
      ImGui::RadioButton("Ortho", &e_camera_proj,
                         int(
                           app_camera_proj_type::CAMERA_PROJ_ORTHO));
      c_app::get_state()._camera->cur_proj = app_camera_proj_type(
            e_camera_proj);

      ImGui::SameLine();
      if (ImGui::Button("Reset cam" , ImVec2(80,20))){
          c_app::get_state()._workspace_manager->
              get_current_workspace()->reset_camera();
        }
    }

  bool bCartAxis = c_app::get_state().bDrawAxis;
  ImGui::SameLine();
  ImGui::Checkbox("Cart. Axis" , &bCartAxis);
  c_app::get_state().bDrawAxis = bCartAxis;

  bool bDrawGrid = c_app::get_state().bDrawGrid;
  ImGui::SameLine();
  ImGui::Checkbox("Grid XY" , &bDrawGrid);
  c_app::get_state().bDrawGrid = bDrawGrid;

  ImGui::End();
  ImGui::PopStyleVar();
}

void ui_manager::render_task_panel(){

}

void ui_manager::render_ws_tabs(){
  //  ImGui::SetNextWindowSize(ImVec2(c_app::get_state().wWidth - iObjInspWidth ,
  //                                  35
  //                                  ));
  //  ImGui::SetNextWindowPos(ImVec2(0,
  //                                 iWorkPanelYOffset + iWorkPanelHeight));

  // ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  // ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.f);

  //  if (ImGui::Begin("tanb", NULL,
  //               ImGuiWindowFlags_NoMove |
  //               ImGuiWindowFlags_NoResize |
  //               ImGuiWindowFlags_NoCollapse |
  //               ImGuiWindowFlags_NoNavFocus |
  //               ImGuiWindowFlags_NoTitleBar)){
  // // ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1.0f);
  //  ImGui::Button("workspace1");
  //  //ImGui::PopStyleVar();
  //    }
  //  ImGui::End();

  //  ImGui::PopStyleVar(2);

}

void ui_manager::render_object_inspector(){

  app_state* astate = &(c_app::get_state());

  ImGui::SetNextWindowSize(ImVec2(iObjInspWidth ,
                                  astate->wHeight-(iWorkPanelYOffset +
                                                   iWorkPanelHeight)
                                  ));
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
  ImGui::Separator();
  ImGui::Button("Add geom ");
  ImGui::SameLine();
  ImGui::Button("Import geom ");
  ImGui::Separator();
  int iCurWs = astate->_workspace_manager->iCurrentWorkSpace;
  workspace* cur_ws = astate->_workspace_manager->ws[iCurWs];
  if (cur_ws != NULL)
    for (int i = 0; i < cur_ws->ws_items.size(); i++){
        bool _clp = ImGui::CollapsingHeader(cur_ws->ws_items.at(i)->name.c_str());
        if (_clp) cur_ws->ws_items.at(i)->render_ui();
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
