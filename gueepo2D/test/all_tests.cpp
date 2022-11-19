#define GUEEPO2D_MAIN
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

// This is kind of dumb, but hey, it works?
// In case it is needed that this works as some sort of sanity check as well, just return a new Dummy() instead of a nullptr
gueepo::Application* gueepo::CreateApplication() {
	int result = Catch::Session().run();
	return nullptr;
}