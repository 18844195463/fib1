#include <iostream>
#include "zf_log.h"
#ifndef TYPE_COUNT
	#include "datatype.h"
#endif
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#if defined(_WIN32) || defined(_WIN64)
	#include <windows.h>
#else
	#include <unistd.h>
	#include <sys/time.h>
#endif
char state[MAX_STRING_SIZE_ALL] = { 0 };

char* getUserDefinedType(char* str)
{
	for (int i = 1; i <= TYPE_COUNT; ++i)
	{
		if (!strcmp(str, "S_Temp"))
			return S_Temp::tostring();
		else
		{
			char* p = "";
			return p;
		}
	}
}
char* get_type(char* type)
{
	if (type == nullptr)
		return nullptr;
	if (!strcmp(type, "double"))
		return "%.4f, ";
	if (!strcmp(type, "float"))
		return "%.2f, ";
	if (!strcmp(type, "int32"))
		return "%d, ";
	if (!strcmp(type, "int64"))
		return "%d, ";
	if (!strcmp(type, "uint32"))
		return "%d, ";
	if (!strcmp(type, "uint64"))
		return "%d, ";
	if (!strcmp(type, "bool"))
		return "%d, ";
	if (!strcmp(type, "char"))
		return "%c, ";
	if (!strcmp(type, "int"))
		return "%d, ";
	if (!strcmp(type, "*"))
		return "%p, ";
	char* str = getUserDefinedType(type);
	return str;
}
void setfmt(int count, ...)
{
	if (!count)
		return;
	char wanted[MAX_STRING_SIZE_ALL] = {0};
	va_list va;
	va_start(va, count);
	if (strcmp(state, ""))
	{
		for (int i = 0; i < MAX_STRING_SIZE_ALL; ++i)
			state[i] = 0;
	}
	for (int num = 0; num < count; ++num)
	{
		char* type;
		type = va_arg(va, char*);
		strcat(state, get_type(type));
	}
	va_end(va);
	//strcpy(Log::state, wanted);
	//return wanted;
}

void write_to_log(char* str, ...)
{
	//ZF_LOGI(log, __VA_ARGS__);
}


void write_to_file(char* src, size_t buflen, const char* filename)
{
	char file_name[100] = { 0 };
	if (!filename)
		return;
	strcat(file_name, "E:\\");
	strcat(file_name, filename);
	SYSTEMTIME st;
	GetLocalTime(&st);
	char hour[10];
	char minute[10];
	char second[10];
	sprintf(hour, "%hu", st.wHour);
	sprintf(minute, "%hu", st.wMinute);
	sprintf(second, "%hu", st.wSecond);
	strcat(file_name, hour);
	strcat(file_name, minute);
	strcat(file_name, second);
	std::cout << file_name;
	FILE *fp;
	if ((fp = fopen(file_name, "w")) == NULL) {
		printf("File cannot be opened\n");
		//exit(0);
	}
	else
		printf("File opened for writing\n");
	char* ptr = src;
	for (size_t i = 0; i < buflen; i += 8)
	{
		printf("%02x: ", src + i);
		fprintf(fp, "%02x: ", src + i);
		for (size_t j = 0; j < 8; ++j)
		{
			if (i + j < buflen)
			{
				printf("%02x ", ptr[i + j]);
				fprintf(fp, "%02x ", ptr[i + j]);
			}
			else
			{
				fprintf(fp, " ");
				printf(" ");
			}
		}
		fprintf(fp, "\n");
		printf("\n");
		fflush(fp);
	}
	fclose(fp);
}