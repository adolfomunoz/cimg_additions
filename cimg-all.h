#pragma once

#ifndef cimg_display
#define cimg_display 0
#endif

#define cimg_plugin  <image/cimg-hdr.h>
#define cimg_plugin1 <image/cimg-tmo.h>

// The code below allows to add the support for the specified extension.
//---------------------------------------------------------------------
#ifndef cimg_load_plugin
#define cimg_load_plugin(filename) \
	  if (!cimg::strncasecmp(cimg::split_filename(filename),"hdr",3)) return load_hdr(filename);
#endif
#ifndef cimg_save_plugin
#define cimg_save_plugin(filename) \
	  if (!cimg::strncasecmp(cimg::split_filename(filename),"hdr",3)) return save_hdr(filename);
#endif


#include <CImg.h>
