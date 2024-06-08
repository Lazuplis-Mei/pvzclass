#include "Mixin.h"

using namespace PVZ;
using namespace PVZ::Mixin;

bool PVZ::Mixin::Modify(int region_start, int region_end, BYTE* code, size_t code_len) {
	size_t region_len = region_end - region_start;
	if (region_len - region_end < code_len) {
		return false;
	}

	BYTE* writting_code = new BYTE[region_len];
	memset(writting_code, 0, region_len);
	memcpy(writting_code, code, code_len);

	// ÐÞ¸Ä´úÂë
	BOOL status = Memory::WriteArray<BYTE>(region_start, writting_code, region_len);
	return status == TRUE;
}