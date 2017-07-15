Steps for Installing a new Version of FreeImage:
1. Donwload and replace old one in the Folder of This directory
2. Go to /FreeImage/Source/FreeImageLib
3. Create a minimal Cmake File from the VisualStudio project located there
4. Go through the FreeImage source and check for instances of 
		#define snprintf
   and make sure all of them are wrapped in a conditional like:
		#if defined(WIN32) && _MSC_VER < 1900 
5. done