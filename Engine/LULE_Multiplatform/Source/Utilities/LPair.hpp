#ifndef LULE_PAIR_H
#define LULE_PAIR_H

namespace LULE {
	template<class T1, class T2>
	struct LULE_API LPair {
		T1 First;
		T2 Second;

		LPair() = default;
		explicit LPair(T1 value1) : First(value1) {};
		explicit LPair(T2 value2) : Second(value2) {};
		LPair(T1 value1, T2 value2) : First(value1), Second(value2) {};

		~LPair() = default;

		LPair(LPair&) noexcept = default;
		LPair(LPair&&) noexcept = default;
	};
}

#endif // !LULE_PAIR_H
