// �ṩ��PVZ����������޸ĵ�һ���װ

#pragma once

#include "PVZ.h"
#include "itab.h"

namespace PVZ {
	// ����pvzָ���ȡx86,���Դ˴�������64λָ��

	/**
	 * @brief Intelָ��ǰ׺
	*/
	struct Prefixes {
		BYTE lock;
		BYTE repeat;
		BYTE segment;
		BYTE operand;
		BYTE address;
	};

	/**
	 * @brief Intelָ�������
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
	 * @brief Intelָ��������
	*/
	struct InsAnalysis {
		size_t len;

		Prefixes pfx;

		Opcode opc;

		ModRM modrm;
		SIB sib;
	};

	/**
	 * @brief Mixin�����ռ� �ṩ��PVZ������޸Ĺ��ܵķ�װ
	*/
	namespace Mixin {
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
		bool Modify(int region_start, int region_end, BYTE* code, size_t code_len);

		/**
		 * @brief ȡָ��
		 * @param ins_addr ָ���ַ
		 * @param ins_data ָ������
		 * @return ָ��������
		*/
		InsAnalysis Fetch(int ins_addr, BYTE *ins_data);
	}
}