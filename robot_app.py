import serial
import time
import Tkinter
from Tkinter import *
import threading
from PIL import ImageTk, Image

# Minotaurs position i,j -> maze[2*i+1][2*j+1]

# Minotaur's current position #
iCoordM = 4
jCoordM = 4
crossedCells = 0
distance = 0
# --------------------------- #

# Maze representation ------------------------------------------ #
maze_inicial = [['#','#','#','#','#','#','#','#','#','#','#'],
        ['#',' ','|',' ','|',' ','|',' ','|',' ','#'],
        ['#','-','#','-','#','-','#','-','#','-','#'],
        ['#',' ','|',' ','|',' ','|',' ','|',' ','#'],
        ['#','-','#','-','#','-','#','-','#','-','#'],
        ['#',' ','|',' ','|',' ','|',' ','|',' ','#'],
        ['#','-','#','-','#','-','#','-','#','-','#'],
        ['#',' ','|',' ','|',' ','|',' ','|',' ','#'],
        ['#','-','#','-','#','-','#','-','#','-','#'],
        ['#',' ','|',' ','|',' ','|',' ','|',' ','#'],
        ['#','#','#','#','#','#','#','#','#',' ','#']]

maze = [['#','#','#','#','#','#','#','#','#','#','#'],
        ['#',' ','|',' ','|',' ','|',' ','|',' ','#'],
        ['#','-','#','-','#','-','#','-','#','-','#'],
        ['#',' ','|',' ','|',' ','|',' ','|',' ','#'],
        ['#','-','#','-','#','-','#','-','#','-','#'],
        ['#',' ','|',' ','|',' ','|',' ','|',' ','#'],
        ['#','-','#','-','#','-','#','-','#','-','#'],
        ['#',' ','|',' ','|',' ','|',' ','|',' ','#'],
        ['#','-','#','-','#','-','#','-','#','-','#'],
        ['#',' ','|',' ','|',' ','|',' ','|',' ','#'],
        ['#','#','#','#','#','#','#','#','#',' ','#']]
		
mazePrueba = [['#','#','#','#','#','#','#','#','#','#','#'],
	      ['#','0','#','0','|','0','#','0','|','0','#'],
	      ['#','-','#','-','#','#','#','-','#','#','#'],
	      ['#','0','#','0','|','0','#','0','|','0','#'],
	      ['#','-','#','#','#','-','#','#','#','-','#'],
	      ['#','0','#','0','#','0','|','0','#','0','#'],
	      ['#','-','#','-','#','#','#','-','#','-','#'],
	      ['#','0','#','0','|','0','#','0','|','0','#'],
	      ['#','-','#','-','#','-','#','-','#','-','#'],
	      ['#','0','|','0','#','0','|','0','#','0','#'],
	      ['#','#','#','#','#','#','#','#','#','E','#']]
# -------------------------------------------------------------- #

# ------------------------------------------------------------------ CLASS ------------------------------------------------------------------------- #
# -------------------------------------------------------------------------------------------------------------------------------------------------- #

# Threading class which is constantly reading the serial connection with the minotaur
class serialThread(threading.Thread):
    # initialize class
    def __init__(self, arduino):
        threading.Thread.__init__(self)
        self.arduino = arduino
        self.bufferArduino = ""

    def run(self):
        while 1:
            self.bufferArduino = ""
            try:
                while(self.arduino.inWaiting() > 0):
                    self.bufferArduino += self.arduino.read(1)
                proc_buffer(self.bufferArduino)
                arduino.flush()
            except:
                pass
            time.sleep(2)

# ------------------------------------------------------------------ FUNCTIONS --------------------------------------------------------------------- #
# -------------------------------------------------------------------------------------------------------------------------------------------------- #

# Function that insterts text into the text aera of the app
def insert_textArea(str):
    textArea.insert(END,str)
    textArea.see(END)

