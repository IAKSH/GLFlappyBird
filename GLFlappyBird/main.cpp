#include "flappybird.hpp"

int main() noexcept
{
	std::cout << "hello\n";

	FlappyBird fb;
	fb.initialize();
	fb.mainLoop();

	return 0;
}