#pragma once

struct OffsetSignature
{
	std::string pattern;
	bool read;
	LPVOID* offset;
};

inline LPVOID oGameTime;
inline LPVOID oChatClient;
inline LPVOID oLocalPlayer;
inline LPVOID oHudInstance;
inline LPVOID oViewProjMatrices;
inline LPVOID oHeroList;
inline LPVOID oTurretList;
inline LPVOID oInhibitorList;
inline LPVOID oMinionList;

inline LPVOID oPrintChat;
inline LPVOID oIssueOrder;
inline LPVOID oIsAlive;
inline LPVOID oGetAttackDelay;
inline LPVOID oGetAttackCastDelay;

inline OffsetSignature signaturesToScan[] = {
	{
		"8B 0D ? ? ? ? 8A D8 85 C9",
		true, &oChatClient
	},
	{
		"8B 3D ? ? ? ? 3B F7 75 09",
		true, &oLocalPlayer
	},
	{
		"8B 0D ? ? ? ? 6A 00 8B 49 34",
		true, &oHudInstance
	},
	{
		"B9 ? ? ? ? E8 ? ? ? ? B9 ? ? ? ? E8 ? ? ? ? B9 ? ? ? ?",
		true, &oViewProjMatrices
	},
	{
		"8B 15 ? ? ? ? 0F 44 C1",
		true, &oHeroList
	},
	{
		"8B 35 ? ? ? ? 8B 76 18",
		true, &oTurretList
	},
	{
		"A1 ? ? ? ? 53 55 56 8B 70 04 8B 40 08",
		true, &oInhibitorList
	},
	{
		"A3 ? ? ? ? E8 ? ? ? ? 83 C4 04 85 C0 74 32",
		true, &oMinionList
	},
	{
		"E8 ? ? ? ? 8B 4C 24 20 C6 47 0D 01",
		false, &oPrintChat
	},
	{
		"83 EC 3C 53 8B 1D ? ? ? ?",
		false, &oIssueOrder
	},
	{
		"8B 44 24 04 51 F3",
		false, &oGetAttackDelay
	},
	{
		"83 EC 0C 53 8B 5C 24 14 8B CB 56 57 8B 03 FF 90",
		false, &oGetAttackCastDelay
	},
	{
		"56 8B F1 8B 06 8B 80 8C 00 00 00 FF D0 84 C0 74 19",
		false, &oIsAlive
	}
};

inline BYTE* FindAddress(const std::string& pattern)
{
	std::vector<int> bytes;
	std::vector<bool> mask;
	std::string strByte;
	std::istringstream iss(pattern, std::istringstream::in);
	while (iss >> strByte)
	{
		if (strByte == "?")
		{
			bytes.push_back(0x00);
			mask.push_back(false);
		}
		else
		{
			bytes.push_back(std::stoi(strByte, nullptr, 16));
			mask.push_back(true);
		}
	}
	const auto module = GetModuleHandle(nullptr);
	const auto dosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
	const auto ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<BYTE*>(module) + dosHeader->e_lfanew);
	const auto textSection = IMAGE_FIRST_SECTION(ntHeaders);
	const auto startAddress = reinterpret_cast<BYTE*>(module) + textSection->VirtualAddress;
	const DWORD size = textSection->SizeOfRawData;
	const auto endAddress = startAddress + size - bytes.size();
	MEMORY_BASIC_INFORMATION mbi;
	for (auto pageStart = startAddress; pageStart < endAddress;)
	{
		if (!VirtualQuery(pageStart, &mbi, sizeof(mbi))) break;
		pageStart = static_cast<BYTE*>(mbi.BaseAddress);
		const auto pageEnd = pageStart + mbi.RegionSize;
		if (mbi.Protect != PAGE_NOACCESS)
		{
			for (auto address = pageStart; address < pageEnd - bytes.size(); address++)
			{
				bool found = true;
				for (size_t i = 0; i < bytes.size(); i++)
				{
					if (mask[i] && bytes[i] != address[i])
					{
						found = false;
						break;
					}
				}
				if (found) return address;
			}
		}
		pageStart = pageEnd;
	}
	return nullptr;
}

inline void Scan(bool init)
{
	if (init)
	{
		const std::string pattern = "F3 0F 11 05 ? ? ? ? 8B 49 08";
		if (auto address = FindAddress(pattern); !address)
		{
			MessageBox(nullptr, "Failed to find GameTime", "WARN", MB_OK | MB_ICONWARNING);
		}
		else
		{
			address = *reinterpret_cast<BYTE**>(address + pattern.find_first_of('?') / 3);
			oGameTime = address;
		}
	}
	else
	{
		for (const auto& [pattern, read, offset] : signaturesToScan)
		{
			if (auto address = FindAddress(pattern); !address)
			{
				MessageBoxA(nullptr, ("Failed to find pattern: " + pattern).c_str(), "WARN", MB_OK | MB_ICONWARNING);
			}
			else
			{
				if (read) address = *reinterpret_cast<BYTE**>(address + pattern.find_first_of('?') / 3);
				else if (address[0] == 0xE8) address = address + *reinterpret_cast<DWORD*>(address + 1) + 5;
				*offset = address;
			}
		}
	}
}
