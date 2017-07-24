Steps for Installing a new Version of FreeImage:
	1. Backup the CMakeLists.txt in FreeImage/Source
	2. Replace the FreeImage Folder with the new version of the library
	3. Place back the CMakeLists.txt
	4. Update the SourceFiles [painful, ikr]
	5. Check all Libraries for new added Preprocessor statements 
	6. Surround all references of #define snprintf with #if _MSC_VER < 1900   ...    #endif
	7. rename file ./FreeImage/Source/LibJXR/common/include/guiddef.h to something uncommon so its not being used
	8. Change line ~667 in file ./FreeImage/Source/LibJXR/image/sys/strcodec.c from
		#if (defined(WIN32) && !defined(UNDER_CE) && (!defined(__MINGW32__) || defined(__MINGW64_TOOLCHAIN__))) || (defined(UNDER_CE) && defined(_ARM_))
	to
		#if (defined(WIN32) && !defined(UNDER_CE))  || (defined(UNDER_CE) && defined(_ARM_))

	7. launch build
	8. pray it works	
Steps for Installing a new Version of GLEW
	1. Replace the FreeImage Folder with the new version of the library
	2. Comment out the line (around 103): "target_link_libraries (glew LINK_PRIVATE -nodefaultlib -noentry)"
	3.Change the line (around 194):
		"if(WIN32 AND(NOT MSVC_VERSION LESS 1600) AND (NOT CMAKE_VERSION VERSION_LESS "3.1"))"
	  to 
	    "if(WIN32 AND MSVC AND (NOT MSVC_VERSION LESS 1600) AND (NOT CMAKE_VERSION VERSION_LESS "3.1"))"