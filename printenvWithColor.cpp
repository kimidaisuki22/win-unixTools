#include<vector>
#include<string>
#include<iostream>
#include<windows.h>

void write(const std::wstring& str);
std::vector<std::wstring> getEnvs();
std::vector<std::wstring> split(const std::wstring& str);
int main()
{
	for (auto str : getEnvs())
	{
		auto p = str.find(L"=");
		auto  p1 = str.substr(0, p);
		auto p2 = str.substr(p + 1);

		write(L"\033[38;2;152;195;121m");
		write(p1 + L"\n");
		write(L"\033[38;2;97;175;239m");

		for (auto value : split(p2)) {
			write(value + L"\n");
		}
		write(L"\n");
	}
	write(L"\033[0m");
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

std::vector<std::wstring> split(const std::wstring& str) {
	std::vector<std::wstring > retv;
	std::wstring buff;

	for (auto ch : str) {
		buff.push_back(ch);
		if (ch == L';') {
			retv.push_back(std::move(buff));
		}
	}
	if (!buff.empty())
		retv.push_back(std::move(buff));

	return retv;
}