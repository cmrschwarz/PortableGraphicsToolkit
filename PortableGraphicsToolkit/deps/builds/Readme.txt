Steps for Installing a new Version of FreeImage:
	1. Backup the CMakeLists.txt in FreeImage/Source
	2. Replace the FreeImage Folder with the new version of the library
	3. Place back the CMakeLists.txt
	4. Update the SourceFiles [painful, ikr]
	5. Check all Libraries for new added Preprocessor statements 
	6. Surround all references of #define snprintf with #if _MSC_VER < 1900   ...    #endif
	7. launch build
	8. pray it works	
Steps for Installing a new Version of GLEW
	1. Replace the FreeImage Folder with the new version of the library
	2. Comment out the line (around 103): "target_link_libraries (glew LINK_PRIVATE -nodefaultlib -noentry)"