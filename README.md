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
