## Installation

### Source
Install xcode command line tools
```bash
xcode-select --install
```
Now playing cli (MUST BE FROM SOURCE)
```bash
git clone https://github.com/kirtan-shah/nowplaying-cli.git && cd nowplaying-cli
make && sudo mv nowplaying-cli /usr/local/bin/nowplaying-cli
cd .. && rm -rf nowplaying-cli
```
Clone this repository
```bash
git clone https://github.com/penguinify/mystique.git && cd mystique
```
Build CMakelists
```bash
cmake .
```
Build the project
```bash
cmake --build .
```
Move the binary to /usr/local/bin
```bash
sudo mv mystique /usr/local/bin/mystique
```

