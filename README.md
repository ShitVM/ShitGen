# ShitGen
ShitVM 바이트 파일 생성기

## 컴파일
```
$ git clone https://github.com/ShitVM/ShitGen.git --recurse-submodules
$ cd ShitGen
$ cmake .
$ cmake --build .
```

## 예제
### 피보나치
```cpp
#include <sgn/ByteFile.hpp>
#include <sgn/Builder.hpp>
#include <sgn/Generator.hpp>

using namespace sgn;

int main() {
	ByteFile file;

	FunctionIndex fiboFunc = file.AddFunction(1, true);
	Builder fiboBuilder(file, fiboFunc);

	IntConstantIndex int1 = file.AddIntConstantFast(1);
	IntConstantIndex int2 = file.AddIntConstantFast(2);

	fiboBuilder.Load(fiboBuilder.GetArgument(0));
	fiboBuilder.Push(int2);
	fiboBuilder.Cmp();
	fiboBuilder.Jae(fiboBuilder.ReserveLabel("calc"));
	fiboBuilder.Pop();
	fiboBuilder.Load(fiboBuilder.GetArgument(0));
	fiboBuilder.Ret();
	fiboBuilder.AddLabel("calc");
	fiboBuilder.Load(fiboBuilder.GetArgument(0));
	fiboBuilder.Push(int1);
	fiboBuilder.Sub();
	fiboBuilder.Call(fiboFunc);
	fiboBuilder.Load(fiboBuilder.GetArgument(0));
	fiboBuilder.Push(int2);
	fiboBuilder.Sub();
	fiboBuilder.Call(fiboFunc);
	fiboBuilder.Add();
	fiboBuilder.Ret();

	Builder entryBuilder(file, file.GetEntrypoint());

	IntConstantIndex int35 = file.AddIntConstantFast(35);

	entryBuilder.Push(int35);
	entryBuilder.Call(fiboFunc);

	Generator gen(file);
	gen.Generate("Fibonacci.sbf");
}
```