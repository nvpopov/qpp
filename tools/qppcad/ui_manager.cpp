#include <qppcad/ui_manager.hpp>

using namespace qpp;

ui_manager::ui_manager(){

}

void ui_manager::render_ui(){
  render_main_menu();
  render_object_inspector();
}

void ui_manager::render_main_menu(){
  if (ImGui::BeginMainMenuBar()){
      if (ImGui::BeginMenu("File")){
          ImGui::MenuItem("New");
          ImGui::MenuItem("Open");
          ImGui::MenuItem("Save");
          ImGui::MenuItem("Save as");
          ImGui::MenuItem("Exit");
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

      ImGui::EndMainMenuBar();

    }
}

void ui_manager::render_object_inspector(){

}
