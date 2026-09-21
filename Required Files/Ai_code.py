import cv2
import mediapipe as mp
import math
import threading
import time

# --- الإعدادات المسار ---
file_path = r"D:\self_study\RoboTech\Project\Fair_Project\Fair_Project\files\gesture.txt"
path_pos = r"D:\self_study\RoboTech\Project\Fair_Project\Fair_Project\files\positions.txt"
path_pagetxt = r"D:\self_study\RoboTech\Project\Fair_Project\Fair_Project\files\pagetxt.txt"

# --- المتغيرات العامة ---
mp_hands = mp.solutions.hands
mp_drawing = mp.solutions.drawing_utils
exit_flag = False
current_gestures = {"Left": "None", "Right": "None"}
var = 0
x_pos = 0.5
y_pos = 0.5

# --- كلاس قراءة الكاميرا لضمان السلاسة (No Lag) ---
class VideoStream:
    def __init__(self, src=0):
        self.stream = cv2.VideoCapture(src)
        self.stream.set(cv2.CAP_PROP_FOURCC, cv2.VideoWriter_fourcc('M','J','P','G'))
        self.stream.set(cv2.CAP_PROP_FRAME_WIDTH, 300)
        self.stream.set(cv2.CAP_PROP_FRAME_HEIGHT, 300)
        self.stream.set(cv2.CAP_PROP_BUFFERSIZE, 1)
        (self.grabbed, self.frame) = self.stream.read()
        self.stopped = False

    def start(self):
        threading.Thread(target=self.update, args=(), daemon=True).start()
        return self

    def update(self):
        while not self.stopped:
            (self.grabbed, self.frame) = self.stream.read()

    def read(self):
        return self.frame

    def stop(self):
        self.stopped = True
        self.stream.release()

def control_system(results , frame):
            temp = {"Left": "None", "Right": "None"}
            if results.multi_hand_landmarks and results.multi_handedness:
                for idx, hand_landmarks in enumerate(results.multi_hand_landmarks):
                    label = results.multi_handedness[idx].classification[0].label 
                    lm = hand_landmarks.landmark
                    max_y = hand_landmarks.landmark[0].y
                    max_index_y = 0
                    middel_up = lm[12].y < lm[10].y
                    index_up = lm[8].y < lm[6].y

                    for i in range(21):
                        if lm[i].y < max_y:
                            max_y = lm[i].y
                            max_index_y = i

                    if label == "Left":
                        dist = math.hypot(lm[8].x - lm[4].x, lm[8].y - lm[4].y , lm[8].z - lm[4].z)
                        if dist < 0.08: temp["Left"] = "J"
                        elif index_up and not middel_up: temp["Left"] = "player one"
                        elif index_up and middel_up: temp["Left"] = "player two"
                    
                    elif label == "Right":
                        x_coords = [p.x for p in lm]        
                        y_coords = [p.y for p in lm]
                        thumb_x = lm[4].x
                        idx_up = lm[8].y < lm[6].y
                        mid_up = lm[12].y < lm[10].y
                    
                        if idx_up and not mid_up: temp["Right"] = "u"
                        elif idx_up and mid_up: temp["Right"] = "d"
                        elif max_index_y == 4: temp["Right"] = "s"
                        elif thumb_x <= min(x_coords): temp["Right"] = "L"
                        elif thumb_x >= max(x_coords): temp["Right"] = "R"

                        
                    
                        

                    mp_drawing.draw_landmarks(
                        frame,
                        hand_landmarks,
                        mp_hands.HAND_CONNECTIONS,
                        mp_drawing.DrawingSpec(color=(0, 255, 0), thickness=2, circle_radius=2)
                    )
            return temp

def control_game(results , frame):
            temp = {"Left": "None", "Right": "None"}
            if results.multi_hand_landmarks and results.multi_handedness:
                for idx, hand_landmarks in enumerate(results.multi_hand_landmarks):
                    label = results.multi_handedness[idx].classification[0].label 
                    lm = hand_landmarks.landmark
                    max_y = hand_landmarks.landmark[0].y
                    

                    if label == "Left":
                        dist = math.hypot(lm[8].x - lm[4].x, lm[8].y - lm[4].y , lm[8].z - lm[4].z)
                        if dist < 0.08: temp["Left"] = "J"
                        
                    
                    elif label == "Right":
                        x_coords = [p.x for p in lm]        
                        thumb_x = lm[4].x
                        
                        if thumb_x <= min(x_coords): temp["Right"] = "L"
                        elif thumb_x >= max(x_coords): temp["Right"] = "R"
                        

                    mp_drawing.draw_landmarks(
                        frame,
                        hand_landmarks,
                        mp_hands.HAND_CONNECTIONS,
                        mp_drawing.DrawingSpec(color=(0, 255, 0), thickness=2, circle_radius=2)
                    )
            return temp

