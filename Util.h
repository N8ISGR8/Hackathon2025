#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "DBHandler.h"
#include <cmath>
#include <sstream>
#include <thread>
#include "Window.h"
#include <filesystem>

//what do you want
void menu();

// prompt and get file to upload to db
void UploadImage(int64_t parent = 0);

void Browse();

void OpenImage();

// currently open art window
void ImageFromName();

void ForkImage();

void GetContributions();