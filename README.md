# pvzclass-with-events
pvzclass 是一个用于控制植物大战僵尸游戏内部运行实体的一套框架

## with events?

在处理时有种种问题，例如：

+ 如何知道玩家种下了一棵植物？
+ 如何知道玩家铲掉或僵尸啃掉了一棵植物？

等这些问题，或许不需要事件监听，但会比较繁琐。

本人受到Bukkit Events API启发。

将会不断完善其它的事件。

（新人刚来）

## 安装方法

### 手动安装（推荐）

直接打包zip吧。

### 手动安装2

请先下载[pvzclass](https://github.com/Lazuplis-Mei/pvzclass)，然后在PVZ.cpp中找到

```cpp
	class Plant
	{
		int BaseAddress;
#if _DEBUG
		PlantType::PlantType DebugType;
#endif
	public:
		Plant(int indexoraddress);
```

将其修改为：

```cpp

	class Plant
	{
	public:
		int BaseAddress;
#if _DEBUG
		PlantType::PlantType DebugType;
#endif
		Plant(int indexoraddress);
```
然后下载EventHandler.h/.cpp就完成了。

##怎么用？

pvzclass.cpp。
