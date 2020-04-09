# pvzlass 是一个用于控制植物大战僵尸游戏内部运行实体的一套框架

<<<<<<< HEAD
## 框架将游戏内部的对象进行了封装，供监视和控制，同时提供了一系列内部的方法，以下有几个注意点

* 要编译这个框架，你需要使用 **Visual Studio 2019 (v142平台工具集)**
* 框架仅能完全适用于**1.0.0.1051版本**的游戏
* 程序从pvzclass.cpp的main函数开始运行，你可以直接在里面修改，编写你的程序，也可以用如下的格式构建

```cpp
#include "pvzclass.h"

int main()
{
    DWORD pid = ProcessOpener::Open();
    if (pid) {
        PVZ* pPVZ = new PVZ(pid);
        /*在这里编写你的代码*/

        delete pPVZ;
        }
    return 0;
}
```

* **不要忘记delete pPVZ关闭句柄**

---

### 关于ProcessOpener

* 这是一个只有静态成员的类
* 它提供了获取游戏**进程标识符**的函数
* 你可以通过修改它的4个静态字段来修改默认的寻找参数
* 你可以手动调用指定函数来寻找游戏
* 默认Open()函数寻找的顺序是 进程名->窗口标题->文件路径
* 失败返回0

### 关于PVZ类

* 必须new一个PVZ类型的对象(参数是**进程标识符**)，才可以使用PVZ类中的属性和方法

```cpp
PVZ* pPVZ = new PVZ(pid);
pPVZ->Sun = 9990;//修改阳光
pPVZ->Win();//直接获胜
```

* 当已经拥有PVZ类型的对象pPVZ时，才可以使用PVZ类中的静态成员类，如Memory

```cpp
int address = PVZ::Memory::AllocMemory();//申请内存空间
```

* 当PVZ类型的对象被delete后，PVZ类中的静态成员类亦无法使用

* 属性BaseAddress可以用于判断游戏当前是否在关卡内(0为不在)，**绝大多数功能必须在关卡内部才可以使用**

### 关于Memory类

* 这是一个只有静态成员的类
* 是PVZ的成员类
* 它提供了对游戏内存的以下功能

>内存的读写

```cpp
/*你可以使用任何数据类型去读写内存*/

int var = PVZ::Memory::ReadMemory<int>(0x750000);//读内存0x750000的一个整数值
PVZ::Memory::WriteMemory<int>(0x750000, 100);//写内存0x750000的为整数100

/*读写文本(数组)*/

char str1[50];
//STRING是一个宏，等价于str,sizeof(str)/sizeof(*str)，后者的值会在编译期被计算出来
PVZ::Memory::ReadArray<char>(0x750000, STRING(str1));
char str2[50] = "这是用于测试的文本";
PVZ::Memory::WriteArray<char>(0x750000, STRING(str1));

/*读指针*/

int sun = PVZ::Memory::ReadPointer(0x6A9EC0, 0x768, 0x5560);

```

>远程线程注入

```cpp
byte asmcode[] = { RET };//RET是一个宏，等价于0xC3
PVZ::Memory::Execute(STRING(asmcode));
```

>设置内存可完全访问

```cpp
PVZ::Memory::AllAccess(0x750000);
```

>内存申请与释放

```cpp
int address = PVZ::Memory::AllocMemory();
PVZ::Memory::FreeMemory(address);
```

>dll注入

```cpp
PVZ::Memory::InjectDll("yourdll.dll");
```

* 静态字段mainwindowhandle是游戏的窗口句柄

### 关于Animation类

* 是PVZ的成员类
* 它的对象代表了游戏中的一个动画实体
* 它有2个静态方法

> UnLock(int animprop)用于解锁属性，如不解锁，这些属性将是只读的

```cpp
//AP_开头的宏表示动画属性，可以用"|"隔开
PVZ::Animation::UnLock(AP_PLANTCOLOR | AP_ZOMBIECOLOR);
```

> Lock()用于重新锁定被解锁的属性

* 可以通过其他对象的GetAnimation()方法取得对应的动画对象
* 可以手动获取整个游戏中的第n个对象

```cpp
PVZ::Animation* anim = new PVZ::Animation(0);//获得第1个对象
```

### 关于唯一指定的类

* 是PVZ的成员类
* 需要用pPVZ->GetXXX的方式获得，**不要手动new**
* 以下类属于唯一指定的
* 通常起控制作用

1. Lawn
2. Icetrace
3. Wave(需要参数指定是当前关卡的第几波)
4. Mouse
5. MousePointer
6. Caption
7. Miscellaneous
8. SaveData
9. Music

### 关于游戏内的对象实体类

* 是PVZ的成员类
* 需要手动获取整个游戏中的第n个对象，方法同Animation类
* 部分类可以用pPVZ->GetAllXXX的方式一次获得当前全部可用的对象

```cpp
PVZ::Zombie* zombies[100];
int num = pPVZ->GetAllZombies(zombies);//返回实际获取到的对象数量
```

* 以下类属于游戏内的对象实体类

1. Zombie
2. Projectile
3. Plant
4. Coin
5. Lawnmover
6. Griditem(Grave,Crater,Brain,Vase类的基类)
7. CardSlot

### 关于SeedCard类和GardenPlant类

* 分别是CardSlot类和SaveData类的成员类
* 需要用上一级类的对象的->GetXXX的方式获得
* 可以手动获取整个游戏中的第n个对象，方法同Animation类

### 关于枚举类型

* 每一种枚举类型都在其各自的名称空间里
* 每一种枚举类型的名称空间里都有ToString方法，可以将枚举类型转化为字符串

### 关于Extensions.h

* 默认在pvzclass.h中被包含
* 不是必须的
* 提供了几个常用的修改功能
* 参数是代表开启还是关闭功能

### 关于Creater

* Creater是一个名称空间
* 声明和定义默认在pvzclass.h中被包含
* 提供了在游戏中创建实体的函数
* **AsmInit函数是部分方法的初始化函数**，只需要调用一次
* 以下函数需要必须要初始化才能使用

1. 重载函数CreateProjectile(ProjectileType::ProjectileType,int,int,float,float);
2. __CreatePortal
3. CreatePortal

* FrozeAll函数需要在关卡出现过植物的情况下才有效果
=======
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
>>>>>>> 68a069ecf44f19bb2c8f60f8a0a930b0703eddd1
