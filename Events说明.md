# DebugEvents 说明

之前的事件实现方式可能会出现事件的漏判，hook 的实现方式扩展性不是很好。

为了解决这一问题，在 shade_joker 的提醒下，我使用 debug 断点的方式来进行事件的判定。

这种实现方式经过排山倒海小游戏的测试，性能消耗不大，且不会出现误判；此外合适的断点位置可以提供先前的事件系统无法做到的功能。

## 使用说明

请参照同一个 commit 中的 pvzclass.cpp 文件。

首先，编写一个 listener 函数，返回类型与参数类型需要与事件类中的模板类型对应。例如：

```cpp
class ZombieHitEvent : public TemplateEvent<std::function<
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
    DebugEventHandler handler;
    ZombieHitEvent e;
    e.addListener(listener);
    handler.addEvent(make_shared<ZombieHitEvent>(e));
    handler.start();
    while (true)
    {
        handler.run(1)
    }
    handler.stop();
```

说明几个注意点：

1. 调用 start 之后，PVZ 便会在触发事件时被阻塞，直到事件被 handle.run 处理，请确保 run 的调用足够频繁，且 start 与 run 之间不会有相关事件被触发。

2. run 的参数是等待时间（毫秒），如果在这期间触发了事件，则返回 true。

3. 等待时间如果是 -1（INFINITY）则会阻塞住 pvzclass 直到事件触发，等待时间至少为 1ms，请根据自己的需要选择合适的等待时长。

4. listener 会按照添加的先后顺序触发，请确保它们之间的正常运行逻辑。

5. listener 中，使用 `Execute` 会导致程序卡死，请另开一个线程执行使用 `Execute` 的函数。

## 开发说明

请参照 Events 文件夹中相关文件。

首先，确认 listener 的返回类型与参数类型，然后继承 TemplateEvent 基类。

之后，实现以下两个方法：

1. 构造函数中，将 address 设定为需要中断的地址。

2. handle 中，实现事件的具体处理逻辑。
