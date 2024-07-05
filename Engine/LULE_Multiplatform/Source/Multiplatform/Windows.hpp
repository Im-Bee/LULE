#ifndef LULE_LWINDOWS_H
#define LULE_LWINDOWS_H

namespace LULE::Application {

	struct LULE_API LWindowProps {
		LUINT32 Top = 0;
		LUINT32 Left = 0;
		LUINT32 Height = 1200;
		LUINT32 Width = 800;
		LWCHAR  Title[64] = L"LULE_EMPTY_WINDOW";
	};

	/*
	* Provide basic set of functionality for windows.
	**/
	class LULE_API ILWindow {
	protected:
		LWindowProps m_Props = {};

	public:
		ILWindow() = default;
		ILWindow(LWindowProps&& props) : m_Props(std::move(props)) {};
		~ILWindow() = default;

	public:
		virtual void CreateAndRegister() = 0;
		virtual void Show() = 0;
		virtual void Hide() = 0;
		virtual void Destroy() = 0;


		// Setters ---------------------------------------------------------------------
		void SetPosition(LUINT32 x, LUINT32 y) {
			m_Props.Left = x;
			m_Props.Top = y;
			UpdateDimensions();
		}

		void SetDimensions(LUINT32 width, LUINT32 height) {
			m_Props.Height = height;
			m_Props.Width = width;
			UpdateDimensions();
		}

		// Getters ---------------------------------------------------------------------
		const LWindowProps GetProperties() { return m_Props; }

	protected:
		// Change window's properties
		virtual void UpdateDimensions() = 0;
	};

#ifdef _WIN32
	class LULE_API BaseWindow : public LULE::Application::ILWindow {
	protected:
		HWND m_HWND = nullptr;

	public:
		BaseWindow() = default;
		~BaseWindow() {
			this->Destroy();
		}

	public:
		void CreateAndRegister() override;
		void Show() override;
		void Hide() override;
		void Destroy() override;

		// Win32 specific --------------------------------------------------------------
		// This function should be overrided by derived class
		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

		// Getters ---------------------------------------------------------------------
		const HWND& GetHwnd() { return m_HWND; }

	private:
		void UpdateDimensions() override;

		// Win32 messages --------------------------------------------------------------
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
#elif __GNUC__
#endif // !_WIN32
}

#endif // !LULE_LWINDOWS_H
