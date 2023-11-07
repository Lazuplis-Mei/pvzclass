#pragma once
namespace ThreeState
{
	//功能的启动状态
	enum ThreeState
	{
		//禁用功能。任何情况下该特性都失效。
		Disable = -1,
		//恢复默认情况。
		None,
		//启用功能。任何情况下该特性都生效。
		Enable
	};

	extern const char* ToString(ThreeState mouset);

}