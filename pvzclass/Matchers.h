#pragma once

#include "Mixin.h"


namespace PVZ {
	namespace Mixin {
		/**
		 * @brief 一些现成的匹配器
		*/
		namespace Matchers {
			template<int count, MnemonicCode mnemonic>
			class CountingMnemonicMatcher {
			private:
				int ptr;
			public:
				CountingMnemonicMatcher() : ptr(0)
				{
				}
				~CountingMnemonicMatcher() {
				}
				bool operator()(InsAnalysis ins) {
					if (mnemonic == MC_ANY || ins.definition.mnemonic == mnemonic) {
						ptr++;
					}
					return ptr == count;
				}
			};

			template<int count>
			using CountingMatcher = CountingMnemonicMatcher<count, MC_ANY>;

			template<MnemonicCode mnemonic>
			using MnemonicMatcher = CountingMnemonicMatcher<1, mnemonic>;
		}
	}
}