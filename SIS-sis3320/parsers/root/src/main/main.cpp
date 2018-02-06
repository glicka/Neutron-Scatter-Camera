#include "../ReadSIS3302.hpp"

/* Example of using the parser */
int main(int argc, char *argv[]) {
	ReadSIS3302 *s;
	// Handle the input
	switch (argc) {
		case 3:
			s = new ReadSIS3302(argv[1], argv[2]);
			break;
		default:
			cout << "Syntax:" << "\n  ";
			cout << argv[0] << " [infile].dat [outfile].root" << endl;
			return 1;
	}
	try {
		s->Parse();
	} catch(exception const& e) {
			cerr << e.what() << endl;
			return 1;
	}
	delete s;
	return 0;
}
