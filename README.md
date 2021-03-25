# 自用cpptools
记录一些自己写的库。

### defer
延迟函数，将指定指令延迟到该代码块结束的时候执行。
类似于Golang的defer。
```c++
{
    defer(cout << 1 << endl);
    cout << 2 << endl;
}
```
