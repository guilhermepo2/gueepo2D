#include <gueepo2d.h>

class DummyApp : public gueepo::Application {
public:
	DummyApp(const std::string& _Title, unsigned int _Width, unsigned int _Height) : Application(_Title, _Width, _Height) {}
	~DummyApp() { LOG_INFO("deleting dummy app"); }
};

gueepo::Application* gueepo::CreateApplication() {
	return new DummyApp("dummy app!", 640, 360);
}