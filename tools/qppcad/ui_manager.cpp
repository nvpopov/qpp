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

      ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4,4));
      if (ImGui::BeginMenu("File")){
          ImGui::MenuItem("New");
          ImGui::MenuItem("Open");
          if (ImGui::BeginMenu("Import")){
              ImGui::MenuItem("Standart XYZ(0D)");
              ImGui::MenuItem("VASP POSCAR/CONTCAR)");
              ImGui::EndMenu();
            }
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
              ImGui::Checkbox("Show tws-Tree",
                              &(c_app::get_state().bDebugDrawRTree));
              ImGui::Checkbox("Show debug selection ray",
                              &(c_app::get_state().bDebugDrawSelectionRay));
              ImGui::EndMenu();
            }

          ImGui::Checkbox("Cartesian Axis" , &(c_app::get_state().bDrawAxis));
          ImGui::Checkbox("Grid XY" , &(c_app::get_state().bDrawGrid));

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

      ImGui::PopStyleVar();

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
  ImGui::Begin("task_panel", nullptr,
               ImGuiWindowFlags_NoTitleBar |
               ImGuiWindowFlags_NoMove |
               ImGuiWindowFlags_NoResize |
               ImGuiWindowFlags_NoScrollbar |
               ImGuiWindowFlags_NoBringToFrontOnFocus);
  ImGuiWindow* window = ImGui::GetCurrentWindow();
  window->DC.LayoutType = ImGuiLayoutType_Horizontal;

  ImGui::Button("a" , ImVec2(20,20));
  ImGui::Button("b" , ImVec2(20,20));
  ImGui::Button("c" , ImVec2(20,20));
  ImGui::Separator();

  ImGui::Button("Rx" , ImVec2(20,20));
  ImGui::Button("Ry" , ImVec2(20,20));
  ImGui::Button("Rz" , ImVec2(20,20));
  ImGui::Separator();

  ImGui::Button("Tx" , ImVec2(20,20));
  ImGui::Button("Ty" , ImVec2(20,20));
  ImGui::Button("Tz" , ImVec2(20,20));
  ImGui::Separator();

  ImGui::Text("Edit mode:");
  int edit_mode = int(c_app::get_state().cur_edit_type);
  ImGui::BeginTabs("newtab", 2, edit_mode, 60 );
  if (ImGui::AddTab( "NODE")) {
      c_app::get_state().cur_edit_type = app_edit_type::EDIT_WS_ITEM;
    }

  if (ImGui::AddTab( "CONTENT")) {
      c_app::get_state().cur_edit_type = app_edit_type::EDIT_WS_ITEM_CONTENT;
    }
  ImGui::EndTabs();
  c_app::get_state().cur_edit_type = app_edit_type(edit_mode);

  ImGui::Spacing();
  ImGui::Separator();


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
  ImGui::Begin("Object inspector", nullptr,
               ImGuiWindowFlags_NoMove |
               ImGuiWindowFlags_NoResize |
               ImGuiWindowFlags_NoCollapse);

  ImGui::Separator();
  ImGui::Button("Add geom ");
  ImGui::SameLine();
  ImGui::Button("Import geom ");
  ImGui::Separator();
  auto iCurWs = astate->_workspace_manager->iCurrentWorkSpace;
  workspace* cur_ws = astate->_workspace_manager->ws[iCurWs];
  if (cur_ws != nullptr)
    for (ws_item* ws_it : cur_ws->ws_items){
        bool _clp = ImGui::CollapsingHeader(ws_it->name.c_str());
        if (_clp) ws_it->render_ui();
      }


  ImGui::End();
  ImGui::PopStyleVar();

}

void ui_manager::render_mtable_big(){
  float mendFrm = 0.85f;
  ImGui::SetNextWindowSize(ImVec2(c_app::get_state().wWidth*mendFrm ,
                                  c_app::get_state().wHeight*mendFrm));
  ImGui::SetNextWindowPos(ImVec2(c_app::get_state().wWidth*(1-mendFrm)*0.5f,
                                 c_app::get_state().wHeight*(1-mendFrm)*0.5f));

  ImGui::Begin("Mendeley table", nullptr,
               ImGuiWindowFlags_NoMove |
               ImGuiWindowFlags_NoResize |
               ImGuiWindowFlags_NoCollapse);

  ImGui::End();
}