def control_profile(results , frame):
            global x_pos , y_pos
            selecting=0
            temp = {"Left": "None", "Right": "None"}
            if results.multi_hand_landmarks and results.multi_handedness:
                for idx, hand_landmarks in enumerate(results.multi_hand_landmarks):
                    label = results.multi_handedness[idx].classification[0].label 
                    lm = hand_landmarks.landmark

                    
                    if label == "Right":
                        max_y_index = 0
                        min_x_index = 0
                        max_y_finger = hand_landmarks.landmark[0].y
                        min_x_finger = hand_landmarks.landmark[0].x
                        for i , hand in enumerate(hand_landmarks.landmark):
                            if max_y_finger > hand.y:
                                max_y_index = i
                                max_y_finger = hand.y
                        
                            if min_x_finger > hand.x:
                                min_x_index = i
                                min_x_finger = hand.x
                    
                        if max_y_index == 8:
                            x_pos = hand_landmarks.landmark[8].x
                            y_pos = hand_landmarks.landmark[8].y
                            print(f"X = {x_pos}\nY = {y_pos}")

                        if min_x_index == 4:
                            selecting=1

                        with open(path_pos , "w") as f:
                            f.write(f"{x_pos}\n{y_pos}\n{selecting}")
                    
                        

                    mp_drawing.draw_landmarks(
                        frame,
                        hand_landmarks,
                        mp_hands.HAND_CONNECTIONS,
                        mp_drawing.DrawingSpec(color=(0, 255, 0), thickness=2, circle_radius=2)
                    )
            return temp

# --- ثريد معالجة اليد (منطقك الأصلي بالحرف) ---
def hand_detection_thread():
    global exit_flag, current_gestures,var
    vs = VideoStream(0).start()
    time.sleep(1.0) 
    
    temp = {"Left": "None", "Right": "None"}
    with mp_hands.Hands(
        model_complexity=0, 
        min_detection_confidence=0.8, 
        min_tracking_confidence=0.8
    ) as hands:
        while not exit_flag:
            frame = vs.read()
            if frame is None: continue
            
            with open(path_pagetxt , "r") as filee:
                var = filee.read()
                print(var)
                print(type(var))
            frame = cv2.flip(frame, 1)
            image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            results = hands.process(image)
            
            if var == "0":
                temp = control_system(results , frame)
            elif var == "1":
                temp = control_profile(results , frame)
            elif var == "2":
                temp = control_game(results , frame)


            current_gestures = temp
            R_tex = temp["Right"]
            L_tex = temp["Left"]
            cv2.putText(frame , f"Right Hand : f{R_tex} : " , (10 , 50) , 1 , 1.5 , (0,0,255) , 1)
            cv2.putText(frame , f"Left Hand : f{L_tex} : " , (10 , 200) , 1 , 1.5 , (0,0,255) , 1)
            cv2.imshow('Icy Tower - Faster Response', frame)
            cv2.moveWindow('Icy Tower - Faster Response' , 1200 , 0)
            if cv2.waitKey(1) & 0xFF == ord('q'): 
                exit_flag = True
                vs.stop()
                break
    cv2.destroyAllWindows()

# --- ثريد الكتابة (تحسين السرعة القصوى وفك اللاج) ---
def file_writer_thread():
    global exit_flag, current_gestures
    last_sent = ""
    last_menu_time = 0
    menu_cooldown = 0.3 
    none_counter = 0

    while not exit_flag:
        active = [v for v in current_gestures.values() if v != "None"]
        current_time = time.time()
        msg = " ".join(active) if active else "None"
        
        is_menu =  any(c in ["u", "d", "s", "player one", "player two"] for c in active)

        try:
            if is_menu:
                if (current_time - last_menu_time) > menu_cooldown:
                    # نستخدم 'wb' مع encode لضمان أسرع كتابة بايتات مباشرة
                    with open(file_path, "wb", buffering=0) as f: 
                        f.write(msg.encode())
                    time.sleep(0.06) # نبضة سريعة جداً للمنيو
                    with open(file_path, "wb", buffering=0) as f: 
                        f.write(b"None")
                    last_menu_time = current_time
                    last_sent = "None" 

            else:
                # الحركة في اللعبة (نط ويمين وشمال)
                if msg != last_sent:
                    with open(file_path, "wb", buffering=0) as f: 
                        f.write(msg.encode())
                    last_sent = msg
                    none_counter = 0
                
                if msg == "None":
                    none_counter += 1
                    if none_counter >= 2 and last_sent != "None":
                        with open(file_path, "wb", buffering=0) as f: 
                            f.write(b"None")
                        last_sent = "None"
        except: pass
        
        # الانتظار 1 ملّي ثانية فقط لاستجابة فورية
        time.sleep(0.001) 

if __name__ == "__main__":
    t1 = threading.Thread(target=hand_detection_thread, daemon=True)
    t2 = threading.Thread(target=file_writer_thread, daemon=True)
    t1.start()
    t2.start()
    
    while not exit_flag:
        time.sleep(1)