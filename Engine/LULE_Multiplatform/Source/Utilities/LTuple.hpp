#ifndef LULE_TUPLE_H
#define LULE_TUPLE_H

#include "LAllocator.hpp"

namespace LULE {
	template<class... UTypes>
	struct LTuple : public LULE::LAllocatorU {
		LTuple(UTypes... inputs) {
			for (const auto p : { inputs... })
				this->AddSlot(sizeof(p));
		}
	};
}

#endif // !LULE_TUPLE_H
