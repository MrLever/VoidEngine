#pragma once
//STD Headers
#include <span>

//Library Headers

//Void Engine Headers

namespace utils {
	/**
	 * @class MultiSpan
	 * @brief A dynamic-allocation free datastructure for iterating over a collection
	 *        of spans as if they were contiguous in memory
	 */
	template<class T, size_t Count>
	class MultiSpan {
	public:
		/**
		 * Constructor
		 * @param spans The spans this multispan provides a view to
		 */
		MultiSpan(std::array<std::span<T>, Count>& spans);

	private:
		/** The span data */
		std::array<std::span<T>, Count> m_Spans;
	};
	
	template<class T, size_t Count>
	inline MultiSpan<T, Count>::MultiSpan(std::array<std::span<T>, Count>& spans) 
		: m_Spans(spans) {

	}
}