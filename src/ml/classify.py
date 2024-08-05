import joblib
import sys

model = joblib.load('./src/ml/models/model.pkl')

def classify(song, author):
    label = model.predict([song + ' ' + author])[0]
    return label

if __name__ == '__main__':
    song = sys.argv[1]
    author = sys.argv[2]
    label = classify(song, author)
    print(label)
