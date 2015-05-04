#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <stdio.h>
#include <algorithm>
#include <Windows.h>


#include <windows.h>
size_t cache_line_size() {
	size_t line_size = 0;
	DWORD buffer_size = 0;
	DWORD i = 0;
	SYSTEM_LOGICAL_PROCESSOR_INFORMATION * buffer = 0;

	GetLogicalProcessorInformation(0, &buffer_size);
	buffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION *)malloc(buffer_size);
	GetLogicalProcessorInformation(&buffer[0], &buffer_size);

	for (i = 0; i != buffer_size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); ++i) {
		if (buffer[i].Relationship == RelationCache && buffer[i].Cache.Level == 1) {
			line_size = buffer[i].Cache.LineSize;
			break;
		}
	}

	free(buffer);
	return line_size;
}

struct MyStruct
{
	int i;
	int* p;
	//std::string s;
};

int main()
{
	std::cout << std::is_pod < MyStruct >::value << "\n";


	SYSTEM_INFO s;
	GetSystemInfo(&s);

	std::cout << s.dwPageSize << "\n";
	std::cout << cache_line_size() << "\n";

	system("PAUSE");
}