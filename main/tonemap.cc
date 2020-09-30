#include <cimg-all.h>
#include <string>

using namespace cimg_library;

int main(int argc, const char** argv) {
	const char* input = "input.hdr";
	const char* output = "output.ppm";
    float lwhite = -1;
    float a = 0.18;
	for (int i = 0; i<argc-1; ++i) {
		if      (strcmp("-input",argv[i])==0) input = argv[++i];
		else if (strcmp("-output",argv[i])==0) output = argv[++i];
        else if (strcmp("-a",argv[i])==0) a = atof(argv[++i]);
        else if (strcmp("-lwhite",argv[i])==0) lwhite = atof(argv[++i]);
	}

	CImg<double> image;
	image.load(input);
	image.print(input);
    if (lwhite < 0) lwhite = image.max();
    image.tmo_reinhard02(lwhite, a);
    image.print(output);
	image.save(output);
}
