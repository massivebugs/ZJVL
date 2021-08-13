#include "all.h"
#include "core/app.h"

// Create the app instance and call run() to execute the game loop.
// Arguments and the return statement are required for compatibility with SDL
int main(int argc, char *argv[])
{
	ZJVL::Core::App *app = ZJVL::Core::App::instance();
	int code = app->run();
	delete app;
	return code;
}