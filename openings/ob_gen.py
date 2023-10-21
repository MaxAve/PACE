'''
This script is used for parsing PGN files and generating opening books.
To create or update opening books simply add (unedited!) PGN files into the gm_games directory,
add the new PGN files to the list below (pgn_games_to_parse), and run the script.
The new opening book will be written to white.txt and black.txt (white.txt will contain openings
which resulted in a win for white, and black.txt contains games where black won).
You can also control how many moves an opening should last by changing max_game_len, which controls
at which point to truncate a game to only include the opening phase
'''

import chess
import os

'''
Opening book generation parameters
'''
# PGN game files which will be added to the opening book (white.txt/black.txt)
pgn_games_to_parse = ['Nakamura.pgn', 'Carlsen.pgn', 'Eljanov.pgn']

# Longest opening (longer games will be truncated)
max_game_len = 10


class PGN_str:
    def __init__(self, moves, result):
        self.moves = moves
        self.result = result

class PGN_simplified:
    def __init__(self):
        self.moves = []
        self.result = 0

def parse_pgn(pgn: str):
    pgns = PGN_simplified()

    # Remove move numbers
    game_str = pgn[0:len(pgn)-5].replace('\n', ' ')
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
    counter = 0
    for i in range(len(shortened_game_str)):
        if shortened_game_str[i] == ' ':
            if counter > max_game_len:
                break
            pgns.moves.append(tmp_dat)
            tmp_dat = ''
            counter += 1
            continue
        tmp_dat += shortened_game_str[i]
    
    return pgns

def generate_uci_moves(pgn_data: PGN_simplified):
    board = chess.Board()
    uci_data = ''
    for move in pgn_data.moves:
        uci_move = board.push_san(move).uci()
        uci_data += (uci_move + ';')
    return uci_data


if __name__ == '__main__':
    # Clear previous opening book data
    print('Clearing old data...')
    open(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'white.txt'), 'w').close()
    open(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'black.txt'), 'w').close()
    
    uci_games_white = []
    uci_games_black = []
    
    for file_path in pgn_games_to_parse:
        with open(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'gm_games', file_path), 'r') as file:
            print('Parsing ' + file_path + '...')
            file_data = file.read()
            game_data = ''
            is_tag = False
            # Parse pgn file
            for i in range(len(file_data)):
                # Filter for game data tags
                if not is_tag and file_data[i] == '[':
                    is_tag = True
                if is_tag and file_data[i-1] == ']':
                    is_tag = False
                if not is_tag:
                    game_data += file_data[i]
            
            game_data = game_data.replace('\n\n\n\n\n\n\n\n\n\n\n\n\n', '')       
            game_data = game_data.replace('\n', ' ')
            game_data = game_data.replace('  ', ' ')
            
            # Parse individual strings
            games = []
            tmp_game_string = ''
            for i in range(len(game_data)):
                tmp_game_string += game_data[i]
                if tmp_game_string[len(tmp_game_string)-3:len(tmp_game_string)] == '1-0' or tmp_game_string[len(tmp_game_string)-3:len(tmp_game_string)] == '0-1' or tmp_game_string[len(tmp_game_string)-7:len(tmp_game_string)] == '1/2-1/2':
                    result = 0
                    if tmp_game_string[len(tmp_game_string)-3:len(tmp_game_string)] == '1-0':
                        result = 1
                    if tmp_game_string[len(tmp_game_string)-3:len(tmp_game_string)] == '0-1':
                        result = -1
                    games.append(PGN_str(tmp_game_string, result))
                    tmp_game_string = ''
            
            print('Converting to UCI...')
            for i in range(len(games)):
                game = parse_pgn(games[i].moves)
                game.result = games[i].result
                del game.moves[0]
                try:
                    if game.result > 0:
                        uci_games_white.append(generate_uci_moves(game))
                    elif game.result < 0:
                        uci_games_black.append(generate_uci_moves(game))
                    # Print progress whenever 500 games have been read
                    if (i % 500) == 0:
                        print(str(int(i / len(games) * 100)) + '%')
                except:
                    pass
    
    # Dictionaries used to quickly check for duplicate openings
    white_games = dict()
    black_games = dict()
    
    # Write games to white.txt
    with open(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'white.txt'), 'w') as file:
        print('Writing games to white.txt...')
        for game in uci_games_white:
            exists = True
            try:
                white_games[game] # Check if this opening already exists
            except:
                exists = False # Opening does not yet exist
            if not exists:
                file.write(game + '\n')
                white_games[game] = 1 # Remember this opening
            
    # Write games to black.txt
    with open(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'black.txt'), 'w') as file:
        print('Writing games to black.txt...')
        for game in uci_games_black:
            exists = True
            try:
                black_games[game] # Check if this opening already exists
            except:
                exists = False # Opening does not yet exist
            if not exists:
                file.write(game + '\n')
                black_games[game] = 1 # Remember this opening
