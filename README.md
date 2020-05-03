# UniversalDialogQtBinding
Qt Binding for UniversalDialog.

How to build:

- Install qt, cmake and ninja.

On Arch Linux, do

``` shell
sudo pacman -Syu qt cmake ninja
```

On Ubuntu, do

``` shell
sudo apt install ninja-build cmake qtbase5-dev
```

On macOS, which it is **not recommended**, do

``` shell
brew install qt cmake ninja
```

And you should also add qt to the PATH while homebrew **does not** add qt to path.

```shell
export PATH="/usr/local/opt/qt/bin:$PATH"
```

- Execute the auto build script

``` shell 
./scripts/build.sh
```
