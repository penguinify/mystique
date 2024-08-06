import pandas as pd
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.naive_bayes import MultinomialNB
from sklearn.pipeline import Pipeline
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
X = data['song'] + ' ; ' + data['author']
y = data['label']

# Split the data
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42, stratify=y)

# Create a pipeline
pipeline = Pipeline([
    ('tfidf', TfidfVectorizer()),
    ('nb', MultinomialNB())
])

# Hyperparameter tuning using GridSearchCV
param_grid = {
    'tfidf__ngram_range': [(1, 1), (1, 2)],
    'tfidf__max_df': [0.75, 1.0],
    'tfidf__min_df': [1, 2],
    'nb__alpha': [0.1, 1.0, 10.0]
}

grid_search = GridSearchCV(pipeline, param_grid, cv=5, scoring='accuracy', n_jobs=-1)
grid_search.fit(X_train, y_train)

# Best model
best_model = grid_search.best_estimator_

# Save the model
joblib.dump(best_model, './src/ml/models/model.pkl')
print("Model saved to './src/ml/models/model.pkl'")

# Evaluate the model
y_pred = best_model.predict(X_test)
print(f'Accuracy: {accuracy_score(y_test, y_pred)}')
print(classification_report(y_test, y_pred, zero_division=0))

# Display best parameters
print("Best parameters found: ", grid_search.best_params_)
