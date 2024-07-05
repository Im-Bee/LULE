#ifndef LULE_APPPROPS_H
#define LULE_APPPROPS_H

#include <vector>

namespace LULE::Application {

    enum LULE_API KnownPaths {
        Executable,
        UserAppData,
        None
    };

#	pragma warning(push)
#	pragma warning(disable : 4251)
    // Warning	C4251	class needs to have dll - interface to be used by clients
    class LULE_API AppProperties {
        AppProperties() = default;

        AppProperties(AppProperties&&) = delete;
        AppProperties(const AppProperties&) = delete;

    public:
        static AppProperties& Get() {
            static AppProperties instance;
            return instance;
        }

        ~AppProperties() = default;

    public:
        static std::wstring GetKnownPath(const KnownPaths& kp);

    private:
        static void FindKnownPaths(std::vector<std::wstring>& vec);

        static void TrimPathExe(std::wstring& path);

        static void FindExectuablePath(std::wstring& dest);
        static void FindUserAppdataPath(std::wstring& dest);
    };
#	pragma warning(pop)
}

#endif // !LULE_APPPROPS_H
