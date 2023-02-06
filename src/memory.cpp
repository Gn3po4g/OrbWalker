#include "pch.h"

Memory::Memory() : sig_to_scan{ {
	{&offsets.oGameTime, "F3 0F 11 05 ? ? ? ? 8B 49 08", true},
	{&offsets.oChatClient, "8B 0D ? ? ? ? 8A D8 85 C9", true},
	{&offsets.oLocalPlayer, "8B 3D ? ? ? ? 3B F7 75 09", true},
	{&offsets.oHudInstance, "8B 0D ? ? ? ? 6A 00 8B 49 34", true},
	{&offsets.oViewProjMatrices, "B9 ? ? ? ? 56 E8 ? ? ? ? 8D 46 40", true},
	{&offsets.oHeroList, "89 44 24 18 A1 ? ? ? ? 53", true},
	{&offsets.oTurretList, "8B 35 ? ? ? ? 8B 76 18", true},
	{&offsets.oInhibitorList, "A1 ? ? ? ? 53 55 56 8B 70 04 8B 40 08", true},
	{&offsets.oMinionList, "A3 ? ? ? ? E8 ? ? ? ? 83 C4 04 85 C0 74 32", true},
	{&offsets.oPrintChat, "E8 ? ? ? ? 8B 4C 24 20 C6 47 0D 01", false},
	{&offsets.oIssueOrder, "83 EC 3C 53 8B 1D ? ? ? ?", false},
	{&offsets.oGetAttackDelay, "E8 ? ? ? ? D8 44 24 14 83 C4 04", false},
	{&offsets.oGetAttackCastDelay, "E8 ? ? ? ? D9 9E ? ? ? ? 57", false},
	{&offsets.oIsAlive, "E8 ? ? ? ? 84 C0 74 2A 8D 8F ? ? ? ?", false}
} } {
	do {
		Sleep(500);
		Scan(true);
	} while(*(int*)(*(PDWORD)offsets.oGameState + 0x8) != 2);
	Sleep(500);
	Scan(false);
}

PBYTE Memory::FindAddress(const std::string& pattern) {
	using namespace std;
	vector<BYTE> bytes;
	vector<bool> mask;
	istringstream iss(pattern);
	string byte_str;
	for_each(istream_iterator<string>(iss), istream_iterator<string>(),
		[&](const string& byte_str) {
			if(byte_str == "?") {
				bytes.push_back(0x00);
				mask.push_back(false);
			} else {
				bytes.push_back(stoi(byte_str, nullptr, 16));
				mask.push_back(true);
			}
		});
	const auto module = GetModuleHandle(nullptr);
	const auto ntHeaders = (PIMAGE_NT_HEADERS)((PBYTE)module + ((PIMAGE_DOS_HEADER)module)->e_lfanew);
	const auto textSection = IMAGE_FIRST_SECTION(ntHeaders);
	const auto startAddress = (PBYTE)module + textSection->VirtualAddress;
	const DWORD size = textSection->SizeOfRawData;
	const auto endAddress = startAddress + size - bytes.size();

	MEMORY_BASIC_INFORMATION mbi;
	for(PBYTE page_start = startAddress, page_end;
		page_start < endAddress && VirtualQuery(page_start, &mbi, sizeof(mbi));
		page_start = page_end) {
		page_start = (PBYTE)mbi.BaseAddress;
		page_end = page_start + mbi.RegionSize;
		if(mbi.Protect != PAGE_NOACCESS) {
			for(auto address = page_start; address < page_end - bytes.size(); address++) {
				if(all_of(address, address + bytes.size(), [&](const auto& byte) {
					return !mask[&byte - address] || bytes[&byte - address] == byte;
					})) return address;
			}
		}
	}
	return nullptr;
}

void Memory::Scan(const bool init) {
	if(init) {
		const std::string pattern = "A1 ? ? ? ? 68 ? ? ? ? 8B 70 08 ";
		if(auto address = FindAddress(pattern); !address) {
			MessageBox(nullptr, "Failed to find GameState", "WARN", MB_OK | MB_ICONWARNING);
		} else {
			offsets.oGameState = *(PBYTE*)(address + pattern.find_first_of('?') / 3);
		}
	} else {
		for(const auto& [offset, pattern, read] : sig_to_scan) {
			if(auto address = FindAddress(pattern); !address) {
				MessageBoxA(nullptr, ("Failed to find pattern: " + pattern).c_str(), "WARN", MB_OK | MB_ICONWARNING);
			} else {
				if(read) address = *(PBYTE*)(address + pattern.find_first_of('?') / 3);
				else if(address[0] == 0xE8)	address = address + *(PDWORD)(address + 1) + 5;
				*offset = address;
			}
		}
	}
}