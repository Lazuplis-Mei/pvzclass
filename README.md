# 警告：本仓库的 pvzclass 将不再更新！！！

Lazuplis-Mei 于上个月删除了位于 gitee 的 SuperPVZTrainner 代码仓库。

谁也不知道本仓库会否成为下一个受害者。

为了预防本仓库被删除的潜在风险，后续的更新将在[下游仓库](https://github.com/pvzclasses/pvzclass)进行。

若无其他特殊事件发生，本仓库将**不再更新**。

# pvzclass 是一个用于控制植物大战僵尸游戏内部运行实体的一套框架

## 框架将游戏内部的对象进行了封装，供监视和控制，同时提供了一系列内部的方法，以下有几个注意点

* 经过目前实测，你可以使用 **Visual Studio 2019 (v142平台工具集)** 或者 **Visual Studio 2022 (v143平台工具集)** 来编译这个框架
* 默认情况下，项目使用 **Visual Studio 2022 (v143平台工具集)**
* 建议使用 **x86 Release** 方式构建框架
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