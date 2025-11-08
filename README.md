```markdown
# 🐚 42 Minishell 🚀

A simplified Unix shell implementation written in C.

A project to understand the fundamentals of shell programming and system calls.

![License](https://img.shields.io/github/license/GustavonBrito/42_minishell)
![GitHub stars](https://img.shields.io/github/stars/GustavonBrito/42_minishell?style=social)
![GitHub forks](https://img.shields.io/github/forks/GustavonBrito/42_minishell?style=social)
![GitHub issues](https://img.shields.io/github/issues/GustavonBrito/42_minishell)
![GitHub pull requests](https://img.shields.io/github/issues-pr/GustavonBrito/42_minishell)
![GitHub last commit](https://img.shields.io/github/last-commit/GustavonBrito/42_minishell)

![C](https://img.shields.io/badge/C-A8B9CC?style=flat&logo=c)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=flat&logo=linux)

## 📋 Table of Contents

- [About](#about)
- [Features](#features)
- [Quick Start](#quick-start)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [Testing](#testing)
- [License](#license)
- [Support](#support)
- [Acknowledgments](#acknowledgments)

## About

The 42 Minishell project is a simplified Unix shell implementation developed as part of the 42 curriculum. It aims to provide a hands-on understanding of shell programming concepts, system calls, process management, and command parsing. This project focuses on creating a functional shell environment that can execute basic commands, manage environment variables, and handle input/output redirection.

The primary goal is to replicate essential features of a standard shell like `bash` or `zsh`, allowing users to interact with the operating system through a command-line interface. It targets students and developers interested in learning about low-level system interactions and the inner workings of a shell. The project is written in C and relies on standard Unix system calls for process creation, execution, and inter-process communication.

Key technologies include:
- C programming language
- Unix system calls (fork, execve, wait, pipe, dup2)
- Command-line parsing and execution
- Environment variable management

## ✨ Features

- 🎯 **Command Execution**: Executes standard Unix commands (e.g., `ls`, `pwd`, `echo`).
- ⚙️ **Built-in Commands**: Implements built-in commands like `cd`, `env`, `exit`, `export`, and `unset`.
- 🔄 **Redirection**: Supports input and output redirection using `<`, `>`, `>>`.
- 🧵 **Piping**: Allows chaining commands using pipes (`|`).
- 🌍 **Environment Variables**: Manages environment variables and their expansion.
- 🚦 **Signal Handling**: Handles signals such as `Ctrl+C` and `Ctrl+\`.
- ⌨️ **Interactive Mode**: Provides an interactive shell prompt for user input.

## 🚀 Quick Start

Clone and run the minishell in a few steps:

```bash
git clone https://github.com/GustavonBrito/42_minishell.git
cd 42_minishell
make
./minishell
```

## 📦 Installation

### Prerequisites
- GCC
- Make

### From Source
```bash
# Clone the repository
git clone https://github.com/GustavonBrito/42_minishell.git
cd 42_minishell

# Compile the project
make

# Run the executable
./minishell
```

## 💻 Usage

After successful installation, simply run the executable. The minishell will present a prompt where you can enter commands.

```bash
./minishell
minishell> ls -l
total 4
-rw-r--r-- 1 user user 1024 Jan  1 00:00 file.txt
minishell> echo $PATH
/usr/local/bin:/usr/bin:/bin
minishell> exit
```

### Built-in Commands
- `cd [path]`: Change the current directory.
- `env`: Print the environment variables.
- `exit [n]`: Exit the shell with status `n`.
- `export [name=value]`: Set an environment variable.
- `unset [name]`: Unset an environment variable.
- `echo [string]`: Print the string to standard output.

## 📁 Project Structure

```
42_minishell/
├── includes/            # Header files
├── srcs/                # Source files
│   ├── main.c           # Main entry point
│   ├── parsing/         # Command parsing logic
│   ├── execution/       # Command execution logic
│   ├── builtins/        # Built-in command implementations
│   └── utils/           # Utility functions
├── Makefile             # Build instructions
├── README.md            # Project documentation
└── LICENSE              # License file
```

## 🤝 Contributing

Contributions are welcome! Please follow these steps:

1.  Fork the repository.
2.  Create a new branch for your feature or bug fix.
3.  Implement your changes and test them thoroughly.
4.  Submit a pull request with a clear description of your changes.

### Quick Contribution Steps
1. 🍴 Fork the repository
2. 🌟 Create your feature branch (git checkout -b feature/AmazingFeature)
3. ✅ Commit your changes (git commit -m 'Add some AmazingFeature')
4. 📤 Push to the branch (git push origin feature/AmazingFeature)
5. 🔃 Open a Pull Request

## Testing

To test the minishell, run the following command:

```bash
# Create test scripts in tests/ directory
# Run your test scripts
# Example:
./minishell < tests/basic_test.sh
```

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

### License Summary
- ✅ Commercial use
- ✅ Modification
- ✅ Distribution
- ✅ Private use
- ❌ Liability
- ❌ Warranty

## 💬 Support

- 🐛 **Issues**: [GitHub Issues](https://github.com/GustavonBrito/42_minishell/issues)

## 🙏 Acknowledgments

- 🎓 This project is part of the 42 curriculum.
- 📚 **Libraries used**:
  - `libc` - Standard C library
- 👥 **Contributors**: Thanks to all [contributors](https://github.com/GustavonBrito/42_minishell/contributors)
```