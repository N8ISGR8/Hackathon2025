#pragma once
#include <vector>
#include <string>

// prompt and get file to upload to db
void UploadImage();

void Browse();

std::vector<int64_t> GetRandomIDs();

std::string GetNameFromID(int64_t id);

// currently open art window
void DownloadImage();

void ForkImage();