# Function that connects to the minotaur using a COM port. 
# It starts the thread which recieves messages from the minotaur
def connect_to_arduino():
    global arduino
    port = (entryCOM.get())
    portCOM = int(port)
    insert_textArea("Connecting to Minotaur with COM port "+str(portCOM)+"...\n")
    try:
        arduino = serial.Serial(portCOM-1,9600,timeout=0,writeTimeout=0) #Windows--> Serial(PortNumber-1)
        time.sleep(2)  # Wait initialization
        insert_textArea("Connection established with "+arduino.name+'\n')
        thread1 = serialThread(arduino)
        thread1.start()
    except Exception, e:
        insert_textArea("Connection attemp failed. Try again....\n")
        print(e)

# Function that close the connection with the minotaur and
# clean both maze and text areas
def clean():
    global maze, maze_inicial, crossedCells, iCoordM, jCoordM
    textArea.delete('0.0',END)
    insert_textArea("Waiting for a COM port to connect to Minotaur...\n")
    maze = maze_inicial
    crossedCells = 0
    distance = 0
    iCoordM = 4
    jCoordM = 4
    update_maze(0,0,'')
    arduino.close()
    

# Function that close the connection with the minotaur
def finish():
    textArea.delete('0.0',END)
    arduino.close()
    insert_textArea("APLICACION ACABADA\n")

# Function that update the maze representation with new data
def update_maze(i,j,c):
    global crossedCells, distance
    maze[i][j] = c
    mazeArea.delete('0.0',END)
    mazeArea.insert(END,"--------------------------- Maze ---------------------------\n\t\t\t# = Wall\n\t\t\tF = Finish\n\t\t\tM = Minotaur\n\t\t\t0 = Path\n\n")
    mazeArea.insert(END,"\t\t  0   1   2   3   4\n")
    row = 0
    for i in range(11):
        mazeArea.insert(END,"\t\t")
        for j in range(11):
            mazeArea.insert(END,maze[i][j]+' ')
        if(i == 2*row+1):
            mazeArea.insert(END,str(row))
            row = row+1
        mazeArea.insert(END,"\n")
    mazeArea.insert(END,"\n------------------------------------------------------------\n")
    mazeArea.insert(END,"Number of crossed cells = " + str(crossedCells) + "\n")
    mazeArea.insert(END,"Distance                = " + str(distance) + " cm\n")

# Function that process a buffer and extracts different messages and sends them
# to the function that process the messages.
# 	buffer = #message##message##message##...
def proc_buffer(buffer):
    n = len(buffer)
    m0 = ""
    m1 = ""
    m2 = ""
    m3 = ""
    i = 0
    # print "Mensaje " +buffer
    while(i < n) :
        if(buffer[i] == '0'):
            while(buffer[i] != '#'):
                m0 += buffer[i]
                i = i+1
            #print "m0: " + m0
            message(m0)
            m0 = ""
        elif(buffer[i] == '1') :
            while(buffer[i] != '#'):
                m1 += buffer[i]
                i = i+1
            #print "m1: " + m1
            message(m1)
            m1 = ""
        elif(buffer[i] == '2') :
            while(buffer[i] != '#'):
                m2 += buffer[i]
                i = i+1
            #print "m2: " +  m2
            message(m2)
            m2 = ""
        elif(buffer[i] == '3') :
            while(buffer[i] != '#'):
                m3 += buffer[i]
                i = i+1
            #print "m3: " +  m3
            message(m3)
            m3 = ""

        i = i+1
       
