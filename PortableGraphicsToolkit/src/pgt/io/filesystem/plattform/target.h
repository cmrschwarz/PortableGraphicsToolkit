#pragma once
#include <pgt/target_settings/target_settings.h>
#if PGT_OS_WINDOWS
#include <pgt/io/filesystem/plattform/windows/FileSystemWindows.h>
#include <pgt/io/filesystem/plattform/windows/WindowsFileStreamReader.h>
#include <pgt/io/filesystem/plattform/windows/WindowsFileStreamWriter.h>
namespace pgt {
    namespace plattform {
        typedef plattform::FileSystemWindows OSFileSystem;
    }
    typedef plattform::WindowsFileStreamReader FileStreamReader;
    typedef plattform::WindowsFileStreamWriter FileStreamWriter;
}
#else
#error unsupported_os
#endif