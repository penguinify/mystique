<div align="center" >

<img src="https://penguinify.github.io/mystique/mystique.png" width="60%">

# music daemon for macos
[FAQ](#faq)
[Installation](#installation)
</div>

<br><br><br>
## FAQ
What is this?
- mystique is many things for sound on macos. some planned features include:
  * Auto skip advertisements using ml (Implemented)
  * Discord Rich Presence for Videos
  * Prevent iTunes from automatically opening when the pause/play button is pressed
## Installation

### Homebrew
Install my tap
```base
brew tap penguinify/homebrew-penguinify
```
Install mystique (arm64 only at the moment)
```bash
brew install mystique-arm64
```

### Source

## INSTALL FROM SOURCE IS CURRENTLY NOT WORKING. PLEASE USE HOMEBREW TO INSTALL <3

Install xcode command line tools
```bash
xcode-select --install
```
Install python throught their website or through brew
```bash
brew install python
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
Install python dependencies
```bash
pip3 install joblib
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

