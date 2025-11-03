import json
import flask
from flask_cors import CORS

from ui_move_generator import get_ui_move
from game_status import GameStatus
from cpp_wrapper import CppInterface

app = flask.Flask(__name__)
cors = CORS(app) # TODO fix security


current_game = GameStatus()

@app.route('/reset')
def reset():
    global current_game
    current_game = GameStatus()
    current_game.message = "Let's play!";
    return flask.jsonify(current_game)

@app.route('/player_move', methods=['POST'])
def player_move():

    global current_game
    data = flask.request.get_json()
    if not data or 'move' not in data:
        return flask.jsonify({'error': 'Missing "move" field in JSON'}), 400

    if not current_game.player1_plays:
        return flask.jsonify({'error': 'It is not your turn!'}), 400
    
    move_value = data['move']
    if not isinstance(move_value, str):
        return flask.jsonify({'error': '"move" must be a string'}), 400
    
    current_game.move_cpp = move_value;
    current_game = GameStatus.from_json(CppInterface().make_a_player_move(json.dumps(current_game.__dict__)))

    current_game.move = get_ui_move(True, current_game.move_cpp)
    if(current_game.BL_hand == 0 and current_game.BR_hand == 0):
        current_game.message = "player wins"
    else:
        current_game.message = "computer's turn";

    return flask.jsonify(current_game), 200

@app.route('/computer_move')
def computer_move():    
    global current_game

    if current_game.player1_plays:
        return flask.jsonify({'error': 'It is not the computer turn!'}), 400

    current_game = GameStatus.from_json(CppInterface().make_a_computer_move(json.dumps(current_game.__dict__)))
    current_game.move = get_ui_move(False, current_game.move_cpp)

    if(current_game.BL_hand == 0 and current_game.BR_hand == 0):
        current_game.message = "Computer wins"
    else:
        if(current_game.score == -1000):
            current_game.message = "player turn, but computer already calculated a win"
        else:
            current_game.message = "player turn"
    return flask.jsonify(current_game), 200

@app.route('/available_moves')
def available_moves():
    available_moves = CppInterface().get_available_moves(json.dumps(current_game.__dict__))
    return flask.jsonify(json.loads(available_moves)), 200



if __name__ == '__main__':
    app.run(debug=True)