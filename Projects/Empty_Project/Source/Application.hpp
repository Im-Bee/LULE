#ifndef APPLICATION_H
#define APPLICATION_H

#include "EntryPoints/Win32/Entry.hpp"

#include "LULE_Debug.h"

namespace EmptyProject {
	class Application : public LULE::IApplication {
	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Destroy() override;
	};
}

#endif // !APPLICATION_H
