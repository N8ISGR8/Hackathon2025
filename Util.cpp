#include "Util.h"

int64_t selectedImage = 0;

void UploadImage(int64_t parent)
{
	std::string filename;
	std::string artname;
	std::string tagInput;
	std::vector<std::string> tags;
	std::cout << "type filename of your art below, remember to include the file extension. example: untitled.png\n";
	std::cin.ignore();
	std::getline(std::cin, filename);
	std::cout << "what's the name of your piece?\n";
	std::getline(std::cin, artname);
	std::cout << "write comma seperated tags your art falls under. example: cool,awesome,art\n";
	std::getline(std::cin, tagInput);
	std::istringstream iss{ tagInput };
	for (std::string token{}; std::getline(iss, token, ','); tags.push_back(token));
	std::ifstream file(filename, std::ios::binary);
	std::string sendImg((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	MongoDB::SendImage(artname, parent, tags, sendImg);

}

void Browse()
{
	std::cout << "5 wonderful pieces of art have been selected for your viewing.\nYou can choose (1-5) or 0 to return to the main menu\n";

	std::vector<int64_t> ids = MongoDB::GetNRandomIDs(5);
	for (int i = 0; i < ids.size(); ++i)
	{
		std::cout << (i+1) << ") " << MongoDB::GetNameFromID(ids[i]) << std::endl;
	}

	std::string userin;
	int userinint;
	std::cin >> userin;
	while (true)
	{
		try {
			userinint = stoi(userin);
			if (userinint > 5 || userinint < 0)
			{
				throw std::runtime_error("nuh uh");
			}
			break;
		}
		catch (const std::exception& e) {
			std::cout << "Nuh uh buddy - you need a number in the valid range!\n";
			std::cin >> userin;
		}
	}

	if (userinint == 0)
		return;
	selectedImage = ids[userinint - 1];
	OpenImage();
}

void OpenImage()
{
	std::string userin;
	int userinint;
	std::cout << "Opening Image..." << std::endl;

	std::string img = MongoDB::ReadImageFromId(selectedImage);
	std::string name = MongoDB::GetNameFromID(selectedImage);
	std::vector<std::string> tags = MongoDB::GetTags(selectedImage);
	for (std::string tag : tags)
	{
		name.append(", " + tag);
	}
	if (img.empty())
	{
		std::cout << "Image Load Failed..." << std::endl;
		return;
	}
	bool kill = false;
	bool open = false;
	std::thread t = std::thread(WindowRun, img, name, std::ref(kill), std::ref(open));

	while (!open);

	std::cout << "Enter 0 to exit\n1 to fork this image\nor 2 to view the image's family.\n";

	std::cin >> userin;
	while (true)
	{
		try {
			userinint = stoi(userin);
			if (userinint > 2 || userinint < 0)
			{
				throw std::runtime_error("nuh uh");
			}
			break;
		}
		catch (const std::exception& e) {
			std::cout << "Nuh uh buddy - you need a number in the valid range!\n";
			std::cin >> userin;
		}
	}

	if (userinint == 0)
	{
		kill = true;
		if (t.joinable())
			t.join();
		return;
	}
	else if (userinint == 1)
		ForkImage();
	// view family
	else
	{
		std::vector<int64_t> childrenIds = MongoDB::GetChildren(selectedImage);
		size_t size = childrenIds.size();
		int64_t parent = MongoDB::GetParent(selectedImage);
		std::cout << "Press 0 to exit the family viewer\n";
		if (parent != 0)
			std::cout << "Press 1 to view parent drawing\n";
		if (size > 0)
		{
			std::cout << "Press (2-" << size + 1 << ") to view child drawings\n";
			for (int i = 0; i < childrenIds.size(); ++i)
			{
				std::cout << (i + 2) << ") " << MongoDB::GetNameFromID(childrenIds[i]) << std::endl;
			}
		}

		std::cin >> userin;
		while (true)
		{
			try {
				userinint = stoi(userin);
				if (userinint > size + 1 || userinint < 0)
				{
					throw std::runtime_error("nuh uh");
				}
				break;
			}
			catch (const std::exception& e) {
				std::cout << "Nuh uh buddy - you need a number in the valid range!\n";
				std::cin >> userin;
			}
		}
		kill = true;
		if (t.joinable())
			t.join();
		if (userinint == 0)
			return;
			
		else if (userinint == 1 && parent != 0)
		{
			selectedImage = parent;
			OpenImage();
		}
		else if (userinint > 1 && size > 0)
		{
			selectedImage = MongoDB::GetChildren(selectedImage)[userinint - 2];
			OpenImage();
		}
	}
	kill = true;
	if(t.joinable())
		t.join();
}

void ImageFromName()
{
	std::string artName;
	std::cout << "type name to search below\n";
	std::cin.ignore();
	std::getline(std::cin, artName);
	std::vector<int64_t> ids = MongoDB::ReadImagesFromName(artName);
	if (ids.size() < 1)
	{
		std::cout << "No results :(";
		return;
	}
	std::cout << "0 to exit or\nPick a result (1-" << ids.size() << "): \n"; 
	for (int i = 0; i < ids.size(); ++i)
	{
		std::cout << (i + 1) << ") " << MongoDB::GetNameFromID(ids[i]) << std::endl;
	}
	std::string userin;
	int userinint;
	while (true)
	{
		try {
			userinint = stoi(userin);
			if (userinint > ids.size() || userinint < 0)
			{
				throw std::runtime_error("nuh uh");
			}
			break;
		}
		catch (const std::exception& e) {
			std::cout << "Nuh uh buddy - you need a number in the valid range!\n";
			std::cin >> userin;
		}
	}
	selectedImage = ids[userinint - 1];
	OpenImage();
}

void ForkImage()
{
	std::cout << "Begin fork upload.\n";
	UploadImage(selectedImage);
	std::cout << "End fork upload\n";
}

void menu() 
{
	while(true) 
	{
		std::string userin;
		int userinint;
		std::cout << "Welcome to NullPtr's Art-Forker! Press the corresponding number to choose the option:\n\n";
		std::cout << "1 for uploading an original image in the program's files (inserting manually)\n";
		std::cout << "2 for browsing the database of images uploaded,\n";
		std::cout << "or 3 for searching for art by name\n(0 to exit)\n";
		std::cout << "What'll it be, fellas?\n";
		std::cin >> userin;

		while(true) 
		{
			try {
				userinint = stoi(userin);
				if(userinint > 3 || userinint < 0) 
				{
					throw std::runtime_error("nuh uh");
				}
				break;
			}
			catch (const std::exception& e) {
				std::cout << "Nuh uh buddy - you need a number in the valid range!\n";
				std::cin >> userin;
			}
		}

		switch(userinint) 
		{
		case 0:
			return;
		case 1: 
			UploadImage();
			break;
		case 2:
			Browse();
			break;
		case 3:
			ImageFromName();
			break;
		}
		std::cout << "\n\n";
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