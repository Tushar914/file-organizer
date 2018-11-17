#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <sstream>
#include <conio.h>
#include <shlwapi.h>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::experimental::filesystem;

class FileOrganizerClass
{
public:
	typedef std::vector<fs::directory_entry> dirent;

	dirent GetFiles()
	{
		dirent files;
		for (fs::directory_entry fileName : fs::directory_iterator(fs::current_path()))
			files.push_back(fileName);
		return files;
	}

	void MoveFiles(std::string fileTypeStr, fs::directory_entry currentPath, std::string newFile)
	{
		fs::path newPath;
		newPath = fs::current_path().append(fileTypeStr + "\\" + newFile);
		if (!fs::exists(fileTypeStr))
			fs::create_directory(fileTypeStr);
		if (!fs::exists(newPath))
		{
			fs::copy_file(currentPath, newPath);
			std::cout << "File " << newPath.filename().string() << " moved successfully to " << fileTypeStr << std::endl;
			fs::remove(currentPath);
		}
		else
		{
			std::cout << "File " << newPath.filename().string() << " already exits in " << fileTypeStr << std::endl;
		}
	}

	void OrganizeFiles()
	{
		dirent files = GetFiles();

		std::string fileExt;
		std::string docStr = "Documents";
		std::string audStr = "Audio";
		std::string vidStr = "Videos";
		std::string imgStr = "Images";
		std::string zipStr = "Compressed";
		std::string exeStr = "Programs";
		std::string miscStr = "Miscellaneous";

		char thisFile[MAX_PATH];
		DWORD size = GetModuleFileNameA(NULL, thisFile, MAX_PATH);

		for (fs::directory_entry fileName : files)
		{
			if (!fs::is_directory(fileName) && fileName != thisFile)
			{
				fileExt = fileName.path().extension().string();
				std::transform(fileExt.begin(), fileExt.end(), fileExt.begin(), ::tolower);
				bool txtExt =
					(fileExt == ".txt" || fileExt == ".doc" || fileExt == ".docx" || fileExt == ".html" ||
						fileExt == ".htm" || fileExt == ".odt" || fileExt == ".pdf" || fileExt == ".xls" ||
						fileExt == ".ods" || fileExt == ".ppt" || fileExt == ".pptx");

				bool audExt =
					(fileExt == ".mp3" || fileExt == ".wav" || fileExt == ".aac" || fileExt == ".ogg" ||
						fileExt == ".aax" || fileExt == ".aiff" || fileExt == ".dvf" || fileExt == ".flac" ||
						fileExt == ".m4a" || fileExt == ".m4b" || fileExt == ".mogg" || fileExt == ".vox" ||
						fileExt == ".wma" || fileExt == ".wv");

				bool vidExt =
					(fileExt == ".webm" || fileExt == ".mkv" || fileExt == ".flv" || fileExt == ".vob" ||
						fileExt == ".drc" || fileExt == ".gifv" || fileExt == ".mng" || fileExt == ".avi" ||
						fileExt == ".mov" || fileExt == ".qt" || fileExt == ".wmv" || fileExt == ".yuv" ||
						fileExt == ".rm" || fileExt == ".rmvb" || fileExt == ".asf" || fileExt == ".mp4" ||
						fileExt == ".m4p" || fileExt == ".m4v" || fileExt == ".mpg" || fileExt == ".mp2" ||
						fileExt == ".mpeg" || fileExt == ".mpe" || fileExt == ".mpv" || fileExt == ".3gp" ||
						fileExt == ".3g2" || fileExt == ".flv" || fileExt == ".f4v" || fileExt == ".f4p");

				bool imgExt =
					(fileExt == ".png" || fileExt == ".jpg" || fileExt == ".jpeg" || fileExt == ".gif" ||
						fileExt == ".ico" || fileExt == ".bmp" || fileExt == ".cpt" || fileExt == ".psd" ||
						fileExt == ".psp" || fileExt == ".xcf" || fileExt == ".ppm" || fileExt == ".pgm" ||
						fileExt == ".pbm" || fileExt == ".pnm" || fileExt == ".svg");

				bool zipExt =
					(fileExt == ".zip" || fileExt == ".rar" || fileExt == ".7z" || fileExt == ".cab" ||
						fileExt == ".tar" || fileExt == ".iso" || fileExt == ".egg");

				bool exeExt =
					(fileExt == ".bat" || fileExt == ".exe" || fileExt == ".msi" || fileExt == ".apk" ||
						fileExt == ".cmd" || fileExt == ".bin" || fileExt == ".lnk");

				if (txtExt)
					MoveFiles(docStr, fileName, fileName.path().filename().string());
				else if (audExt)
					MoveFiles(audStr, fileName, fileName.path().filename().string());
				else if (vidExt)
					MoveFiles(vidStr, fileName, fileName.path().filename().string());
				else if (imgExt)
					MoveFiles(imgStr, fileName, fileName.path().filename().string());
				else if (zipExt)
					MoveFiles(zipStr, fileName, fileName.path().filename().string());
				else if (exeExt)
					MoveFiles(exeStr, fileName, fileName.path().filename().string());
				else
					MoveFiles(miscStr, fileName, fileName.path().filename().string());
			}
		}
		std::cout << "\nFiles successfully organized" << std::endl;
	}
};

int main(int argc, char* argv[])
{
	FileOrganizerClass fileOrg;
	fileOrg.OrganizeFiles();
	_getch();
	return 0;
}