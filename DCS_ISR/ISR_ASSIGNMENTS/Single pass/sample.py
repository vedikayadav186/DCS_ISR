# single_pass_clustering.py

from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.metrics.pairwise import cosine_similarity
import os

def single_pass_clustering(files, documents, threshold=0.2):
    vectorizer = TfidfVectorizer(stop_words='english')
    tfidf_matrix = vectorizer.fit_transform(documents)
    clusters = []
    cluster_centers = []

    for i, doc_vector in enumerate(tfidf_matrix):
        assigned = False
        for j, center_vector in enumerate(cluster_centers):
            similarity = cosine_similarity(doc_vector, center_vector)[0][0]
            if similarity >= threshold:
                clusters[j].append(files[i])
                cluster_centers[j] = (center_vector + doc_vector) / 2
                assigned = True
                break
        if not assigned:
            clusters.append([files[i]])
            cluster_centers.append(doc_vector)
    return clusters

# === MAIN ===
if __name__ == "__main__":
    folder_path = r"C:\Users\vedik\OneDrive\Desktop\deletemogo\clustered_files"

    files = [f"file{i}.txt" for i in range(1, 6)]
    documents = []

    for f in files:
        with open(os.path.join(folder_path, f), "r", encoding="utf-8") as file:
            documents.append(file.read())

    clusters = single_pass_clustering(files, documents, threshold=0.15)

    print("\nFinal Clusters:")
    for idx, cluster in enumerate(clusters, start=1):
        print(f"Cluster {idx}: {cluster}")

