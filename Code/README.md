### 使用方法

根据注释在对应位置按需修改即可，建议在考试之前把所有的代码都结合课堂知识改改参数跑一遍。

### 宏定义简介
以防大家忘记或者弄错，这里简单说说C/C++宏定义 `#define` 的用法

宏定义 `#define a b`，即告诉编译器，在编译的时候把 `a` 替换为 `b`，其中 `a` 必须为合法变量名，`b` 为合法表达式。

#### 例
```cpp
#include <iostream>
using namespace std;
#define N 10

int main()
{
    cout << N << endl;
}
```

等效于
```cpp
#include <iostream>
using namespace std;

int main()
{
    cout << 10 << endl;
}
```

注意，`b`除非是单一的值，不强烈建议宏定义写成 `#definde a (b)` 的形式，以免出现替换后，运算优先级混乱。