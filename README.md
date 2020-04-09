<<<<<<< HEAD
# pvzlass 是一个用于控制植物大战僵尸游戏内部运行实体的一套框架

## pvzclass-with-events 附加

### EventHandler是一个类。这个类可以被构造：

```cpp
EventHandler(PVZ* pvz);
```

这个类可以注册所有的监听器：

+ `PlantPlantEvent`-PVZ::Plant*
+ `PlantRemoveEvent`-PVZ::Plant*
+ `PlantUpgradeEvent`-PVZ::Plant*
+ `LevelOpenEvent`-void
+ `LevelCloseEvent`-void
+ `LevelWaveEvent`-int

格式：
`注册名`——`函数传递参数`

注册监听器需要将register放到前面。

+ `RegisterPlantPlantEvent(...)`

`Run` 代表运行一次监听器。

**注意：Run只能进行一次监听，不能持久，不会多开线程**

监听的函数必须有一个相对应的参数。

`void onPlant( PVZ::Plant *e )`

代码：

```cpp
#include "events.h"
///...
void plant(PVZ::Plant e)//e与参数对应
{
	cout << "found Plant on " << e.Row << " " << e.Column << " " << ToString(e.Type) << endl;
}
void open(void)//其实这里void可以拿走
{
        cout << "open" << endl;
}
void wave(int w)
{
        cout << "wave is: " << wave << endl;
}
//...
int main()
{
//...
	EventHandler e(pvz);
	e.RegisterPlantPlantEvent(plant);
	e.RegisterLevelOpenEvent(open);
	while (1)
		e.Run();      //进行一次监听
//...
}
```
=======
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
>>>>>>> 68a069ecf44f19bb2c8f60f8a0a930b0703eddd1
