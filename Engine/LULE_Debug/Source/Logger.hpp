#ifndef LULE_LOGGER_H
#define LULE_LOGGER_H

#ifdef _DEBUG
#	define L_LOG(...) LULE::Debug::Logger::Get().Log(__VA_ARGS__)
#else
#	define L_LOG(...)
#endif // _DEBUG

#include <atomic>
#include <mutex>
#include <queue>
#include <thread>

namespace LULE::Debug {

	enum Severity {
		Info = 0x00,
		Warning = 0x02,
		Error = 0x04,
		Exception = 0x08
	};

	typedef std::tuple<Severity, std::chrono::system_clock::time_point, LWCHAR*> LogMessage;
	constexpr LUINT32 LogDelay = 50;

#	pragma warning(push)
#	pragma warning(disable : 4251)
	// Warning	C4251	class needs to have dll - interface to be used by clients

	/*
	* Basic logger class.
	* Singleton, has it's own separate thread for writing to file.
	**/
	class LULE_API Logger {
		Logger() {
			StartWriteThread();
		}

		Logger(Logger&&) = delete;
		Logger(const Logger&) = delete;

		LWCHAR m_szTargetFile[LULE_PATH_MAX_SIZE] = { 0 };

		std::queue<LogMessage> m_MessageQ = std::queue<LogMessage>();
		std::mutex m_WriteLock = std::mutex();
		std::atomic<LBOOL> m_bWrite = false;
		std::thread* m_tWriteThread = nullptr;

	public:
		static Logger& Get() {
			static Logger instance;
			return instance;
		}

		~Logger() {
			StopWriteThread();
		}

	public:
		void Log(Severity s, const LWCHAR* format, ...);

	private:
		void CreateTargetFile();

		void WriteLoop();

		std::wstring CreateTag(
			const Severity& s,
			const std::chrono::system_clock::time_point& tp);

		void StartWriteThread();
		void StopWriteThread();
	};
#	pragma warning(pop)
}

#endif // !LULE_LOGGER_H