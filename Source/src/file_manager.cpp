#include "file_manager.h"
#include <fstream>
#include <iostream>

bool FileManager::get_fileExists() {
	return m_fileExists;
}

FileManager::FileManager(std::string filename)
						: m_filename(filename),
						m_fileExists(false) {
	std::fstream file;
	file.open(m_filename);
	if (!file.is_open()) { 
		m_fileExists = false; 
		return; }
	m_fileExists = true;
	file.close();
}

std::string FileManager::get_filename() {
	return m_filename;
}

bool FileManager::remove_file() {
	if (!get_fileExists())
	{
		return false;
	}
	if (std::remove(get_filename().c_str()) != 0) {
		return false;
	}
	return true;
}