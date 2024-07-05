#include "Application.hpp"

LULE_DECL_ENTRY_APPLICATION(EmptyProject::Application);

void EmptyProject::Application::Initialize() {
	L_LOG(LULE::Debug::Info, L"Text");
	L_LOG(LULE::Debug::Info, L"Nie text");
	LULE::Application::LWindowProps wp = { .Title = L"What's up?" };
	LULE::Application::BaseWindow* bw = new LULE::Application::BaseWindow(wp);
	bw->CreateAndRegister();
	bw->Show();
}

void EmptyProject::Application::Update() {
}

void EmptyProject::Application::Destroy() {
}
