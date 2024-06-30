# Calc

Calc is a simple tool that evaluates mathematical expressions and outputs the result to the standard output.

## Installation

### Compile the Binary
To compile the binary, run the following command in the terminal. This will create a binary file named `calc` in the current directory:

```sh
make
```

### Install the Binary
Move the binary to a desired location, or install it system-wide using the following command:

```sh
sudo make install
```

## Usage

### Evaluate a Single Expression
To evaluate a single mathematical expression, use the following command:

```sh
$ calc '2 + 4 * 2'
10
```

### Use as a REPL
To use Calc in a REPL (Read-Eval-Print Loop) mode, run:

```sh
$ calc
Welcome to the calc REPL! Type in math expressions.
>> 2 + 4 * 2
10
>>
```

## License

Calc is licensed under the MIT License.
