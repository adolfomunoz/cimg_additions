#pragma once

#ifndef cimg_display
#define cimg_display 0
#endif

#define cimg_plugin  <additions/cimg-hdr.h>
#define cimg_plugin1 <additions/cimg-ppm.h>
#define cimg_plugin2 <additions/cimg-tmo.h>

// The code below allows to add the support for the specified extension.
//---------------------------------------------------------------------
#define cimg_load_plugin(filename) \
	  if (!cimg::strcasecmp(ext,"hdr")) load_hdr(filename);
#define cimg_save_plugin(filename) \
	  if (!cimg::strcasecmp(ext,"hdr")) return save_hdr(filename);

#define cimg_load_plugin1(filename) \
	  if (!cimg::strcasecmp(ext,"ppm")) load_ppm(filename);
#define cimg_save_plugin1(filename) \
	  if (!cimg::strcasecmp(ext,"ppm")) return save_ppm(filename);


#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <CImg.h>
