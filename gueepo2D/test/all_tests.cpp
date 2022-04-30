#include "gueepo2D.h"
#include <catch2/catch_all.hpp>
#include "vector2.h"
#include "vector3.h"
#include "json.h"

class Dummy : public gueepo::Application {
public:

	Dummy() : Application("sandbox", 960, 540) {}
	~Dummy() {}
};

gueepo::Application* gueepo::CreateApplication() {
	
	LOG_INFO("RUNNING TESTS!");
	int result = Catch::Session().run();
	LOG_INFO("FINISHED RUNNING TESTS");

	// argh, this is awful, I wish I could just run the tests
	// I will pat myself in the back and tell myself that this can also work as a sanity test to see if we can create a window
	return new Dummy();
}