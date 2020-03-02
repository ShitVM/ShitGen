# ShitGen
ShitVM 바이트 파일 생성기

## 컴파일
```
$ git clone https://github.com/ShitVM/ShitGen.git
$ cd ShitGen
$ cmake CMakeLists.txt
$ make
```

## 예제
### 피보나치
```cpp
#include <sgn/ByteFile.hpp>
#include <sgn/Builder.hpp>

using namespace sgn;

int main() {
	ByteFile file;

	const auto fiboFunc = file.AddFunction(1, true);
	Builder fb(file, fiboFunc);

	const auto int2 = file.AddIntConstantFast(2);
	const auto int1 = file.AddIntConstantFast(1);

	fb.Load(fb.GetArgument(0));
	fb.Push(int2);
	fb.Cmp();
	fb.Jae(fb.ReserveLabel("calc"));
	fb.Pop();
	fb.Load(fb.GetArgument(0));
	fb.Ret();
	fb.AddLabel("calc");
	fb.Load(fb.GetArgument(0));
	fb.Push(int1);
	fb.Sub();
	fb.Call(fiboFunc);
	fb.Load(fb.GetArgument(0));
	fb.Push(int2);
	fb.Sub();
	fb.Call(fiboFunc);
	fb.Add();
	fb.Ret();

	Builder eb(file, file.GetEntryPoint());

	const auto int35 = file.AddIntConstantFast(35);

	eb.Push(int35);
	eb.Call(fiboFunc);

	file.Save("./test.sbf");
}
```