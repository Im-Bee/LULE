#ifndef LULE_LALLOCATOR_H
#define LULE_LALLOCATOR_H

#include <type_traits>

namespace LULE {

	typedef LUINT64 MEM_LOCATION;

	class LULE_API LAllocator {
		LUINT64 m_uByteCapacity;
		MEM_LOCATION m_uBegBuffPosition;
		MEM_LOCATION m_uEndBuffPosition;

	public:
		LAllocator() = delete;
		LAllocator(const LUINT64& uInitialByteSize);

		LAllocator(const LAllocator&) noexcept = default;
		LAllocator(LAllocator&& other);

		~LAllocator();

	public:
		void* _RawBuffer;
		
		const LUINT64& GetByteCapacity() { return m_uByteCapacity; }

	protected:
		const MEM_LOCATION& _BeginML() { return m_uBegBuffPosition; }
		const MEM_LOCATION& _EndML() { return m_uEndBuffPosition; }

		void _Resize(const LUINT64& uByteResize);

		LBOOL _RecalcResize(LUINT64& uCurrentCapacity, LUINT32& uResize);
	};

	template<class T, LUINT32 InitialSize = 32>
	class LAllocatorT : public LAllocator {
		LUINT32 m_uResize = InitialSize;
		LUINT64 m_uCapacity = m_uResize;

		LUINT32 m_uSizeOfT = sizeof(T);
		LUINT32 m_uByteResize = m_uResize * m_uSizeOfT;

	public:
		LAllocatorT() : LAllocator(sizeof(T)* InitialSize) {};

		LAllocatorT(const LAllocatorT&) noexcept = default;
		LAllocatorT(LAllocatorT&& other) noexcept : LAllocator(other) {};

		~LAllocatorT() = default;

	public:
		T& operator[](const LUINT64& i) {
			if (i >= m_uCapacity) {
				throw;
			}

			return (reinterpret_cast<T*>(_RawBuffer)[i]);
		}

		const LUINT64& Capacity() {
			return m_uCapacity;
		}

		void Reserve(const LUINT64& uAmount) {
			if (uAmount <= m_uCapacity)
				return;

			_Resize((uAmount * m_uSizeOfT) - this->GetByteCapacity());
			m_uCapacity += (uAmount - m_uCapacity);
		}

	protected:
		void Resize() {
			_Resize(m_uByteResize);
			m_uCapacity += m_uResize;

			if (_RecalcResize(m_uCapacity, m_uResize))
				m_uByteResize = m_uResize * m_uSizeOfT;
		}
	};

	class LAllocatorU : public LAllocator {
		LAllocatorT<LUINT8, 0> m_ByteOffsets = {};

	public:
		LAllocatorU() : LAllocator(0) {};

	public:
		void* Get(const LUINT64& uIndex) {
			if (uIndex >= m_ByteOffsets.Capacity()) {
				throw;
			}

			MEM_LOCATION offset = this->_BeginML();
			for (LUINT64 i = 0; i < uIndex; ++i) {
				offset += m_ByteOffsets[i];
			}

			if (offset > this->_EndML() - m_ByteOffsets[uIndex]) {
				throw;
			}
			return reinterpret_cast<void*>(offset);
		}

	protected:
		void AddSlot(const LUINT8& uByteSize) {
			m_ByteOffsets.Reserve(m_ByteOffsets.Capacity() + 1);
			m_ByteOffsets[m_ByteOffsets.Capacity() - 1] = uByteSize;
			this->_Resize(uByteSize);
		}

	};
}

#endif // !LULE_LALLOCATOR_H