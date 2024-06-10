// 提供对PVZ程序本身代码修改的一层封装

#pragma once

#include "PVZ.h"
#include "itab.h"

typedef unsigned long long QWORD;

namespace PVZ {
	/**
	 * @brief Mixin命名空间 提供对PVZ代码的修改功能的封装
	*/
	namespace Mixin {
		// 由于pvz指令集采取x86,所以此处不优先考虑64位指令

		/**
		 * @brief 寄存器组
		*/
		enum class RegisterGroup {
			GPR, // 通用寄存器
			MMX, // MMX寄存器
			CR,  // 控制寄存器
			DB,  // 调试寄存器
			SEG, // 段寄存器
			XMM  // XMM寄存器
		};

		/**
		 * @brief REX前缀
		*/
		struct PrefixREX {
			BYTE w;
			BYTE r;
			BYTE x;
			BYTE b;
			BYTE raw;
		};

		/**
		 * @brief Intel指令前缀
		*/
		struct Prefixes {
			BYTE lock;

			BYTE str;
			// string的不同类型
			BYTE rep;
			BYTE repe;
			BYTE repne;

			BYTE segment;
			BYTE operand;
			BYTE address;
			PrefixREX rex;
		};

		struct ModRM {
			BYTE mod;
			BYTE reg;
			BYTE rm;
			BYTE raw;
		};

		struct SIB {
			BYTE scale;
			BYTE index;
			BYTE base;
			BYTE raw;
		};

		union ImmVal {
			BYTE val8;
			WORD val16;
			DWORD val32;
			QWORD val64;
			struct {
				WORD segment;
				WORD offset;
			} ptr16;
			struct {
				WORD segment;
				DWORD offset;
			} ptr32;
		};

		struct Operand {
			// 操作数类型
			OperandType type;
			WORD size;
			// sib
			BYTE scale;
			RegisterType index;
			RegisterType base;
			// 立即值
			ImmVal imm;
			WORD disp_size;
		};

		/**
		 * @brief Intel指令解析结果
		*/
		struct InsAnalysis {
			size_t len;

			Prefixes pfx;

			ModRM modrm;
			bool modrm_decoded;

			SIB sib;

			InstructionDefinition definition;
			Operand operands[4];

			BYTE operand_size;
			BYTE address_size;

			bool far_flag;
		};
		/**
		 * @brief 将长度为bufsz的buf中的第一条指令进行解码
		 * 
		 * 暂时不能解析一些SSE指令与64位指令
		 * 
		 * @param buf 缓存
		 * @param bufsz 缓存长度
		 * @param ins 指令 
		 * @return false为解码失败,true为解码成功
		*/
		bool Decode(BYTE *buf, size_t bufsz, InsAnalysis *ins);

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
		bool Modify(int region_start, int region_end, BYTE *code, size_t code_len);

		/**
		 * @brief 取指令
		 * @param ins_addr 指令地址
		 * @param ins_data 指令数据
		 * @return 指令解析结果
		*/
		InsAnalysis Fetch(int ins_addr, BYTE *ins_data);

		/**
		 * @brief 扫描某个区域 找到首个matcher接受的指令的地址
		 * @tparam MatchFunc 匹配函数 应当接收一个InsAnalysis的参数 返回一个bool的结果
		 * @param matcher 匹配函数
		 * @param region_start 区域起始
		 * @param region_end 区域结束
		 * @return 
		*/
		template<typename MatchFunc>
		int Scan(MatchFunc matcher, int region_start, int region_end) {
			int cur = region_start;
			while (cur < region_end) {
				InsAnalysis ins = Fetch(cur, NULL);

				if (matcher(ins)) {
					return cur;
				}

				cur += ins.len;
			}
			return 0;
		}

		/**
		 * @brief  获得当前存放代码的地址
		 *
		 * @return 当前存放代码的地址
		*/
		int& CodePlacingAddress();

		/**
		 * @brief 替换某个区域的代码。
		 * 
		 * 额外开辟一个区域存放code,并使用jmp指令跳转到code区域,在code区域末尾跳转回原区域
		 * 
		 * 若code将region_start视作本段代码的起始位置,则
		 * code中所有靠偏移量寻址的指令,应额外加上(CodePlacingAddress() - region_start)作为修正
		 *
		 * @param region_start 起始区域
		 * @param region_end   结束区域
		 * @param code         代码
		 * @param code_len     代码长度
		 * @return 是否替换成功
		*/
		bool Replace(int region_start, int region_end, BYTE *code, size_t code_len);

		/**
		 * @brief 向targetpoint后插入一段代码
		 * 
		 * 需要保证targetpoint附近没有按偏移寻址的指令(附近指:targetpoint ~ targetpoint + 5这一段)
		 * 额外开辟一个区域存code,并使用jmp指令跳转到code区域,在code区域末尾跳转回原区域
		 * Insert函数将targetpoint及其后1~4条指令变更为跳转到code区域的一个jmp指令,将该1~4条指令放置于区域末尾
		 * 
		 * @param targetpoint 目的点
		 * @param code 代码
		 * @param code_len 代码长度
		 * @param origin_code 被替换的代码, 记得将其delete
		 * @param origin_code_len 被替换的代码的长度
		 * @return 是否插入成功
		*/
		bool Insert(int targetpoint, BYTE *code, size_t code_len, BYTE **origin_code = NULL, size_t *origin_code_len = NULL);

		/**
		 * @brief 重定向某个函数
		 * @param function_start 函数起始点
		 * @param function_end  函数中止点
		 * @param new_function_address 函数地址
		 * @return 是否重定向成功
		*/
		bool Redirect(int function_start, int function_end, int new_function_address);
	}
}