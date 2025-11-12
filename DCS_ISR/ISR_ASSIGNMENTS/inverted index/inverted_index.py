import os
import string

def build_inverted_index(folder_path):
    index = {}
    files = [f for f in os.listdir(folder_path) if f.endswith('.txt')]

    for f in files:
        with open(os.path.join(folder_path, f), 'r', encoding='utf-8') as file:
            text = file.read().lower()
            text = text.translate(str.maketrans('', '', string.punctuation))
            words = set(text.split())  # unique words

            for word in words:
                index.setdefault(word, []).append(f)

    return index

def search(index, word):
    return index.get(word.lower(), [])

if __name__ == "__main__":
    folder = r"C:\Users\vedik\OneDrive\Desktop\deletemogo\clustered_files"

    print("Building Inverted Index...\n")
    index = build_inverted_index(folder)
    print("Inverted index ready!\n")

    while True:
        q = input("Search word (or 'exit'): ").strip()
        if q.lower() == "exit":
            print("Goodbye!")
            break

        result = search(index, q)
        print(f"Found in: {result}\n" if result else "Not found.\n")
