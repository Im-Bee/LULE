#include "LULE_Multiplatform.h"

#include <filesystem>
#include <shlobj_core.h>

// Public ----------------------------------------------------------------------

// -----------------------------------------------------------------------------
std::wstring LULE::Application::AppProperties::GetKnownPath(const KnownPaths& kp) {
	static std::vector<std::wstring> vecKnown = {};
	if (vecKnown.empty())
		FindKnownPaths(vecKnown);

	return vecKnown[kp];
}

// Private ---------------------------------------------------------------------

// -----------------------------------------------------------------------------
void LULE::Application::AppProperties::FindKnownPaths(std::vector<std::wstring>& vec) {
	for (LUINT8 i = 0; i < KnownPaths::None; ++i) {
		vec.push_back(new LWCHAR[LULE_PATH_MAX_SIZE]());

		switch (i) {
		case KnownPaths::Executable:
			AppProperties::FindExectuablePath(vec[i]);
			continue;
		case KnownPaths::UserAppData:
			AppProperties::FindUserAppdataPath(vec[i]);
			continue;
		default:
			throw;
		}
	}
}

// -----------------------------------------------------------------------------
void LULE::Application::AppProperties::TrimPathExe(std::wstring& path) {
	// Check if it's null terminated
	if (path.size() >= LULE_PATH_MAX_SIZE)
		throw;

	// Force to find the last slash
	auto i = path.find_last_of(L'\\');
	if (i == std::string::npos)
		i = path.find_first_of(L'/');

	// Something is not okay, throw
	if (i == std::string::npos)
		throw;

	// Trim the path
	path.erase(i + 1);
}

// -----------------------------------------------------------------------------
void LULE::Application::AppProperties::FindExectuablePath(std::wstring& dest) {
#ifdef _WIN32
	LWCHAR tmp[LULE_PATH_MAX_SIZE] = { 0 };
	GetModuleFileName(NULL, tmp, LULE_PATH_MAX_SIZE);
	dest = tmp;
	TrimPathExe(dest);
#else
#	error "Couldn't detect the system, void LULE::Application::AppProperties::FindExectuablePath(LWCHAR* dest) not avalible."
#endif // _WIN32
}

// -----------------------------------------------------------------------------
void LULE::Application::AppProperties::FindUserAppdataPath(std::wstring& dest) {
#ifdef _WIN32
	PWSTR tmp = {};
	SHGetKnownFolderPath(
		FOLDERID_RoamingAppData,
		0,
		nullptr,
		&tmp);
	dest = tmp;
	dest += L"\\LULE\\";
	CoTaskMemFree(tmp);

	// Check if directory exists
	if (!std::filesystem::exists(dest)) {
		std::filesystem::create_directories(dest);
	}
#else
#	error "Couldn't detect the system, void LULE::Application::AppProperties::FindExectuablePath(LWCHAR* dest) not avalible."
#endif // _WIN32
}
