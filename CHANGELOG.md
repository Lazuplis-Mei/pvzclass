# TOC	
- [1.15.1](#1.15.1（2023/11/22）)
- [1.15.0](#1.15.0（2023/10/27）)
- [1.14.3](#1.14.3（2023/10/22）)

## 1.15.1 （2023/11/22）

### 新增内容

- `ThreeState` 枚举，用于三态判断。
- `Miscellaneous` 类添加了 `SetMemSize()`，用于扩展该类。
- `Extensions.h` 添加 `EnableVaseBreak()`，可以启用砸罐子模式的部分特性。
- `Const::GetLevelScene()` 和 `Const::SetLevelScene`，用于获取/设置模式的默认关卡。
- `Flags.h`，包含 `DamageRangeFlags` 和 `DamageFlags`，用于存储状态压缩存储的量。
- `Zombie` 类添加了 `Hit()` 和 `HitDirect()` 的 `DamageFlags` 适配版。
- `Zombie` 类添加了 `EffectedBy()`，用于判定僵尸是否符合某些条件。
- `PVZApp` 类添加若干属性。

### 改动

- 平台工具集从 `v142` 更新至 `v143`。
- `Events` 组件现在支持 `x64` 构建。
- `Events` 组件的部分功能分拆到 `.cpp` 文件中。
- 使用 `Creator::CreateZombie()` 生成的僵王博士将被强制生成在 0 行 0 列。
- 更新 `README.md` 的过时内容。
- `Memory` 类现在使用新的方式实现 `Execute()`，可用 `immediateExecute` 控制是否不等待 `Board` 更新就执行指令。
- 优化 `Memory::Variable` 的注释。

### 漏洞修复

- 修复 `Const::WriteCoinValue()` 不能正确修改小阳光价值的漏洞。
- 修复 `Zombie::canDecelerate()` 无法正常判定的漏洞。

### 兼容性

- 兼容 1.15.0。
- **不兼容** 1.14.3 及以前的版本。

## 1.15.0 （2023/10/27）

### 新增内容

- `PVZApp` 类，用于处理 `PVZ_BASE` 偏移的属性。
- `PVZutil` 类，用于存放部分功能，目前只支持版本查询。
- `BaseClass` 类，作为大部分类的基类，提供只读基址和简单构造函数。

### 改动

- 将 `PVZ` 从类转换为命名空间。
  - 原本的属性均已转移到其他类的定义之下。
  - `PVZ.h` 中的四个结构体均移入 `PVZ` 命名空间内部。
  - 需要 `PVZ` 对象作为参数的函数均已更新。
- 根据 `PVZ` 命名空间的改动，更新 `README.md`。

### 漏洞修复

- 修复 `CALC_PTR_ADDR` 宏不能正确指定运算类型的漏洞。
- 修复某些情况下无法初始化 pvzclass 的漏洞。

### 兼容性

- **不兼容** 1.14.3 及以前的版本。

## 1.14.3（2023/10/22）
- 大重构前的最后一个稳定版本。