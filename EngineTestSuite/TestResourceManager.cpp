//STD Headers
#include <fstream>

//Library Headers
#include "CppUnitTest.h"

//Void Engine Headers
#include "ThreadPool.h"
#include "ResourceManager.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace utils;

namespace EngineUtilitiesTests {

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

	TEST_CLASS(ResourceManagerTests) {
	public:

		TEST_METHOD(LoadNewResourceTest) {
			std::string SuccessString = "Wowza engine programming is fuckin' hard dude";

			std::shared_ptr<ThreadPool> pool = std::make_shared<ThreadPool>();
			ResourceManager<RawFile> resourceMan(pool);

			auto rawHandle = resourceMan.LoadResource("Resources/Testing/ResourceManagerDummyResource.txt");
			auto rawFile = rawHandle.GetResource();

			Assert::AreEqual(SuccessString, rawFile->FileContents);
		}

		TEST_METHOD(GetResourceTest) {
			std::string SuccessString = "Wowza engine programming is fuckin' hard dude";

			std::shared_ptr<ThreadPool> pool = std::make_shared<ThreadPool>();
			ResourceManager<RawFile> resourceMan(pool);

			auto res = resourceMan.LoadResource("Resources/Testing/ResourceManagerDummyResource.txt");

			auto file = resourceMan.GetResource("Resources/Testing/ResourceManagerDummyResource.txt");
			Assert::AreEqual(SuccessString, file->FileContents);
		}

		TEST_METHOD(ReloadResourceTest) {
			std::string SuccessString = "Wowza engine programming is fuckin' hard dude";

			std::shared_ptr<ThreadPool> pool = std::make_shared<ThreadPool>();
			ResourceManager<RawFile> resourceMan(pool);

			//Request resource to be loaded.
			auto res1 = resourceMan.LoadResource("Resources/Testing/ResourceManagerDummyResource.txt");

			//Explicitly request resource be loaded again
			res1 = resourceMan.ReloadResource("Resources/Testing/ResourceManagerDummyResource.txt");

			//Aquire the resource
			auto rawFile = resourceMan.GetResource("Resources/Testing/ResourceManagerDummyResource.txt");

			Assert::AreEqual(SuccessString, rawFile->FileContents);
		}

		TEST_METHOD(RequestInvalidResourceTest) {
			std::string SuccessString = "Error";
			std::shared_ptr<ThreadPool> pool = std::make_shared<ThreadPool>();
			ResourceManager<RawFile> resourceMan(pool);

			auto res = resourceMan.LoadResource("FooBar");
			auto invalidResouce = resourceMan.GetResource("FooBar");
			Assert::AreEqual(SuccessString, invalidResouce->FileContents);
		}
	};

}