# HookEvents 说明

之前的事件实现方式可能会出现事件的漏判，为了解决这一问题，我使用 hook 的方式来进行事件的判定。

这种实现方式经过排山倒海小游戏的测试，性能消耗不大，且不会出现误判；此外合适的 hook 位置可以提供先前的事件系统无法做到的功能。

## 使用说明

请参照同一个 commit 中的 pvzclass.cpp 文件。

首先，编写一个 listener 函数，返回类型与参数类型需要与事件类中的模板类型对应。例如：

```cpp
class ZombieHitEvent : public BaseEvent<std::function<
    int(std::shared_ptr<PVZ::Zombie>, DamageType::DamageType, int)>>
```

代表 listener 的返回类型为 `int`，参数类型依次为 `std::shared_ptr<PVZ::Zombie>` `DamageType::DamageType` `int`。那么我们就可以编写这样一个 listener：

```cpp
int listener(shared_ptr<PVZ::Zombie> zombie, DamageType::DamageType type, int amount)
{
    cout << ZombieType::ToString(zombie->Type) << " 受到了 " << amount << " 点伤害，类型为 " << DamageType::ToString(type) << endl;
    return amount;
}
```

返回值可以用来修改僵尸受到的伤害，不同事件可能会有各自独特的 listener 类型，具体还请参照各个事件类的说明。

然后，就可以用以下方式使用事件了：

```cpp
    ZombieHitEvent e;
    e.start();
    e.addListener(listener);
    e.addListener(listener);
    e.removeListener(1);
    while (true)
    {
        e.run();
    }
    e.end();
```

说明几个注意点：

1. 调用 start 之后，PVZ 便会在触发事件时被阻塞，直到事件被 run 处理，请确保 run 的调用足够频繁，且 start 与 run 之间不会有相关事件被触发。

2. removeListener 是移除对应位置的 listener，且之后 listener 的位置会变动，请留意。

3. listener 会按照添加的先后顺序触发，请确保它们之间的正常运行逻辑。

## 开发说明

请参照同一个 commit 中的 ZombieHitEvent 相关文件。

首先，确认 listener 的返回类型与参数类型，然后继承 BaseEvent 基类。

之后，实现以下三个方法：

1. start 在启用事件时调用，将相关的 PVZ 代码段改为 hook 代码。

2. run 在监听事件时调用，将相关内存数据转换为对象，并调用各个 listener。

3. end 在停用事件时调用，复原相关的 PVZ 代码，以避免过多的资源消耗以及阻塞。

## 开发计划

第一批开发的事件是 pvzclass 中使用了 Memory::Execute 的事件，列举如下：

- [ ] CoinCreateEvent

- [ ] CoinCollectEvent

- [ ] GriditemCreateEvent

- [ ] GriditemRemoveEvent

- [ ] MouseClickEvent

- [x] PlantShootEvent

- [ ] PlantCreateEvent

- [ ] PlantRemoveEvent

- [ ] ProjectileOnFireEvent

- [ ] ProjectileCreateEvent

- [ ] ProjectileRemoveEvent

- [x] ZombieHitEvent

- [ ] ZombieBlastEvent

- [ ] ZombieButterEvent

- [ ] ZombieDecelerateEvent

- [ ] ZombieFrozeEvent

- [ ] ZombieHyponotizeEvent

- [ ] ZombieCreateEvent

- [ ] ZombieRemoveEvent

- [ ] GraveCreateEvent

- [ ] CraterCreateEvent

- [ ] LadderCreateEvent
