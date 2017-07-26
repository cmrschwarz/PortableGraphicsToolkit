if (NOT EXISTS "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/cmake-build-debug/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/install_manifest.txt")
    message(FATAL_ERROR "Cannot find install manifest: \"C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/cmake-build-debug/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/install_manifest.txt\"")
endif(NOT EXISTS "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/cmake-build-debug/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/install_manifest.txt")

file(READ "C:/daten_local/tech/programming/CPlusPlus/PortableGraphicsToolkit/cmake-build-debug/PortableGraphicsToolkit/deps/builds/SDL-mirror-master/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach (file ${files})
    message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
    execute_process(
        COMMAND C:/Program Files/JetBrains/CLion 2017.1.3/bin/cmake/bin/cmake.exe -E remove "$ENV{DESTDIR}${file}"
        OUTPUT_VARIABLE rm_out
        RESULT_VARIABLE rm_retval
    )
    if(NOT ${rm_retval} EQUAL 0)
        message(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif (NOT ${rm_retval} EQUAL 0)
endforeach(file)

