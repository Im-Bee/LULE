#ifndef LULE_IAPPLICATION_H
#define LULE_IAPPLICATION_H

#define LULE_DECL_ENTRY_APPLICATION(implClass) LULE::IApplication* LULE::EntryApplication() { return new implClass; }

namespace LULE {

	class LULE_API IApplication {
	public:
		IApplication() = default;
		~IApplication() = default;

		IApplication(IApplication&&) = delete;
		IApplication(const IApplication&) = delete;

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual void Destroy() = 0;
	};

	IApplication* EntryApplication();
}

#endif // !LULE_IAPPLICATION_H
