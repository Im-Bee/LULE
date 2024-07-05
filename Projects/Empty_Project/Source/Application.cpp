#include "Application.hpp"

LULE_DECL_ENTRY_APPLICATION(EmptyProject::Application);

void EmptyProject::Application::Initialize() {
	L_LOG(LULE::Debug::Info, L"Text");
	L_LOG(LULE::Debug::Info, L"Nie text");
}

void EmptyProject::Application::Update() {
}

void EmptyProject::Application::Destroy() {
}
