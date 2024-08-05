import pandas as pd
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import MultinomialNB
from sklearn.pipeline import make_pipeline
from sklearn.metrics import accuracy_score, classification_report
import joblib
# Load the data
songs = pd.read_csv('./src/ml/trainingdata/song.csv', delimiter=';')
ads = pd.read_csv('./src/ml/trainingdata/advertisement.csv', delimiter=';')

# Add a label column
songs['label'] = 'song'
ads['label'] = 'advertisement'

# Combine the datasets
data = pd.concat([songs, ads], ignore_index=True)

# Replace NaN values with empty strings
data = data.fillna('')

# Prepare features and labels
X = data['song'] + ' ' + data['author']
y = data['label']

# Split the data
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Create a pipeline
model = make_pipeline(TfidfVectorizer(), MultinomialNB())

# Train the model
model.fit(X_train, y_train)

# Save the model
joblib.dump(model, './src/ml/models/model.pkl')
print("Model saved to './src/ml/models/model.pkl'")

# Evaluate the model
y_pred = model.predict(X_test)
print(f'Accuracy: {accuracy_score(y_test, y_pred)}')
print(classification_report(y_test, y_pred, zero_division=0))
