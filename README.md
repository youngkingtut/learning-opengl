### First time setup
Project uses
- glad
- glfw
- glm
- freetype2

Glad was produced [here](https://glad.dav1d.de/) and copied into ext/glad

The other three are pulled in using [git submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules). To set those up first run
```bash
git submodule init
```
follow by
```bash
git submodule update
```

That should pull everything into ext/

### Running
I'm using clion which seamlessly integrates with cmake, making it a one click build.

If you're using cmake on the command line, I believe you can run the following to build and compile

```bash
cmake -DCMAKE_BUILD_TYPE=Debug /path/to/folder/with/CmakeList.txt/leraning-opengl
cmake -build /path/to/cmake/build/folder
```

and then run the program

```bash
/path/to/cmake/build/folder/bin/LeraningOpenGl
```
