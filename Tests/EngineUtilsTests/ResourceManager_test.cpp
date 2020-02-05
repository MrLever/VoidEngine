//STD Headers
#include <fstream>

//Library Headers
#include "gtest/gtest.h"

//Void Engine Headers
#include "utils/threading/ThreadPool.h"
#include "utils/resource/ResourceAllocator.h"
#include "core/Game.h"

using namespace utils;

namespace utils_tests {

	struct RawFile : public Resource {
		const std::string ErrorString = "Error";
		std::string FileContents;

		RawFile(std::string path) : Resource(path) {

		}

		bool Load() override {
			std::ifstream ifs;
			ifs.open(ResourcePath);

			if (!ifs.is_open()) {
				return false;
			}

			std::getline(ifs, FileContents);
			return true;
		}

		bool LoadErrorResource() override {
			FileContents = ErrorString;
			return true;
		}

		virtual void Initialize() {

		}

	};

	TEST(ResourceManagerTests, LoadResourceTest) {
		std::string SuccessString = "Wowza engine programming is fuckin' hard dude";
		core::Game g("");
		ResourceAllocator<RawFile> resourceMan;

		auto rawHandle = resourceMan.LoadResource("Resources/Testing/ResourceManagerDummyResource.txt");
		auto rawFile = rawHandle.GetResource();

		ASSERT_EQ(SuccessString, rawFile->FileContents);
	}

	TEST(ResourceManagerTests, GetResourceTest) {
		std::string SuccessString = "Wowza engine programming is fuckin' hard dude";

		core::Game g("");
		ResourceAllocator<RawFile> resourceMan;

		auto res = resourceMan.LoadResource("Resources/Testing/ResourceManagerDummyResource.txt");

		auto file = resourceMan.GetResource("Resources/Testing/ResourceManagerDummyResource.txt");
		ASSERT_EQ(SuccessString, file->FileContents);
	}

	TEST(ResourceManagerTests, ReloadResourceTest) {
		std::string SuccessString = "Wowza engine programming is fuckin' hard dude";

		core::Game g("");
		ResourceAllocator<RawFile> resourceMan;

		//Request resource to be loaded.
		auto res1 = resourceMan.LoadResource("Resources/Testing/ResourceManagerDummyResource.txt");

		//Explicitly request resource be loaded again
		res1 = resourceMan.ReloadResource("Resources/Testing/ResourceManagerDummyResource.txt");

		//Aquire the resource
		auto rawFile = resourceMan.GetResource("Resources/Testing/ResourceManagerDummyResource.txt");

		ASSERT_EQ(SuccessString, rawFile->FileContents);
	}

	TEST(ResourceManagerTests, RequestInvalidResourceTest) {
		std::string SuccessString = "Error";
		core::Game g("");
		ResourceAllocator<RawFile> resourceMan;

		auto res = resourceMan.LoadResource("FooBar");
		auto invalidResouce = resourceMan.GetResource("FooBar");
		ASSERT_EQ(SuccessString, invalidResouce->FileContents);
	}

}