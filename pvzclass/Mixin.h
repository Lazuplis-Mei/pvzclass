// �ṩ��PVZ����������޸ĵ�һ���װ

#pragma once

#include "PVZ.h"
#include "itab.h"

typedef unsigned long long QWORD;

namespace PVZ {
	/**
	 * @brief Mixin�����ռ� �ṩ��PVZ������޸Ĺ��ܵķ�װ
	*/
	namespace Mixin {
		// ����pvzָ���ȡx86,���Դ˴������ȿ���64λָ��

		/**
		 * @brief �Ĵ�����
		*/
		enum class RegisterGroup {
			GPR, // ͨ�üĴ���
			MMX, // MMX�Ĵ���
			CR,  // ���ƼĴ���
			DB,  // ���ԼĴ���
			SEG, // �μĴ���
			XMM  // XMM�Ĵ���
		};

		/**
		 * @brief REXǰ׺
		*/
		struct PrefixREX {
			BYTE w;
			BYTE r;
			BYTE x;
			BYTE b;
			BYTE raw;
		};

		/**
		 * @brief Intelָ��ǰ׺
		*/
		struct Prefixes {
			BYTE lock;

			BYTE str;
			// string�Ĳ�ͬ����
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
			// ����������
			OperandType type;
			WORD size;
			// sib
			BYTE scale;
			RegisterType index;
			RegisterType base;
			// ����ֵ
			ImmVal imm;
			WORD disp_size;
		};

		/**
		 * @brief Intelָ��������
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
		 * @brief ������Ϊbufsz��buf�еĵ�һ��ָ����н���
		 * 
		 * ��ʱ���ܽ���һЩSSEָ����64λָ��
		 * 
		 * @param buf ����
		 * @param bufsz ���泤��
		 * @param ins ָ�� 
		 * @return falseΪ����ʧ��,trueΪ����ɹ�
		*/
		bool Decode(BYTE *buf, size_t bufsz, InsAnalysis *ins);

		/**
		 * @brief �޸�PVZ�����ĳ�δ���
		 * 
		 * Modify������[region_start, region_end)���ֵĴ����滻Ϊָ���Ĵ���(��code)��
		 * ��code_len > region_start - region_end, ���������޷������Щ����, modify�����˳�������false
		 * ��code_len <= region_start - region_end, modify�����򽫸ò��ִ����滻Ϊָ������,���ڽ�β����nopָ��
		 * 
		 * @param region_start �滻����Ŀ�ʼ��ַ
		 * @param region_end �滻����Ľ�����ַ
		 * @param code ָ��Ҫ�滻�Ĵ���
		 * @param code_len ����ĳ���
		 * @return false�����滻ʧ��, true�����滻�ɹ�
		*/
		bool Modify(int region_start, int region_end, BYTE *code, size_t code_len);

		/**
		 * @brief ȡָ��
		 * @param ins_addr ָ���ַ
		 * @param ins_data ָ������
		 * @return ָ��������
		*/
		InsAnalysis Fetch(int ins_addr, BYTE *ins_data);

		/**
		 * @brief ɨ��ĳ������ �ҵ��׸�matcher���ܵ�ָ��ĵ�ַ
		 * @tparam MatchFunc ƥ�亯�� Ӧ������һ��InsAnalysis�Ĳ��� ����һ��bool�Ľ��
		 * @param matcher ƥ�亯��
		 * @param region_start ������ʼ
		 * @param region_end �������
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
		 * @brief  ��õ�ǰ��Ŵ���ĵ�ַ
		 *
		 * @return ��ǰ��Ŵ���ĵ�ַ
		*/
		int& CodePlacingAddress();

		/**
		 * @brief �滻ĳ������Ĵ��롣
		 * 
		 * ���⿪��һ��������code,��ʹ��jmpָ����ת��code����,��code����ĩβ��ת��ԭ����
		 * 
		 * ��code��region_start�������δ������ʼλ��,��
		 * code�����п�ƫ����Ѱַ��ָ��,Ӧ�������(CodePlacingAddress() - region_start)��Ϊ����
		 *
		 * @param region_start ��ʼ����
		 * @param region_end   ��������
		 * @param code         ����
		 * @param code_len     ���볤��
		 * @return �Ƿ��滻�ɹ�
		*/
		bool Replace(int region_start, int region_end, BYTE *code, size_t code_len);

		/**
		 * @brief ��targetpoint�����һ�δ���
		 * 
		 * ��Ҫ��֤targetpoint����û�а�ƫ��Ѱַ��ָ��(����ָ:targetpoint ~ targetpoint + 5��һ��)
		 * ���⿪��һ�������code,��ʹ��jmpָ����ת��code����,��code����ĩβ��ת��ԭ����
		 * Insert������targetpoint�����1~4��ָ����Ϊ��ת��code�����һ��jmpָ��,����1~4��ָ�����������ĩβ
		 * 
		 * @param targetpoint Ŀ�ĵ�
		 * @param code ����
		 * @param code_len ���볤��
		 * @param origin_code ���滻�Ĵ���, �ǵý���delete
		 * @param origin_code_len ���滻�Ĵ���ĳ���
		 * @return �Ƿ����ɹ�
		*/
		bool Insert(int targetpoint, BYTE *code, size_t code_len, BYTE **origin_code = NULL, size_t *origin_code_len = NULL);

		/**
		 * @brief �ض���ĳ������
		 * @param function_start ������ʼ��
		 * @param function_end  ������ֹ��
		 * @param new_function_address ������ַ
		 * @return �Ƿ��ض���ɹ�
		*/
		bool Redirect(int function_start, int function_end, int new_function_address);
	}
}