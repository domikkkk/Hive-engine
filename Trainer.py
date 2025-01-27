import subprocess
import json
import sys
import random

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
    def __init__(self, engine1, engine2, move_limit = 35):
        if engine1 != "rand":
            self.engine1 = HiveEngine("./" + engine1)
            print(self.engine1.get_response())
        else:
            self.engine1 = "rand"
            print(engine1)
        if engine2 != "rand":
            self.engine2 = HiveEngine("./" + engine2)
            print(self.engine2.get_response())
        else:
            self.engine2 = "rand"
            print(engine2)
        self.move_limit = move_limit
        
    def play_game(self, par1, par2, time=False):
        print('#######')
        print(self.engine1.send_command('newgame'))
        print(self.engine2.send_command('newgame'))
        for move_number in range(self.move_limit):  # Maksymalna liczba ruchów
            print(f"#{move_number + 1}", end=' ')

            best_move = self.engine1.send_command(f'bestmove {"time" if time else "depth"} {par1}')
    
            self.engine1.send_command(f"play {best_move}")
            string = self.engine2.send_command(f"play {best_move}")
            print(f"{best_move}", end=' ')
            state = get_state(string)
            if state != 'InProgress':
                break

            best_move2 = self.engine2.send_command(f'bestmove {"time" if time else "depth"} {par2}')

            self.engine1.send_command(f"play {best_move2}")
            string = self.engine2.send_command(f"play {best_move2}")
            state = get_state(string) 
            if state != 'InProgress':
                break
            print(f"{best_move2}")
        return state

    def play_with_naive(self, par, time=False):
        engine = self.engine1 if self.engine1 != "rand" else self.engine2
        engine_not_start = 0 if self.engine1 != "rand" else 1
        print('#######')
        print(engine.send_command("newgame"))
        if engine_not_start:
            validmoves = engine.send_command('validmoves')
            best_move = random.choice(validmoves.split(';'))
            engine.send_command(f'play {best_move}')
            print(f"{best_move}", end=' ')

        for move_number in range(engine_not_start, self.move_limit):
            best_move = engine.send_command(f'bestmove {"time" if time else "depth"} {par}')
            string = engine.send_command(f'play {best_move}')
            end = '\n' if engine_not_start else ' '
            print(f"{best_move}", end=end)
            
            state = get_state(string)
            if state != 'InProgress':
                break
            
            validmoves = engine.send_command('validmoves')
            best_move = random.choice(validmoves.split(';'))
            string = engine.send_command(f'play {best_move}')
            end = ' ' if engine_not_start else '\n'
            print(f"{best_move}", end=end)
            
            state = get_state(string)
            if state != 'InProgress':
                break
        return state
        

    def close(self):
        self.engine1.close()
        self.engine2.close()


def tournament(engine1, engine2):
    times = ['00:00:05', '00:00:10', '00:01:00', '00:05:00']
    stats = [["" for _ in range(len(times))] for _ in range(len(times))]
    for i, time1 in enumerate(times):
        for j, time2 in enumerate(times):
            a = Analyse(engine1, engine2)
            state = a.play_game(time1, time2, True)
            a.close()
            stats[i][j] = state
            with open(f"{engine1}_vs_{engine2}_time.json", 'w') as f:
                json.dump(stats, f, indent=4)


def naive_tournament(engine1, engine2):
    times = ['00:00:05', '00:00:10', '00:01:00', '00:05:00']
    stats = ["" for _ in range(len(times))]
    for i, time in enumerate(times):
        a = Analyse(engine1, engine2)
        state = a.play_with_naive(time, True)
        stats[i] = state
        with open(f"{engine1}_vs_{engine2}_time.json", 'w') as f:
            json.dump(stats, f, indent=4)


# tournament(*sys.argv[1:])

a = Analyse(*sys.argv[1:])
a.play_game('00:00:05', '00:00:05', time=True)
