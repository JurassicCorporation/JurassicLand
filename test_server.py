from flask import Flask, request, jsonify
import sqlite3
import json
import threading

app = Flask(__name__)

DATABASE = 'my_database.db'
conn = sqlite3.connect(DATABASE, check_same_thread=False)
cursor = conn.cursor()

#전적 기록 테이블
cursor.execute('''
    CREATE TABLE IF NOT EXISTS players (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        player_name TEXT, 
        wins INTEGER DEFAULT 0,
        losses INTEGER DEFAULT 0,
        score INTEGER DEFAULT 0
    )
''')    
# 승패 기록 테이블
cursor.execute('''
    CREATE TABLE IF NOT EXISTS matches (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        winner_id INTEGER,
        loser_id INTEGER,
        FOREIGN KEY (winner_id) REFERENCES players (id),
        FOREIGN KEY (loser_id) REFERENCES players (id)
    )
''')
# 스킬 프리셋 정보 테이블
cursor.execute('''
    CREATE TABLE IF NOT EXISTS skill_presets (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        player_name TEXT,
        skills TEXT,
        settings TEXT
    )
''')
# 접속자 테이블
cursor.execute('''
    CREATE TABLE IF NOT EXISTS player_connections (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        player_name TEXT,
        timestamp DATETIME DEFAULT (DATETIME('now', 'localtime'))
    )
''')

conn.commit()


# 전적 및 스코어 업데이트 API
# client에서 보낼 json 형식 :{"winner_name":"a","loser_name":"b"} 
@app.route('/post_match', methods=['POST'])
def update_data():    
    try:
        data = request.get_json()
        print(data)
        if data is None:
            return jsonify({"error": "Invalid JSON data"}), 400

        winnername = data.get("winner_name")
        losername = data.get("loser_name")
        if winnername is None or losername is None:
            return jsonify({"error": "Invalid data format"}), 400
        
        cursor.execute('SELECT id FROM players WHERE player_name = ?', (winnername,))
        winner_id = cursor.fetchone()[0]
        
        cursor.execute('SELECT id FROM players WHERE player_name = ?', (losername,))
        loser_id = cursor.fetchone()[0]

        cursor.execute('INSERT INTO matches (winner_id, loser_id) VALUES (?, ?)', (winner_id, loser_id))

        # 승자와 패자의 승리 및 패배 업데이트
        cursor.execute('UPDATE players SET wins = wins + 1 WHERE id = ?', (winner_id,))
        cursor.execute('UPDATE players SET score = score + 2 WHERE id = ?', (winner_id,))
        cursor.execute('UPDATE players SET losses = losses + 1 WHERE id = ?', (loser_id,))
        cursor.execute('UPDATE players SET score = score - 1 WHERE id = ?', (loser_id,))
        conn.commit()


        return jsonify({"message": "Data added successfully"})
    except Exception as e:
        return jsonify({"error": str(e)}), 500                                                                        


# 게임 스킬 프리셋 정보 업데이트 API
# client에서 보낼 json 형식 :
# {"player_name": "a", "skills": ["Skill1", "Skill2", "Skill3"], "settings": {"option1": true, "option2": false}}
@app.route('/post_preset', methods=['POST'])
def update_preset():  
            
        try:
            data = request.get_json()
            if data is None:
                return jsonify({"error": "Invalid JSON data"}), 400 
            
            player_name = data.get("player_name")
            skills = data.get("skills")
            settings = data.get("settings")
            if player_name is None or skills is None or settings is None:
                return jsonify({"error": "Invalid data format"}), 400
            
            # 딕셔너리를 JSON 문자열로 변환하여 저장(SQLite에서 파라미터 바인딩 시에 딕셔너리 데이터 타입을 직접 지원하지 않기 때문)
            settings_str = json.dumps(settings)
            # 스킬 목록을 문자열로 변환하여 저장(SQLite에서 파라미터 바인딩 시에 리스트 데이터 타입을 직접 지원하지 않기 때문)
            skills_str = ', '.join(skills)
            cursor.execute("INSERT INTO skill_presets (player_name, skills, settings) VALUES (?, ?, ?)", (player_name, skills_str, settings_str))
            conn.commit()

            return jsonify({"message": "Skillset added successfully"})
        
        except Exception as e:
            return jsonify({"error": str(e)}), 500         
        
# 랭킹 조회
@app.route('/get_ranking', methods=['GET'])
def get_ranking(limit=5):
    cursor.execute('SELECT player_name, wins, losses, score FROM players ORDER BY score DESC LIMIT ?', (limit,))
    ranking = cursor.fetchall()
    return ranking

# 실시간 접속자 수를 저장하는 변수
current_connections = 0
current_connections_lock = threading.Lock()

# 게임 유저 접속 이벤트를 처리하는 함수
def handle_connection_event(player_name):
    global current_connections
    with current_connections_lock:
        current_connections += 1
    cursor.execute("INSERT INTO player_connections (player_name) VALUES (?)", (player_name,))
    conn.commit()

# 게임 유저 로그아웃 이벤트를 처리하는 함수
def handle_logout_event(player_name):
    global current_connections
    with current_connections_lock:
        current_connections -= 1
    conn.execute("DELETE FROM player_connections WHERE player_name = ?", (player_name,))
    conn.commit()

# 게임 유저 접속 상태 조회 API
@app.route('/get_connections', methods=['GET'])
def get_connections():
    with current_connections_lock:
        return jsonify({"current_connections": current_connections})

# 게임 유저 접속 이벤트를 처리하는 API
# client json 예시 : {"player_name":"a"}
@app.route('/player_connect', methods=['POST'])
def player_connect():
    try:
        data = request.get_json()
        if data is None:
            return jsonify({"error": "Invalid JSON data"}), 400

        player_name = data.get("player_name")
        if player_name is None:
            return jsonify({"error": "Invalid data format"}), 400

        handle_connection_event(player_name)

        return jsonify({"message": "Connection event handled successfully"})
    except Exception as e:
        return jsonify({"error": str(e)}), 500

# 게임 유저 로그아웃 이벤트를 처리하는 API
@app.route('/player_logout', methods=['POST'])
def player_logout():
    try:
        data = request.get_json()
        if data is None:
            return jsonify({"error": "Invalid JSON data"}), 400

        player_name = data.get("player_name")
        if player_name is None:
            return jsonify({"error": "Invalid data format"}), 400

        handle_logout_event(player_name)

        return jsonify({"message": "Logout event handled successfully"})
    except Exception as e:
        return jsonify({"error": str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)