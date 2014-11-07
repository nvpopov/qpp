#include "App.hpp"

using namespace molcad;

void App::Init()
{
	Workspace* ws1 = new Workspace();
	Workspace* ws2 = new Workspace();
	this->workspaces.push_back(ws1);
	this->workspaces.push_back(ws2);
}

void App::InitGUI()
{

}

void App::ReadMolecule(std::string filename)
{

}

void App::Update(){

}

void App::InitAtomRepr()
{

}

void App::onCommand(QString)
{

}
