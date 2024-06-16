# Class Generator

## Description

This is a simple generator that build the .hpp and .cpp files for a Canonical Orthodox class, also known as Coplien's form.
The generated class follows the requirements for the 42 Network-associated schools' norm.

## Usage

```bash
newClass <ClassName> "type var"...
```

## Example

```bash
newClass AwesomeClass "int awesomeInt" "std::string awesomeString"
```

## Installation

[Download the installation script](https://raw.githubusercontent.com/AlRodriguezGar14/newClass/main/class_gen_installer.sh) and run it, or follow the next steps:

```bash
curl -sSL https://raw.githubusercontent.com/AlRodriguezGar14/newClass/main/class_gen_installer.sh | bash
```

1. Clone the repository:

```bash
git clone https://github.com/AlRodriguezGar14/generate_class.git class_generator
```

2. Change directory to the cloned repository:

```bash
cd class_generator
```

3. Build the program:

```bash
make
```

4. Add the executable to your path (optional):

```bash
export PATH=$PATH:$(pwd)/newClass
```

4.1 Optionally you can move the executable to /usr/local/bin:

5. Clean the object files:

```bash
make clean
```

## License

[MIT](https://choosealicense.com/licenses/mit/)

## What is a Canonical Orthodox class?

The Canonical Orthodox or Orthodox Canonical Class Form in C++ is a term that refers to a class that implements certain member functions that the C++ compiler can automatically generate. These functions are essential for managing resources, especially when objects of the class are copied or destroyed. In C++98 this consists of four member functions:

- Default constructor: Constructs a new object and initializes its members.
- Copy constructor: Constructs a new object as a copy of an existing object.
- Destructor: Cleans up when an object is destroyed, such as releasing any memory that was allocated.
- Copy assignment operator: Assigns the value of an existing object to another existing object.

Manually building these functions ensures that they are implemented correctly without any unexpected behavior.
