# CupMan - Coff3e Unamed Project Manager

This is a simple project to management of project folders, it can to list the categories, projects or the files inside the projects and easyly to change for the project directory.

## Getting Started

Before anything, this project stil cant run on Windows, and you will need to create some directories for to begin.

```
$HOME/
	Create/                    // Root folder, must be on $HOME/Create
		Projects/                // Category, must exist at least one
			HelloWorld/            // Project
				hello.c
				readme.md
		Tests/                   // Another Category
			Test_Hello/            // Another Project
				test.py
```

Compile the cup with:

```shell
$ make 
```

> Move the `cup` binary to path (`/usr/bin` as example).

Then, you can try it:

```shell
$ cup -l

  Projects 
    HelloWorld

  Tests 
    Test_Hello
```

```shell
$ cup -L
  Projects
  Tests
```

```shell
$ cup -l proj
  HelloWorld
```

```shell
$ cup -l proj hello
  README.md
  hello.c
```

```shell
$ cup -l hello
  README.md
  hello.c
```

```shell
$ mkdir $(cup -s hello)/dir
$ touch $(cup -s hello)/dir/joao.txt
$ cup -l hello/dir
  joao.txt
```

```shell
$ cup -s proj
/home/<user>/Create/Projects
```

```shell
$ cup -s hello
/home/<user>/Create/Projects/hello
```

```shell
$ mkdir $(cup -s proj hello)/app && touch `cup -s proj hello`/app/joao.txt
$ cup -l proj hello/app
  joao.txt
```

```shell
$ cd `cup -s proj` # Or "cup proj", becouse "-s" is the default option
$ pwd
~/Create/Projects
```

For more informations try a `cup -h`