# Function that recieves a message from the minotaur and process it
# Message formats: COD+Info
#       0"message"  : text message from the minotaur
#       1ij         : minotaur's maze position update to coordinates i & j (0 <= i,j <= 4)
#       2k          : wall discovered by the minotaur in his cell in position k (0:up, 1:bottom, 2:left, 3:right)
#       3x          : x = Number of crossed cells
def message(entry_str):
    global iCoordM, jCoordM, crossedCells, distance
    fc = entry_str[0] # fc = COD
    
    if (fc == '0'):
        # COD = 0 -> message from arduino
        message = entry_str[1:]     # Remove first char(COD)
        insert_textArea(message+'\n')
        
    elif (fc == '1'):
        # COD = 1 -> minotaur's maze position update
        j = int(entry_str[1])
        i = int(entry_str[2])
        if(maze[2*i+1][2*j+1] == '0'):
            # the minotaur is returning to a previously visited cell
            update_maze(2*iCoordM+1, 2*jCoordM+1, ' ')    
        else:
            # the minotaur is moving to a new cell
             update_maze(2*iCoordM+1, 2*jCoordM+1, '0')
        update_maze(2*i+1, 2*j+1, 'M')
        iCoordM = i
        jCoordM = j
        insert_textArea("Minotaur entering cell "+str(i)+" "+str(j)+'\n')
        
    elif (fc == '2'):
        # COD = 2 -> wall discovered by the minotaur
        wallPos = entry_str[1]  # Wall position
        if(wallPos == '0'):
            # Wall up
            update_maze(2*iCoordM, 2*jCoordM+1, '#')
            insert_textArea("\tWall discovered: UP\n")
        elif(wallPos == '1'):
            # Wall bottom
            update_maze(2*iCoordM+2, 2*jCoordM+1, '#')
            insert_textArea("\tWall discovered: BOTTOM\n")
        elif(wallPos == '2'):
            # Wall left
            update_maze(2*iCoordM+1, 2*jCoordM, '#')
            insert_textArea("\tWall discovered: LEFT\n")
        elif(wallPos == '3'):
            # Wall right
            update_maze(2*iCoordM+1, 2*jCoordM+2, '#')
            insert_textArea("\tWall discovered: RIGHT\n")

    elif (fc == '3'):
        # COD = 3 -> Number of crossed cells
        crossedCells = crossedCells + 1
        distance = 20*crossedCells
        update_maze(0, 0, '')

    

# ------------------------------------------------------------------ MAIN PROGRAM ------------------------------------------------------------------ #
# -------------------------------------------------------------------------------------------------------------------------------------------------- #
root = Tkinter.Tk()
root.configure(background='white')
root.title("Minotaur")
root.geometry("1200x500")

textArea = Tkinter.Text(root, bg="black", fg="white", width=60, height=50)
scrollBar = Tkinter.Scrollbar(root)
textArea.focus_set()
scrollBar.pack(side=Tkinter.LEFT, fill=Tkinter.Y)
textArea.pack(side=Tkinter.LEFT)
scrollBar.config(command=textArea.yview)
textArea.config(yscrollcommand=scrollBar.set)

insert_textArea("Waiting for a COM port to connect to Minotaur...\n")

mazeArea = Tkinter.Text(root, bg="black", fg="white", width=60, height=50)
mazeArea.pack(side=Tkinter.RIGHT)
update_maze(0,0,'')


labelImg = Tkinter.Label(root, text="_______________________________________\n",bg="white",fg="black")
labelImg.pack()

img = ImageTk.PhotoImage(Image.open("C:\Users\GII\Dropbox\DCE\Robot\Python_bluetooth\games_minotaur.jpg").resize((300, 200), Image.ANTIALIAS))
panel = Tkinter.Label(root, image = img)
panel.pack()

labelMapp = Tkinter.Label(root, text="\nMinotaur v1.0\n_______________________________________",bg="white",fg="black")
labelMapp.pack()

labelCOM = Tkinter.Label(root, text="\nEnter the COM port",bg="white",fg="black")
labelCOM.pack()

entryCOM = Tkinter.Entry(root)
entryCOM.pack()

boton_iniciar = Tkinter.Button(root, text="Connect", command=connect_to_arduino, width=15, height=0, bg="green")
boton_iniciar.pack()

boton_recarga = Tkinter.Button(root, text="Clean", command=clean, width=15, height=0, bg="blue")
boton_recarga.pack()


boton_acabar = Tkinter.Button(root, text="Finish", command=finish, width=15, height=0, bg="red")
boton_acabar.pack()

labelSpace = Tkinter.Label(root, text="\n_______________________________________\n",bg="white",fg="black")
labelSpace.pack()


root.mainloop()

