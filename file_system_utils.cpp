/* Following lists describes the main api's modern c++ provides for the file system utilities
1. Current Directory Information
Shows the current working directory path
2. Path Analysis
Checks if paths exist
Determines file types (regular file, directory, symlink)
Displays file sizes, permissions, and last modification times
3. Directory Listing
Lists all files and directories in a directory
Shows detailed information including permissions and file sizes
Formatted table output
4. Path Operations
Demonstrates absolute vs relative paths
Shows path decomposition (filename, extension, stem, parent path)
Path concatenation and component iteration
5. File Operations
Creates directories and files
Copies files
Moves/renames files
Cleans up created files and directories
6. Disk Space Information
Shows total capacity, free space, and available space
7. Recursive Directory Traversal
Lists directory contents recursively with depth control

Key Features:
  Uses C++17 <filesystem> library
  Comprehensive error handling with try-catch blocks
  Unix-style permission display
  Proper resource cleanup
*/
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace filesystem;

class FileSystemUtilities {
public:
    // Display current working directory
    static void showCurrentDirectory() {
        cout << "\n=== Current Working Directory ===" << endl;
        try {
            cout << "Current path: " << current_path() << endl;
        } catch (const filesystem_error& e) {
            cout << "Error getting current path: " << e.what() << endl;
        }
    }

    // Check if path exists and what type it is
    static void checkPath(const path& p) {
        cout << "\n=== Path Information: " << p << " ===" << endl;
        cout << "Exists: " << (exists(p) ? "Yes" : "No") << endl;

        if (exists(p)) {
            cout << "Is regular file: " << (is_regular_file(p) ? "Yes" : "No") << endl;
            cout << "Is directory: " << (is_directory(p) ? "Yes" : "No") << endl;
            cout << "Is symlink: " << (is_symlink(p) ? "Yes" : "No") << endl;

            if (is_regular_file(p)) {
                cout << "File size: " << file_size(p) << " bytes" << endl;
            }

            // Get permissions
            auto perms = status(p).permissions();
            cout << "Permissions: ";
            cout << ((perms & perms::owner_read) != perms::none ? "r" : "-");
            cout << ((perms & perms::owner_write) != perms::none ? "w" : "-");
            cout << ((perms & perms::owner_exec) != perms::none ? "x" : "-");
            cout << ((perms & perms::group_read) != perms::none ? "r" : "-");
            cout << ((perms & perms::group_write) != perms::none ? "w" : "-");
            cout << ((perms & perms::group_exec) != perms::none ? "x" : "-");
            cout << ((perms & perms::owner_read) != perms::none ? "r" : "-");
            cout << ((perms & perms::owner_write) != perms::none ? "w" : "-");
            cout << ((perms & perms::owner_exec) != perms::none ? "x" : "-");
            cout << endl;

            // Get last write time
            auto ftime = last_write_time(p);
            auto sctp = chrono::time_point_cast<chrono::system_clock::duration>(
                ftime - file_time_type::clock::now() + chrono::system_clock::now());
            time_t cftime = chrono::system_clock::to_time_t(sctp);
            cout << "Last modified: " << asctime(localtime(&cftime));
        }
    }

    // List directory contents
    static void listDirectory(const path& dir_path) {
        cout << "\n=== Directory Contents: " << dir_path << " ===" << endl;

        if (!exists(dir_path) || !is_directory(dir_path)) {
            cout << "Path is not a valid directory" << endl;
            return;
        }

        cout << left << setw(30) << "Name" << setw(10) << "Type" << setw(15) << "Size" << "Permissions" << endl;
        cout << string(70, '-') << endl;

        try {
            for (const auto& entry : directory_iterator(dir_path)) {
                string type = "Unknown";
                string size_str = "-";
                string perms = "---------";

                if (entry.is_regular_file()) {
                    type = "File";
                    size_str = to_string(entry.file_size());
                } else if (entry.is_directory()) {
                    type = "Directory";
                } else if (entry.is_symlink()) {
                    type = "Symlink";
                }

                // Get permissions
                auto p = entry.status().permissions();
                perms[0] = (p & perms::owner_read) != perms::none ? 'r' : '-';
                perms[1] = (p & perms::owner_write) != perms::none ? 'w' : '-';
                perms[2] = (p & perms::owner_exec) != perms::none ? 'x' : '-';
                perms[3] = (p & perms::group_read) != perms::none ? 'r' : '-';
                perms[4] = (p & perms::group_write) != perms::none ? 'w' : '-';
                perms[5] = (p & perms::group_exec) != perms::none ? 'x' : '-';
                perms[6] = (p & perms::others_read) != perms::none ? 'r' : '-';
                perms[7] = (p & perms::others_write) != perms::none ? 'w' : '-';
                perms[8] = (p & perms::others_exec) != perms::none ? 'x' : '-';

                cout << left << setw(30) << entry.path().filename().string()
                     << setw(10) << type
                     << setw(15) << size_str
                     << perms << endl;
            }
        } catch (const filesystem_error& e) {
            cout << "Error listing directory: " << e.what() << endl;
        }
    }

