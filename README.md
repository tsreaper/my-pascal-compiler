# My Pascal Compiler

My Pascal is a simpler and slightly modified version of the ISO7185 Pascal programming language. My Pascal Compiler is the compiler for My Pascal, with LLVM as its backend.

## Feature

* Supports most of the data types in Pascal, including multi-dimension arrays, strings and record types.
* Supports most of the operations and statements in Pascal.
* Supports most of the built-in functions and procedures of Pascal, including read, write, fillchar, etc.
* Can compile My Pascal source code to LLVM IR code, assembly, object file or executable file.

## Usage

```
mpc [-d] [-t filetype] [-o outfile] infile
```

```
-d
    Prints debug message.

-t filetype
    Specify what kind of output mpc should generate. `filetype` can be
        ll: llvm IR code
        asm: textual assembly
        obj: native object file

-o outfile
    Rename output file of mpc to `outfile`
```

## Example

Source file (example.pas):
```pascal
var
    a, b: integer;    
begin
    read(a, b);
    writeln(a + b);
end.
```

Use `mpc -d example.pas` to print the following debug message (AST) and compile source code to executable file.

```
program(
    variable_declaration(
        id_sequence_with_type(
            id(a)
            id(b)
            --- type ---
            int_type()
        )
    )
    function_call(
        id(read)
        --- param ---
        id(a)
        id(b)
    )
    function_call(
        id(writeln)
        --- param ---
        add(
            id(a)
            id(b)
        )
    )
)
```

Use `mpc -t ll example.pas` to compile source code to LLVM IR code.

```
; ModuleID = 'my_pascal_module'
source_filename = "my_pascal_module"

@a = internal global i32 zeroinitializer
@b = internal global i32 zeroinitializer
@scanf_format = private unnamed_addr constant [5 x i8] c"%d%d\00"
@printf_format = private unnamed_addr constant [4 x i8] c"%d\0A\00"

define i32 @main() {
entry:
  %a = load i32, i32* @a
  %b = load i32, i32* @b
  %call_scanf = call i32 (i8*, ...) @scanf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @scanf_format, i32 0, i32 0), i32* @a, i32* @b)
  %a1 = load i32, i32* @a
  %b2 = load i32, i32* @b
  %add_tmp = add i32 %a1, %b2
  %call_printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printf_format, i32 0, i32 0), i32 %add_tmp)
  ret i32 0
}

declare i32 @scanf(i8*, ...)

declare i32 @printf(i8*, ...)
```

Check `test/example` directory for more examples.

## Build from Source

**Now both in-source and out-of-source compilation is allowed.**

### Dependencies

* gcc >= 5.4
* cmake >= 3.10
* llvm >= 6.0

### Build My Pascal Compiler
```
cmake --build <build-dir> --target mpc
```

### Run Tests

* Run all tests
    ```
    cmake --build <build-dir> --target mpc-test
    ```
* Run normal tests
    ```
    cmake --build <build-dir> --target mpc-test-normal
    ```
* Run validation tests
    ```
    cmake --build <build-dir> --target mpc-test-validation
    ```
* Run examples
    ```
    cmake --build <build-dir> --target mpc-test-example
    ```

### Attention for MacOS Users
1. Use `homebrew` to install `llvm`.
``` shell
brew install llvm
```
2. Follow hints in `brew info llvm`, implement
``` shell
echo 'export PATH="/usr/local/opt/llvm/bin:$PATH"' >> ~/.bash_profile
```
3. Use `homebrew` to install `coreutils`
``` shell
brew install coreutils
```
Building Steps are totally same as above.

## Documentation

WIP

## Difference with Pascal

See documentation (WIP)
