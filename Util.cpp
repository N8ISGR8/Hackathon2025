#include "Util.h"


void UploadImage(int64_t ay = 0) 
{
	std::string filename;
	std::string artname;
	std::string tag1;
	std::string tag2;
	std::cout << "type filename of your art below, remember to include the file extension. example: untitled.png";
	std::cin >> filename;
	std::cout << "what's the name of your piece?";
	std::cin >> artname;
	std::cout << "write two tags your art falls under below:";
	std::cin >> tag2;
	std::cin >> tag1;
	std::ifstream file(filename, std::ios::binary);
	std::string sendImg((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	MongoDB::SendImage(artname, ay, {tag1, tag2}, sendImg);

}

void menu() 
{
	while(true) 
	{
		std::string userin;
		int userinint;
		std::cout << "Welcome to NullPtr's Art-Forker! Press the corresponding number to choose the option:\n\n";
		std::cout << "1 for uploading an image in the program's files (insert manually), 2 for browsing the database of images uploaded,\n";
		std::cout << "3 for downloading an image from the database, and - most excitingly - 4 for forking an artpiece in the database.\n\n";
		std::cout << "What'll it be, fellas?\n";
		std::cin >> userin;

		while(true) 
		{
			try {
				userinint = stoi(userin);
				if(userinint > 4 || userinint < 1) 
				{
					throw std::runtime_error("nuh uh");
				}
				break;
			}
			catch (const std::exception& e) {
				std::cout << "Nuh uh buddy - you need an int in the valid range!\n";
				std::cin >> userin;
			}
		}

		switch(userinint) 
		{
		case 1: 
			UploadImage();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		}

	}
}

//void menu();

// prompt and get file to upload to db
//void UploadImage();

//void Browse();

//std::vector<int64_t> GetRandomIDs();

//std::string GetNameFromID(int64_t id);

// currently open art window
//void DownloadImage();

//void ForkImage();