// ==========================
//    PROJECT INFO
// Title:	consolate_driver
// Source:	main.cpp
// Version:	2.0
// Date:	13/04/2018
// Author:	Elijah Shadbolt
// ==========================

#include <consolate.h>

int main()
{
	using namespace consolate;
	using std::endl;
	using std::cout;

	cout << R"(
Hi! I am Consolate.

I was created with the express purpose of making
the Windows Console less intimidating for you!

You can use me (senpai) to:
- Change text colour
- Clear the screen
- Draw rectangles and simple shapes

You can find me in the `consolate` namespace.
I am the main instance of the Consolater class,
which means I use the default stdin/stdout handles.

Try me out!)" << endl;

	Consolate.SetColor(Color_Yellow);

	cout << R"(
	#include <consolate.h>
	...
	consolate::Consolate.SetColor(consolate::Color_Green);
	std::cout << "Hello world!" << std::endl;
)";
	cout << endl;

	Consolate.Reset();

	// Example
	consolate::Consolate.SetColor(consolate::Color_Green);
	std::cout << "Hello world!" << std::endl;
	// END Example

	Consolate.Reset();

	cout << R"(
See how easy that was?

I hope you enjoy working with me as much as I enjoy
making life easier for you!
)";
	cout << endl << endl;

	return 0;
}
