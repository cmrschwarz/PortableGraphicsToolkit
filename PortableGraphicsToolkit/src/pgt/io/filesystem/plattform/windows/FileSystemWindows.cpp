#include "FileSystemWindows.h"
#include <windows.h>
#include <shlobj.h>
#include <pgt/io/logger/logger.h>
#include <pgt/io/filesystem/filesystem.h>
#include <pgt/utils/string/string_utils.h>
#include <pgt/utils/string/path_utils.h>
namespace pgt {
    namespace plattform {
        int strlenw(const WCHAR* c)
        {
            const WCHAR* cc = c;
            while (*cc != 0 || *(cc + 1) != 0) {
                cc++;
            }
            return (cc - c);
        }
        std::string FileSystemWindows::getFilepathOfExecutable()
        {
            const size_t BUFFER_MUL = 256;
            std::string path;
            size_t len = 0u;
            do {
                path.resize(len + BUFFER_MUL);
                len = GetModuleFileNameW(NULL, (WCHAR*)&path[0], path.size());
            } while (len >= path.size());
            // getting rid of the trailing zeros
            path.pop_back();
            path.pop_back();
            path = convertUTF16toUTF8(path);
            return path;
        }

        std::vector<std::string> FileSystemWindows::getAllFilesWithinFolder(
            const std::string& folder)
        {
            std::string search_path = folder + "/*.*";
            search_path = convertUTF8toUTF16With00(search_path);
            std::vector<std::string> names;

            WIN32_FIND_DATAW fd;
            HANDLE hFind = FindFirstFileW((WCHAR*)&search_path[0], &fd);
            if (hFind != INVALID_HANDLE_VALUE) {
                do {
                    if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                        names.push_back(convertUTF16toUTF8(fd.cFileName));
                    }
                } while (::FindNextFileW(hFind, &fd));
                FindClose(hFind);
            }
            return names;
        }

        std::vector<std::string> FileSystemWindows::getAllFoldersWithinFolder(
            const std::string& folder)
        {
            std::vector<std::string> names;
            std::string search_path = folder + "/*.*";
            search_path = convertUTF8toUTF16With00(search_path);
            WIN32_FIND_DATAW fd;
            HANDLE hFind = ::FindFirstFileW((WCHAR*)&search_path[0], &fd);
            if (hFind != INVALID_HANDLE_VALUE) {
                do {
                    std::string subfolder = convertUTF16toUTF8(fd.cFileName);
                    if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                        continue;
                    if (subfolder[0] == '.') {
                        if (subfolder.size() == 1) continue;
                        if (subfolder[1] == '.') {
                            if (subfolder.size() == 2) continue;
                        }
                    }
                    names.push_back(std::move(subfolder));
                } while (::FindNextFileW(hFind, &fd));
                FindClose(hFind);
            }
            return names;
        }

        std::string FileSystemWindows::getDesktopPath()
        {
            WCHAR path[MAX_PATH];
            auto r = SHGetSpecialFolderPathW(HWND_DESKTOP, &path[0],
                                             CSIDL_DESKTOP, FALSE);
            PGT_ASSERT(SUCCEEDED(r), "Failed to get Desktop Path");
            std::string res = convertUTF16toUTF8(path);
            sanitizePathName(res);
            return res;
        }
        void FileSystemWindows::createDirectory(const std::string& path)
        {
            CreateDirectoryW((WCHAR*)&convertUTF8toUTF16With00(path)[0],
                             nullptr);
        }

        void FileSystemWindows::renameFile(const std::string& path,
                                           const std::string& name_new)
        {
            const char* path_end = pgt::getFileNameFromPath(path.c_str());
            std::string path_new(path.c_str(), path_end);
            path_new.append(name_new);
            std::string path_w = pgt::convertUTF8toUTF16With00(path);
            path_new = pgt::convertUTF8toUTF16With00(path_new);
            bool res =
                MoveFileW((WCHAR*)path_w.c_str(), (WCHAR*)path_new.c_str());
            int i = 0;
        }
    }
}