    // Path operations demonstration
    static void demonstratePathOperations() {
        cout << "\n=== Path Operations Demo ===" << endl;

        path p1 = "/home/user/documents/file.txt";
        path p2 = "relative/path/file.cpp";

        cout << "Absolute path: " << p1 << endl;
        cout << "Relative path: " << p2 << endl;
        cout << "p1 is absolute: " << (p1.is_absolute() ? "Yes" : "No") << endl;
        cout << "p2 is absolute: " << (p2.is_absolute() ? "Yes" : "No") << endl;

        cout << "p1 filename: " << p1.filename() << endl;
        cout << "p1 extension: " << p1.extension() << endl;
        cout << "p1 stem: " << p1.stem() << endl;
        cout << "p1 parent path: " << p1.parent_path() << endl;

        // Path concatenation
        path combined = p1 / "subdir" / "newfile.txt";
        cout << "Combined path: " << combined << endl;

        // Path decomposition
        cout << "Path components:" << endl;
        for (const auto& part : combined) {
            cout << "  " << part << endl;
        }
    }

    // File operations demonstration
    static void demonstrateFileOperations() {
        cout << "\n=== File Operations Demo ===" << endl;

        path test_dir = "test_directory";
        path test_file = "test_file.txt";
        path copy_file = "copied_file.txt";

        try {
            // Create directory
            if (!exists(test_dir)) {
                create_directory(test_dir);
                cout << "Created directory: " << test_dir << endl;
            }

            // Create a test file
            if (!exists(test_file)) {
                ofstream file(test_file);
                file << "This is a test file for file system utilities demo." << endl;
                file.close();
                cout << "Created file: " << test_file << endl;
            }

            // Copy file
            copy(test_file, copy_file);
            cout << "Copied " << test_file << " to " << copy_file << endl;

            // Show file sizes
            cout << test_file << " size: " << file_size(test_file) << " bytes" << endl;
            cout << copy_file << " size: " << file_size(copy_file) << " bytes" << endl;

            // Move file to directory
            path moved_file = test_dir / test_file.filename();
            rename(copy_file, moved_file);
            cout << "Moved " << copy_file << " to " << moved_file << endl;

            // List the test directory
            listDirectory(test_dir);

            // Clean up
            cout << "\nCleaning up..." << endl;
            remove(moved_file);
            remove(test_file);
            remove(test_dir);
            cout << "Cleanup completed." << endl;

        } catch (const filesystem_error& e) {
            cout << "File operation error: " << e.what() << endl;
        }
    }

    // Space information
    static void showSpaceInfo(const path& p = current_path()) {
        cout << "\n=== Space Information ===" << endl;
        try {
            auto space_info = space(p);
            cout << "Path: " << p << endl;
            cout << "Capacity: " << space_info.capacity / (1024*1024) << " MB" << endl;
            cout << "Free: " << space_info.free / (1024*1024) << " MB" << endl;
            cout << "Available: " << space_info.available / (1024*1024) << " MB" << endl;
        } catch (const filesystem_error& e) {
            cout << "Error getting space info: " << e.what() << endl;
        }
    }

    // Recursive directory iteration
    static void recursiveList(const path& dir_path, int max_depth = 2) {
        cout << "\n=== Recursive Directory Listing: " << dir_path << " ===" << endl;

        if (!exists(dir_path) || !is_directory(dir_path)) {
            cout << "Path is not a valid directory" << endl;
            return;
        }

        try {
            int current_depth = 0;
            for (const auto& entry : recursive_directory_iterator(dir_path)) {
                // Calculate depth by counting path separators
                string path_str = entry.path().string();
                size_t depth = count(path_str.begin(), path_str.end(), '/');
                size_t base_depth = count(dir_path.string().begin(), dir_path.string().end(), '/');

                if (depth - base_depth > max_depth) continue;

                string indent((depth - base_depth) * 2, ' ');
                string type = entry.is_directory() ? "[DIR]" : "[FILE]";
                cout << indent << type << " " << entry.path().filename() << endl;
            }
        } catch (const filesystem_error& e) {
            cout << "Error in recursive listing: " << e.what() << endl;
        }
    }

    // Demonstrate all utilities
    static void runAllDemos() {
        showCurrentDirectory();
        checkPath(".");
        checkPath("main.cpp");
        listDirectory(".");
        demonstratePathOperations();
        demonstrateFileOperations();
        showSpaceInfo();
        recursiveList(".", 1);
    }
};
