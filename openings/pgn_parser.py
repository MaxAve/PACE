'''
This script is used for parsing PGN files and to generate opening books
'''

import chess
import os

class PGN_simplified:
    def __init__(self):
        self.moves = []
        self.result = 0

def parse_pgn(pgn: str):
    pgns = PGN_simplified()

    # Parse game data (date, winner, etc.)
    game_string_index = 0
    tmp_game_tag = ""
    for i in range(len(pgn)):
        tmp_game_tag += pgn[i]
        # Get winner
        if tmp_game_tag == "[Result \"1-0\"]":
            pgns.result = 1
        elif tmp_game_tag == "[Result \"0-1\"]":
            pgns.result = -1
        # Stop parsing game data when ECO tag is reached
        if tmp_game_tag == "[ECO":
            game_string_index = i + 12
            break
        if pgn[i] == '\n':
            tmp_game_tag = ""
    
    # Remove move numbers
    game_str = pgn[game_string_index:len(pgn)-5].replace('\n', ' ')
    shortened_game_str = ''
    add_char = True
    for i in range(len(game_str)):
        if game_str[i] == ' ' and game_str[i+1].isdigit():
            add_char = False
        if game_str[i-1] == '.':
            add_char = True
            shortened_game_str += ' '
        if add_char:
            shortened_game_str += game_str[i]
            
    # Convert to list and return shortened PGN object
    tmp_dat = ''
    for i in range(len(shortened_game_str)):
        if shortened_game_str[i] == ' ':
            pgns.moves.append(tmp_dat)
            tmp_dat = ''
            continue
        tmp_dat += shortened_game_str[i]
    
    return pgns

def generate_uci_moves(pgn_data):
    board = chess.Board()
    pgn = parse_pgn(pgn_data)
    
    uci_data = ''
    
    for move in pgn.moves:
        uci_move = board.push_san(move).uci()
        uci_data += (uci_move + ';')
        
    return uci_data

# Currently all this script does is parse the PGN in white_openings.txt and prints the UCI moves (seperated by semicolons)
if __name__ == '__main__':
    with open(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'white_openings.txt'), 'r') as file:
        print(generate_uci_moves(file.read()))
