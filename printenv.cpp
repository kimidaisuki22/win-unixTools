#include<vector>
#include<string>
#include<iostream>
#include<windows.h>
 
void write(const std::wstring& str);
std::vector<std::wstring> getEnvs();

int main()
{
	for (auto str : getEnvs())
	{
		str += L"\n";
		write(str);
	}
	return 0;
}


void write(const std::wstring& str) {
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), str.c_str(), str.size(), NULL, nullptr);
}

std::vector<std::wstring> getEnvs() {
	auto envStr = GetEnvironmentStringsW();
	if (envStr == nullptr)
		return {};
	auto pt = envStr;

	std::vector<std::wstring> envs;
	std::wstring buffStr;

	while (true)
	{
		if (*pt == 0)
		{
			envs.push_back(std::move(buffStr));
			if (*(pt + 1) == 0)
				break;
		}
		else {
			buffStr.push_back(*pt);
		}
		pt++;
	}
	FreeEnvironmentStringsW(envStr);
	return envs;
}