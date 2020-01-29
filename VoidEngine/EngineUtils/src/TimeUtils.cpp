//STD Headers
#include <chrono>


//Library Headers


//Engine Core Headers
#include "utils/TimeUtils.h"

namespace utils {
	GameTime GetGameTime() {
		auto timeSinceEpoch = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()
		);

		return timeSinceEpoch.count();
	}

	std::string GetLocalTime(){
		//TODO(MrLever): Use new c++20 Calendar stuff when it comes out
		return "ERROR";
	}
}