## Install Dependencies
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
