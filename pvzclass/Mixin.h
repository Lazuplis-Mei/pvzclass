// 提供对PVZ程序本身代码修改的一层封装

#pragma once

#include "PVZ.h"
#include "itab.h"

namespace PVZ {
	// 由于pvz指令集采取x86,所以此处不考虑64位指令

	/**
	 * @brief Intel指令前缀
	*/
	struct Prefixes {
		BYTE lock;
		BYTE repeat;
		BYTE segment;
		BYTE operand;
		BYTE address;
	};

	/**
	 * @brief Intel指令操作码
	*/
	struct Opcode {
		BYTE byte1;
		BYTE byte2;
		BYTE byte3;
	};

	struct ModRM {
		BYTE mod;
		BYTE reg;
		BYTE rm;
	};

	struct SIB {
		BYTE scale;
		BYTE index;
		BYTE base;
	};

	/**
	 * @brief Intel指令解析结果
	*/
	struct InsAnalysis {
		size_t len;

		Prefixes pfx;

		Opcode opc;

		ModRM modrm;
		SIB sib;
	};

	/**
	 * @brief Mixin命名空间 提供对PVZ代码的修改功能的封装
	*/
	namespace Mixin {
		/**
		 * @brief 修改PVZ程序的某段代码
		 * 
		 * Modify函数将[region_start, region_end)部分的代码替换为指定的代码(即code)。
		 * 若code_len > region_start - region_end, 即区域内无法存放这些代码, modify函数退出并返回false
		 * 若code_len <= region_start - region_end, modify函数则将该部分代码替换为指定代码,并在结尾补充nop指令
		 * 
		 * @param region_start 替换区域的开始地址
		 * @param region_end 替换区域的结束地址
		 * @param code 指定要替换的代码
		 * @param code_len 代码的长度
		 * @return false代表替换失败, true代表替换成功
		*/
		bool Modify(int region_start, int region_end, BYTE* code, size_t code_len);

		/**
		 * @brief 取指令
		 * @param ins_addr 指令地址
		 * @param ins_data 指令数据
		 * @return 指令解析结果
		*/
		InsAnalysis Fetch(int ins_addr, BYTE *ins_data);
	}
}