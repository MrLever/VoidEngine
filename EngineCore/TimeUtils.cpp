//STD Headers
#include <chrono>


//Library Headers


//Engine Core Headers
#include "TimeUtils.h"

namespace EngineUtils {
	GameTime GetGameTime() {
		auto timeSinceEpoch = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()
			);

		return timeSinceEpoch.count();
	}
}