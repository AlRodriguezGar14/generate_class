# Class Generator

## Description
This is a simple generator that build the .hpp and .cpp files for a Canonical Orthodox class, also known as Coplien's form.
The generated class follows the requirements for the 42 Network-associated schools' norm.

## Usage
```bash
generate_class <ClassName> "type var"...
```

## Example
```bash
generate_class AwesomeClass "int awesomeInt" "std::string awesomeString"
```

## Installation

[Download the installation script](https://raw.githubusercontent.com/AlRodriguezGar14/generate_class/main/class_gen_installer.sh) and run it, or follow the next steps:
```bash
curl -sSL https://raw.githubusercontent.com/AlRodriguezGar14/generate_class/main/class_gen_installer.sh | bash
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
export PATH=$PATH:$(pwd)/generate_class
```
4.1 Optionally you can move the executable to /usr/local/bin:

5. Clean the object files:
```bash
make clean
```


## License
[MIT](https://choosealicense.com/licenses/mit/)
