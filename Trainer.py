import subprocess
import json


class HiveEngine:
    def __init__(self, engine_path):
        self.process = subprocess.Popen(
            [engine_path], 
            stdin=subprocess.PIPE, 
            stdout=subprocess.PIPE, 
            stderr=subprocess.PIPE, 
            text=True
        )
    
    def send_command(self, command):
        self.process.stdin.write(command + '\n')
        self.process.stdin.flush()
        
        return self.get_response()
    
    def get_response(self):
        response = ''
        while True:
            line = self.process.stdout.readline().strip()
            if line == "ok":
                break
            response += line
        return response
    
    def close(self):
        self.process.terminate()
        self.process.wait()


def get_state(string: str):
    par = string.split(";")
    return par[1]

class Analyse:
    def __init__(self, engine1_path, engine2_path, move_limit = 30):
        self.engine1 = HiveEngine(engine1_path)
        self.engine2 = HiveEngine(engine2_path)
        self.move_limit = move_limit
        self.stats = [["" for _ in range(6)] for _ in range(6)]
        print(self.engine1.get_response())
        print(self.engine2.get_response())
        
    def play_game(self, depth1, depth2):
        print('#######')
        print(self.engine1.send_command('newgame'))
        print(self.engine2.send_command('newgame'))
        for move_number in range(self.move_limit):  # Maksymalna liczba ruchów
            print(f"Ruch #{move_number + 1}")
            
            best_move = self.engine1.send_command(f"bestmove depth {depth1}")
            self.engine1.send_command(f"play {best_move}")
            string = self.engine2.send_command(f"play {best_move}")
            
            state = get_state(string)
            if state != 'InProgress':
                break
            
            best_move2 = self.engine2.send_command(f"bestmove depth {depth2}")
            self.engine1.send_command(f"play {best_move2}")
            string = self.engine2.send_command(f"play {best_move2}")
            
            state = get_state(string) 
            if state != 'InProgress':
                break
            print(f"{best_move}  {best_move2}")
        return state

    def tournament(self):
        for depth1 in range(3, 9):
            for depth2 in range(depth1, 9):
                state = self.play_game(depth1, depth2)
                self.stats[depth1-3][depth2-3] = state
                with open("res.json", 'w') as f:
                    json.dump(self.stats, f, indent=4)
        self.engine1.close()
        self.engine2.close()

# Ścieżki do silników
engine1_path = "./hive_engine"
engine2_path = "./hive_engine"

a = Analyse(engine1_path, engine2_path)

a.tournament()
