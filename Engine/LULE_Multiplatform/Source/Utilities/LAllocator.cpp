#include "LULE_Multiplatform.h"

// LAllocator ------------------------------------------------------------------
// -----------------------------------------------------------------------------
LULE::LAllocator::LAllocator(const LUINT64& uInitialByteSize)
	: m_uByteCapacity(uInitialByteSize) {
#if _WIN32 || _WIN64
	_RawBuffer = HeapAlloc(GetProcessHeap(), NULL, uInitialByteSize);
#else
#   error "_LUL_::LAllocator::LAllocator(const LUINT64& uInitialByteSize) not implemented on current system."
#endif
	if (_RawBuffer == nullptr)
		throw;

	m_uBegBuffPosition = reinterpret_cast<MEM_LOCATION>(_RawBuffer);
	m_uEndBuffPosition = m_uBegBuffPosition + m_uByteCapacity;
}

// -----------------------------------------------------------------------------
LULE::LAllocator::LAllocator(LAllocator&& other) {
	this->m_uByteCapacity = other.m_uByteCapacity;

#if _WIN32 || _WIN64
	this->_RawBuffer = HeapAlloc(GetProcessHeap(), NULL, this->m_uByteCapacity);
#else
#   error "_LUL_::LAllocator::LAllocator(LAllocator&& other) not implemented on current system."
#endif

	errno_t e = memcpy_s(
		this->_RawBuffer,
		this->m_uByteCapacity,
		other._RawBuffer,
		other.m_uByteCapacity);
	if (e) {
		throw;
	}

	m_uBegBuffPosition = reinterpret_cast<MEM_LOCATION>(_RawBuffer);
	m_uEndBuffPosition = m_uBegBuffPosition + m_uByteCapacity;
}

// -----------------------------------------------------------------------------
LULE::LAllocator::~LAllocator() {
	if (!HeapFree(GetProcessHeap(), NULL, _RawBuffer)) {
		throw;
	}
}

// Protected -------------------------------------------------------------------

//  ----------------------------------------------------------------------------
void LULE::LAllocator::_Resize(const LUINT64& uByteResize) {
	m_uByteCapacity += uByteResize;

#if _WIN32 || _WIN64
	void* reallocPtr = HeapReAlloc(GetProcessHeap(), NULL, _RawBuffer, m_uByteCapacity);
#else
#   error "void _LUL_::LAllocator::_Resize(const LUINT64& uByteResize) not implemented on current system."
#endif

	if (reallocPtr == nullptr) {
		// TO DO: Fiugre out what to do after HeapReAlloc fails.
		throw;
	}

	_RawBuffer = reallocPtr;
	m_uBegBuffPosition = reinterpret_cast<MEM_LOCATION>(_RawBuffer);
	m_uEndBuffPosition = m_uBegBuffPosition + m_uByteCapacity;
}

// -----------------------------------------------------------------------------
LBOOL LULE::LAllocator::_RecalcResize(LUINT64& uCurrentCapacity, LUINT32& uResize) {
	switch (m_uByteCapacity) {


	default:
		return false;
	}
}
