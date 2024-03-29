# RunAsInvoker

运行程序时绕过用户账户控制（UAC）提示，让某个程序默认以普通用户权限运行，而不会弹出 UAC 提示框。

## 使用方法

一般来说，我们可以在控制台中用如下方式运行程序

`.\RunAsInvoker.exe "<path_to_executable>" [arguments...]`

或者创建一个`RunAsInvoker`的快捷方式到桌面，然后将想要运行的**可执行文件**（注意不是快捷方式）拖拽到桌面的快捷方式上。

对于临时使用来说，这个方案已经足够，但是对于需要反复运行的程序（比如 `wegame`），我们还有更好的方案：

- 将 `RunAsInvoker.exe` 放置在合适的位置，比如 `D:\RunAsInvoker.exe` 
- 找到想要以普通用户权限运行的程序的桌面快捷方式，右键 - 属性，在目标栏，路径的前方填入 `"D:\RunAsInvoker.exe" `（注意英文双引号和空格），然后更改图标为原来程序的图标，点击确定即可。例如 `"D:\Program Files\RunAsInvoker.exe " "D:\Some Game\Run.exe"`

## 局限性

此方案只能让当前可执行文件以普通用户权限运行，如果可执行文件必须需要权限提升，此方案并不会给出一个“虚假的权限”，所以可执行文件会失败。

此方案对于那种运行时会解压文件到临时目录，然后再从临时目录中运行的程序无效。

如果调用 RunAsInvoker 时已经提权，则运行的程序也会拥有更高的权限（比如在管理员运行的 cmd 内执行），参考[这个文章](https://devblogs.microsoft.com/oldnewthing/20161117-00/?p=94735)
