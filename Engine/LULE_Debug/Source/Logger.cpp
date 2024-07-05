#include "LULE_Debug.h"

#include <chrono>
#include <fstream>

// Public ----------------------------------------------------------------------

// -----------------------------------------------------------------------------
void LULE::Debug::Logger::Log(Severity s, const LWCHAR* format, ...) {
	using namespace std::chrono;

#ifdef _DEBUG
	if (!m_bWrite.load()) {
		// Gate for set amount of time
		static auto tpMs = time_point_cast<milliseconds>(system_clock::now());
		auto nowMs = time_point_cast<milliseconds>(system_clock::now());
		if ((nowMs.time_since_epoch() - tpMs.time_since_epoch()) >= milliseconds(1000)) {
			L_CONSOLE_OUT(L"Logger thread isn't logging, but log was called.");

			// Update the gate
			tpMs = time_point_cast<milliseconds>(system_clock::now());
		}
	}
#endif // _DEBUG

	// Create pointer to the format,
	// that has to be deleted manualy later
	LWCHAR* formatedBuff = new LWCHAR[LULE_MESSAGE_MAX_SIZE]();

	va_list args;
	va_start(args, format);
	vswprintf_s(formatedBuff, LULE_MESSAGE_MAX_SIZE, format, args);
	va_end(args);

	LogMessage m = std::make_tuple(s, system_clock::now(), formatedBuff);

	m_WriteLock.lock();
	m_MessageQ.push(std::move(m));
	m_WriteLock.unlock();
}

// Private ---------------------------------------------------------------------

// -----------------------------------------------------------------------------
void LULE::Debug::Logger::CreateTargetFile() {
	wcscpy_s(m_szTargetFile, LULE::Application::AppProperties::Get().GetKnownPath(LULE::Application::KnownPaths::UserAppData).c_str());
	wcscat_s(m_szTargetFile, L"Current.log");
}

// -----------------------------------------------------------------------------
void LULE::Debug::Logger::WriteLoop() {
	using namespace std;
	using namespace std::chrono;
	using outStream = std::wofstream;
	using delayPeriod = std::chrono::milliseconds;

	if (m_szTargetFile[0] == 0) {
		this->CreateTargetFile();
	}

	while (m_bWrite.load()) {
		this_thread::sleep_for(delayPeriod(LULE::Debug::LogDelay));

		// try_lock let's us still exit from the thread if the lock fails.
		if (m_MessageQ.empty() ||
			!m_WriteLock.try_lock())
			continue;

		// Try to open the target file
		outStream oS = outStream(m_szTargetFile, ios_base::app);
		if (oS.is_open()) {
			// Process the log
			auto nextData = m_MessageQ.front();

			wstring tag = CreateTag(get<0>(nextData), get<1>(nextData));

			oS << tag << get<2>(nextData) << L'\n';
			
			// Delete the format buffer
			delete get<2>(nextData);
			m_MessageQ.pop();
			oS.close();
		}
		else {
			// Gate for set amount of time
			static auto tpMs = time_point_cast<milliseconds>(system_clock::now());
			auto nowMs = time_point_cast<milliseconds>(system_clock::now());
			if ((nowMs.time_since_epoch() - tpMs.time_since_epoch()) >= milliseconds(1000)) {
				L_CONSOLE_OUT(L"Can't log in to target file. Program is unable to open the file.");

				// Update the gate
				tpMs = time_point_cast<milliseconds>(system_clock::now());
			}
		}
		
		m_WriteLock.unlock();
	}
}

// -----------------------------------------------------------------------------
std::wstring LULE::Debug::Logger::CreateTag(
	const Severity& s, 
	const std::chrono::system_clock::time_point& tp) {

	std::wstringstream result;

	// Put the date
	result << L'[' 
		<< tp 
		<< L']';
	
	// Put the severity tag
	result << L'[';
	switch(s) {
	case Severity::Info:
		result << L"INFO";
		break;
		
	case Severity::Warning:
		result << L"WARNING";
		break;
		
	case Severity::Error:
		result << L"ERROR";
		break;
	
	case Severity::Exception:
		result << L"EXCEPTION";
		break;
	
	default:
		result << L"UNKNOWN SEVERITY";
	}
	result << L"] ";

	return result.str();
}

// -----------------------------------------------------------------------------
void LULE::Debug::Logger::StartWriteThread() {
	if (m_tWriteThread ||
		m_bWrite.load()) {
		// TO DO: Throw an exception
	}

	m_bWrite.store(true);
	m_tWriteThread = new std::thread(&LULE::Debug::Logger::WriteLoop, this);
}

// -----------------------------------------------------------------------------
void LULE::Debug::Logger::StopWriteThread() {
	if (!m_tWriteThread)
		return;

	// Terminate the write thread
	if (m_tWriteThread->joinable()) {
		m_bWrite.store(false);

		// Wait for the write to end
		m_tWriteThread->join();

		delete m_tWriteThread;
		m_tWriteThread = nullptr;
	}
}
