#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "DBHandler.h"
#include <cmath>

//what do you want
void menu();

// prompt and get file to upload to db
void UploadImage(int64_t parent = 0);

void Browse();

std::vector<int64_t> GetRandomIDs();

std::string GetNameFromID(int64_t id);

// currently open art window
void DownloadImage();

void ForkImage();