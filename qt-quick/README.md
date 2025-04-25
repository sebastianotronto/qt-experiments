# QT-quick implementation of a nissy UI

This is a UI for nissy written using
[QT Quick](https://doc.qt.io/qt-6/qtquick-index.html).

It has been tested only on Linux with QT 6.9.
Building requires CMake.

To build this project, first you have to initialize the `nissy-core`
submodule. From the parent directory run

```
git submodule init && git submodule update
```

This will clone the `nissy-core` repository inside the parent folder.

Then from this folder you can run

```
make
```

To run it you can use

```
./run
``

or

```
make run
```

The latter command is going to build the project (if has not already
been built) and run it with some debug options enabled.
