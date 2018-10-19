#include <cimg-all.h>
#include <string>

using namespace cimg_library;

int main(int argc, const char** argv) {
	const char* input = "input.hdr";
	const char* output = "output.ppm";
	unsigned long colorresolution = 255;
	for (int i = 0; i<argc-1; ++i) {
		if      (strcmp("-input",argv[i])==0) input = argv[++i];
		else if (strcmp("-output",argv[i])==0) output = argv[++i];
		else if (strcmp("-color-resolution",argv[i])==0) colorresolution = atol(argv[++i]);
	}

	CImg<double> image;
	image.load(input);
	image.save_ppm(output,colorresolution);
}
