from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/operation', methods=['GET'])
def perform_operation():
    number = request.args.get('number', type=int)
    operation = request.args.get('operation', default='square', type=str)

    if number is None:
        return jsonify({'error': 'Please provide a number parameter!'}), 400

    # Perform the selected operation
    if operation == 'square':
        result = number ** 2
    elif operation == 'cube':
        result = number ** 3
    elif operation == 'double':
        result = number * 2
    else:
        return jsonify({'error': 'Invalid operation! Use square, cube, or double.'}), 400

    return jsonify({
        'number': number,
        'operation': operation,
        'result': result
    })

if __name__ == '__main__':
    print("🚀 Server running on http://127.0.0.1:5000")
    app.run(host='0.0.0.0', port=5000)
