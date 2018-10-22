/** This is a ppm loader / saver that includes the possibility of setting the precission and normalizes the image saving (and loading) the maximum as a comment **/

public: 
CImg<T>& load_ppm(const char *const filename) {
      if (!filename)    throw CImgArgumentException(_cimg_instance
                                    "load_ppm(): Specified filename is (null).",
                                    cimg_instance);
      std::ifstream f(filename);

      if (!f.is_open()) throw CImgIOException(_cimg_instance
                              "load_ppm() : Could not open PPM file '%s'.",
                              cimg_instance,
                              filename?filename:"(std::ifstream)");

      char p, type;
      f>>p>>type;
      if (((p!='p') && (p!='P')) || (type!='3'))
	        throw CImgIOException(_cimg_instance
                              "load_ppm(): PPM header not found in file '%s'.",
                              cimg_instance,
                              filename?filename:"(std::ifstream)");

      unsigned int width(0), height(0);
      T colorresolution(0), maxt(0);
      
      std::cerr<<"LOADING PPM"<<std::endl;
      while (colorresolution == 0) {
      	      std::string line;
	      std::getline(f,line);
	      if (line[0]=='#') {
                  if (line.substr(1,4)=="MAX=") {
			std::stringstream sstr(line.substr(5), std::ios_base::in);
			sstr>>maxt;
		  }
	      } else {
	          std::stringstream sstr(line, std::ios_base::in);
		  if ((width==0) && sstr) sstr>>width;
		  if ((height==0) && sstr) sstr>>height;
		  if ((colorresolution==0) && sstr) sstr>>colorresolution;
	      }
      }

      if (maxt == 0) maxt = 255;

      this->assign(width,height,1,3); T t;
      cimg_forXYC((*this),x,y,c) {
	      f>>t;
      	      (*this)(x,y,0,c) = (t*maxt)/colorresolution;
      }

      return (*this);
}

public:
const CImg<T>& save_ppm(const char* filename, unsigned long colorresolution = 255) const
{
	if (!filename)
		throw CImgArgumentException(_cimg_instance
	                                    "save_ppm() : Specified filename is (null).",
	                                    cimg_instance);
	
        std::ofstream f(filename);

	if (!f.is_open())
   		throw CImgIOException(_cimg_instance
                              "save_ppm() : Could not open PPM file '%s'.",
                              cimg_instance,
                              filename?filename:"(FILE*)");


	f << "P3" << std::endl;
	T maxt = max();
	f << "#MAX="<<(unsigned long)(maxt) <<std::endl;
	f << "# "<<filename<<std::endl;
	f << width()<<" "<<height()<<std::endl;
	f << (unsigned long)(colorresolution) << std::endl;

      cimg_forY((*this),y) {
	      cimg_forX((*this),x) {
	            cimg_forC((*this),c) {
		          f << std::setw(4)<<(unsigned long)(((*this)(x,y,0,c)*double(colorresolution))/double(maxt))<<" ";
		    } 
		    f<<"    ";
	      }
	      f<<std::endl;
      }

      return (*this);
}


static CImg<T> get_load_ppm(const char* filename) {
      return CImg<T>().load_ppm(filename);
}


