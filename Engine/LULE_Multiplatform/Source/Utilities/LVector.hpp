#ifndef LULE_VECTOR_H
#define LULE_VECTOR_H

#include "LAllocator.hpp"

namespace LULE {
	template<class T>
	class LVector : public LAllocatorT<T, 4> {
		LUINT64 m_uAllocated = 0;

	public:
		void Push(const T& itm) {
			if (m_uAllocated > this->Capacity())
				this->Resize();

			static_cast<LUINT32*>(this->_RawBuffer)[m_uAllocated++] = itm;
		}

		void Push(T&& itm) {
			if (m_uAllocated > this->Capacity())
				this->Resize();

			static_cast<LUINT32*>(this->_RawBuffer)[m_uAllocated++] = itm;
		}

		const LUINT64& Size() {
			return m_uAllocated;
		}

		void Pop() {
			if (m_uAllocated == 0) {
				return;
			}
			if (m_uAllocated < 0) {
				m_uAllocated = 0;
				return;
			}

			--m_uAllocated;
		}

		T* begin() { return (T*)(this->_BeginML()); }
		T* end() { return (T*)(this->_BeginML() + (m_uAllocated * sizeof(T))); }
	};
}

#endif // !LULE_VECTOR_H