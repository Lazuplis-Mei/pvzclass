// �ṩ��PVZ����������޸ĵ�һ���װ

#pragma once

#include "PVZ.h"

namespace PVZ {
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
	}
}