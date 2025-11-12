import os
from bs4 import BeautifulSoup

folder = "website"
index = {}

# Build index
for f in os.listdir(folder):
    if f.endswith(".html"):
        text = BeautifulSoup(open(os.path.join(folder, f), encoding="utf-8").read(), "html.parser").get_text().lower()
        for w in text.split():
            index.setdefault(w, set()).add(f)

# Search loop
while True:
    word = input("Search word (or 'exit'): ").lower()
    if word == "exit":
        break
    print("Found in:", ", ".join(index.get(word, [])) or "No page found")
