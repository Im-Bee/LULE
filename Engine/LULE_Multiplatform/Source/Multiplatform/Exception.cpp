#include "LULE_Multiplatform.h"

#include <fstream>
#include <sstream>

// Public ----------------------------------------------------------------------

// -----------------------------------------------------------------------------
LULE::Exception::Exception(ExceptionData&& data) noexcept
	: m_Data(std::move(data)) {

	if (m_Data.Message[0] == 0)
		strcpy_s(m_Data.Message, "No message!");

	PopUp(Raport());
}

// Private ---------------------------------------------------------------------

// -----------------------------------------------------------------------------
LUINT8 LULE::Exception::Raport() {
	using fstream = std::wofstream;
	using namespace LULE::Application;

	LUINT8 failedWrite = 0;
	wcscpy_s(
		m_szRaportLocation, 
		AppProperties::Get().GetKnownPath(KnownPaths::UserAppData).c_str());
	fstream fOut = fstream(m_szRaportLocation);
	if (!fOut.is_open()) {
		failedWrite = 1;
		// At least try to log it directly 
		wcscpy_s(m_szRaportLocation, L"Error.log");
		fOut = fstream(m_szRaportLocation);
		if (!fOut.is_open()) {
			// Okay...
			failedWrite = 2;
			return failedWrite;
		}
	}

	// Write error to file


	return failedWrite;
}

// -----------------------------------------------------------------------------
void LULE::Exception::PopUp(const LUINT8& didRaportFailed) {
	using sstr = std::wstringstream;
	
	sstr errorMsg;
	if (didRaportFailed == 2) {
		errorMsg.str(L"Couldn't raport the exception to out file.");
	}
	else if (didRaportFailed == 1) {
		errorMsg.str(L"Raport falled back to \"Error.log\" located in exectuable's directory.");
	}
	else {
		errorMsg.str(L"Raport was logged to ");
		errorMsg << m_szRaportLocation;
	}
	errorMsg << L'\r';

	errorMsg << L"An exception occured in file: '" << m_Data.File << "'\r";
	errorMsg << L"At line: " << m_Data.Line << "\r";
	errorMsg << L"What: \r" << this->What();
	errorMsg << L"Message:\r" << m_Data.Message;

#ifdef _WIN32
	MessageBox(
		0,
		errorMsg.str().c_str(),
		NULL,
		MB_OK);
#endif // _WIN32
}
