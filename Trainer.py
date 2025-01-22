import subprocess
import json
import sys

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
    def __init__(self, engine1_path, engine2_path, move_limit = 35):
        self.engine1 = HiveEngine(engine1_path)
        self.engine2 = HiveEngine(engine2_path)
        self.move_limit = move_limit
        self.stats = [["" for _ in range(3)] for _ in range(3)]
        print(self.engine1.get_response())
        print(self.engine2.get_response())
        
    def play_game(self, par1, par2, time=False):
        print('#######')
        print(self.engine1.send_command('newgame'))
        print(self.engine2.send_command('newgame'))
        for move_number in range(self.move_limit):  # Maksymalna liczba ruchów
            print(f"#{move_number + 1}", end=' ')

            best_move = self.engine1.send_command(f"bestmove {"time" if time else "depth"} {par1}")
    
            self.engine1.send_command(f"play {best_move}")
            string = self.engine2.send_command(f"play {best_move}")
            print(f"{best_move}", end=' ')
            state = get_state(string)
            if state != 'InProgress':
                break

            best_move2 = self.engine2.send_command(f"bestmove {"time" if time else "depth"} {par2}")

            self.engine1.send_command(f"play {best_move2}")
            string = self.engine2.send_command(f"play {best_move2}")
            state = get_state(string) 
            if state != 'InProgress':
                break
            print(f"{best_move2}")
        return state

    def tournament(self):
        for depth1 in range(4, 7):
            for depth2 in range(4, 7):
                state = self.play_game(depth1, depth2, False)
                self.stats[depth1-4][depth2-4] = state
                with open("v1_vs_v2.json", 'w') as f:
                    json.dump(self.stats, f, indent=4)
        self.engine1.close()
        self.engine2.close()

engine1_path = "./" + sys.argv[1]
engine2_path = "./" + sys.argv[2]

a = Analyse(engine1_path, engine2_path)

a.tournament()
