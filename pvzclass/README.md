# pvzlass 是一个用于控制植物大战僵尸游戏内部运行实体的一套框架

## pvzclass-with-events 附加

### EventHandler是一个类。这个类可以被构造：

```cpp
EventHandler(PVZ* pvz);
```

这个类可以注册所有的监听器：

+ `PlantPlantEvent`
+ `PlantRemoveEvent`
+ `PlantUpgradeEvent`

注册监听器需要将register放到前面。

+ `registerPlantPlantEvent(...)`

`run` 代表运行一次监听器。

**注意：run只能进行一次监听，不能持久，不会多开线程**

监听的函数必须有一个相对应的参数。

`void onPlant( PVZ::Plant e )`

代码：

```cpp
#include "events.h"
///...
void plant(PVZ::Plant e)
{
	cout << "found Plant on " << e.Row << " " << e.Column << " " << ToString(e.Type) << endl;
}
//...
int main()
{
//...
	EventHandler e(pvz);
	e.registerPlantPlantEvent(plant);
	while (1)
		e.run();      //run once
//...
}
```
