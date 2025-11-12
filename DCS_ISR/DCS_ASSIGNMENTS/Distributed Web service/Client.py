import requests
import threading

def request_to_server(number, operation):
    try:
        url = f"http://127.0.0.1:5000/operation?number={number}&operation={operation}"
        response = requests.get(url)
        data = response.json()

        if 'error' in data:
            print(f"❌ Error for {number}: {data['error']}")
        else:
            print(f"✅ Number: {data['number']}, Operation: {data['operation']}, Result: {data['result']}")
    except Exception as e:
        print(f"⚠️ Client error: {e}")

def main():
    count = int(input("Enter how many clients you want to simulate: "))
    threads = []

    for i in range(count):
        number = int(input(f"Enter number for client {i+1}: "))
        operation = input(f"Enter operation for client {i+1} (square/cube/double): ").strip().lower()
        t = threading.Thread(target=request_to_server, args=(number, operation))
        t.start()
        threads.append(t)

    for t in threads:
        t.join()

    print("\n✅ All clients finished processing.")

if __name__ == "__main__":
    main()
