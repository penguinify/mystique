import subprocess
import time

if __name__ == '__main__':
    while True:
        # runs system command and gets the output
        title = subprocess.check_output(['nowplaying-cli', 'get', 'title'])
        artist = subprocess.check_output(['nowplaying-cli', 'get', 'artist'])

        # decode the byte string to string
        title = title.decode('utf-8')
        artist = artist.decode('utf-8')
        # remove newline character
        title = title.strip()
        artist = artist.strip()

        print(f"Song or Advertisement: \n{title} by {artist}")
        videotype = input("1 for song, 2 for advertisement:")

        if videotype == '1':
            with open('./src/ml/trainingdata/song.csv', 'a') as f:
                f.write(f"{title};{artist}\n")
        else:
            with open('src/ml/trainingdata/advertisement.csv', 'a') as f:
                f.write(f"{title};{artist}\n")

        subprocess.run(['nowplaying-cli', 'seek', '19999'])

        time.sleep(1)
