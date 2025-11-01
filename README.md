# RobustServerController

a sever controller written in c++, provides simple functionallity to save server information and automatically find IPv4 addresses. for people who have a bunch of servers on their LAN and their ISP configured a NAT.

# Quickstart

### building project manually
```
# clone using git
$ git clone https://github.com/RoeeWork/RobustServerController
$ cd RobustServerController

# build using cmake
$ cmake -S . -B build
$ cmake --build build
```

### adding to path

bash:
```
# add to PATH temporarily
$ export PATH="/path/to/project_root/RobustServerController/build:$PATH"

# or permanently
$ echo 'export PATH="/path/to/project_root/RobustServerController/build:$PATH"' >> ~/.bashrc
$ source ~/.bashrc
```

zsh:
```
# add to PATH temporarily
$ export PATH="/path/to/project_root/RobustServerController/build:$PATH"

# or permanently
$ echo 'export PATH="/path/to/project_root/RobustServerController/build:$PATH"' >> ~/.zshrc
$ source ~/.zshrc
```

### Usage

```
# lists chosen servers, and if they are offline/online.
$ rsc

# add servers
$ rsc -a
# or
$ rsc --addservers

# remove server
$ rsc -r <ServerName>
# or
$ rsc --removeserver <ServerName>

# start in verbose mode
$ rsc -v
# or
$ rsc --verbose

```
