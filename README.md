# pvzclass 是一个用于控制植物大战僵尸游戏内部运行实体的一套框架

## 框架将游戏内部的对象进行了封装，供监视和控制，同时提供了一系列内部的方法，以下有几个注意点

* 经过目前实测，你可以使用 **Visual Studio 2019 (v142平台工具集)** 或者 **Visual Studio 2022 (v143平台工具集)** 来编译这个框架
* 默认情况下，项目使用 **Visual Studio 2022 (v143平台工具集)**
* 框架仅能完全适用于**1.0.0.1051版本**的游戏
* 程序从pvzclass.cpp的main函数开始运行，你可以直接在里面修改，编写你的程序，也可以用如下的格式构建

```cpp
#include "pvzclass.h"

int main()
{
    DWORD pid = ProcessOpener::Open();
    if (pid) {
        PVZ::InitPVZ(pid);
        /*在这里编写你的代码*/

        PVZ::QuitPVZ();
        }
    return 0;
}
```

* **不要忘记 `PVZ::QuitPVZ()` 关闭句柄**

---

### 关于 ProcessOpener

* 这是一个只有静态成员的类
* 它提供了获取游戏**进程标识符**的函数
* 你可以通过修改它的4个静态字段来修改默认的寻找参数
* 你可以手动调用指定函数来寻找游戏
* 默认 `Open() `函数寻找的顺序是 进程名->窗口标题->文件路径
* 失败返回 0.

### 关于 PVZ 命名空间

* 必须调用 `PVZ::InitPVZ(pid)` 后（参数是**进程标识符**），才可以使用 ` PVZ` 命名空间中的属性和方法：

```cpp
PVZ::InitPVZ(pid);
PVZ::GetBoard()->Sun = 9990;//修改阳光
PVZ::GetBoard()->Win();//直接获胜
```

* 当已经调用 `PVZ::InitPVZ(pid)` 时，才可以使用PVZ类中的静态成员类，如 `Memory`

```cpp
int address = PVZ::Memory::AllocMemory();//申请内存空间
```

* 当调用 `PVZ::QuitPVZ()` 后，PVZ类中的静态成员类也无法使用。

* `PVZ::GetBoard()` 是否返回空指针可以用于判断游戏当前是否在关卡内（空指针表示不在），**绝大多数功能必须在关卡内部才可以使用**。

### 关于 Memory 类

* 这是一个只有静态成员的类
* 是命名空间 `PVZ` 下的类
* 它提供了对游戏内存的以下功能：

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

* 静态字段 `mainwindowhandle` 是游戏的窗口句柄

### 关于 SPT 宏

- 是 `PVZ.h` 中的宏，对应 `std::shared_ptr`
- 可以用于各种需要指针的场景
- `MKS` 宏对应 `std::make_shared`，可用于构造 `SPT`

### 关于基础类

- 是命名空间 `PVZ` 下的类
- 是其他类的基类
- **不要手动构造它们中的任何一个**
- 以下类属于基础类：

1. BaseClass
2. Widget
3. GameObject

### 关于 PVZutil 类

- 是命名空间 `PVZ` 下的类
- 可以获取 pvzclass 的版本和游戏版本
- 需要实例化以使用其功能

### 关于 Animation 类

* 是命名空间 `PVZ` 下的类
* 它的对象代表了游戏中的一个动画实体
* 它有2个静态方法

> UnLock(int animprop)用于解锁属性，如不解锁，这些属性将是只读的

```cpp
//AP_开头的宏表示动画属性，可以用"|"隔开
PVZ::Animation::UnLock(AP_PLANTCOLOR | AP_ZOMBIECOLOR);
```

> Lock()用于重新锁定被解锁的属性

* 可以通过其他对象的 `GetAnimation()` 方法取得对应的动画对象
* 可以手动获取整个游戏中的第 n 个对象

```cpp
SPT<PVZ::Animation> anim = MKS<PVZ::Animation>(0);//获得第1个对象
```

### 关于唯一指定的类

* 是命名空间 `PVZ` 下的类
* 需要用 `PVZ::GetXXX` 的方式获得，**不要手动new**
  * 部分 `GetXXX` 是 `Board` 类的成员函数，需要先 `GetBoard()`  后才能获取

* 以下类属于唯一指定的，通常起控制作用：

1. PVZApp
1. Board
1. SeedChooserScreen
1. Lawn
2. Icetrace
3. Wave（需要参数指定是当前关卡的第几波）
4. Mouse
5. MousePointer
6. Caption
6. CardSlot
7. Miscellaneous
8. SaveData
9. Music
10. PlantDefinition（需要参数指定是哪种植物）
11. ZombieDefinition（需要参数指定是哪种僵尸）
11. ProjectileDefinition（需要参数指定是哪种子弹）
11. ChallengeDefinition（需要参数指定是哪一个模式）

### 关于游戏内的对象实体类

* 是命名空间 `PVZ` 下的类
* 需要手动获取整个游戏中的第 n 个对象，方法同 `Animation` 类
* 部分类可以用 `PVZ::GetBoard()->GetAllXXX` 的方式一次获得当前全部可用的对象

```cpp
std::vector<SPT<PVZ::Zombie>> zombies = PVZ::GetBoard()->GetAllZombies();
```

* 以下类属于游戏内的对象实体类：

1. Zombie
2. Projectile
3. Plant
4. Coin
5. Lawnmover
6. Griditem（Grave, Crater, AquariumBrain, Snail, Vase, IZBrain, Portal 类的基类）
6. Attachment
6. TrackInstance

### 关于 SeedCard 类

* 是 `CardSlot` 类的成员类
* 需要用上一级类的对象的 `->GetXXX` 的方式获得
* 可以手动获取整个游戏中的第 n 个对象，方法同 Animation 类

### 关于 GardenPlant 类

- 一个单独的类，SaveData 类和 Coin 类都有实现它的成员（或成员函数）
- 需要用上一级类的对象的 `->GetXXX` 的方式获得
- **不要手动构造它**

### 关于枚举类型

* 每一种枚举类型都在其各自的名称空间里
* 几乎每一种枚举类型的名称空间里都有 `ToString`  方法，可以将枚举类型转化为字符串

### 关于 Extensions.h

* 默认在 `pvzclass.h` 中被包含
* 不是必须的
* 提供了几个常用的修改功能
* 参数是代表开启还是关闭功能

### 关于 Creator

* `Creator` 是一个名称空间
* 声明和定义默认在 `pvzclass.h` 中被包含
* 提供了在游戏中创建实体的函数
* **`AsmInit` 函数是部分方法的初始化函数**，只需要调用一次
  * 程序结束时，若调用过 `AsmInit`，请务必再调用一次 `AsmReset`

* 以下函数需要必须要初始化才能使用：

1. 重载函数 `CreateProjectile(ProjectileType::ProjectileType,int,int,float,float)`
2. `__CreatePortal`
3. `CreatePortal`

* `FrozeAll` 函数需要在关卡出现过植物的情况下才有效果

### 关于 Const

- `Cosnt` 是一个名称空间
- 提供了查询、修改部分常量的函数
- 默认**不在** `pvzclass.h` 中被包含，请手动 `#include`

### 关于 Events

- 全面更新过的事件组件
- 详情请查阅[这篇文档](./pvzclass/Events/Events说明.md)。

## 怎么用？

pvzclass.cpp。
