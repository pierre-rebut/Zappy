#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import socket
import select
import sys
import random
import player
import time

def error(message, error_code):
    print(message, file=sys.stderr)
    sys.exit(error_code)

def parse_arguments():
    if (len(sys.argv) != 5 and len(sys.argv) != 7):
        error("usage : " + sys.argv[0] + " -n team_name -h hostname -p port", 1)
    check = [False]*3
    args = [None]*3
    i = 0
    idx = 1
    lim = 3
    if (len(sys.argv) == 5):
        args[0] = "localhost"
        lim = 2
    while (i < lim):
        if (sys.argv[idx] == "-h"):
            if (check[0] == True):
                error("Error : -h already precised", 1)
            args[0] = sys.argv[idx + 1]
            check[0] = True
        elif (sys.argv[idx] == "-p"):
            if (check[1] == True):
                error("Error : -p already precised", 1)
            args[1] = sys.argv[idx + 1]
            check[1] = True
        elif (sys.argv[idx] == "-n"):
            if (check[2] == True):
                error("Error : -n already precised", 1)
            args[2] = sys.argv[idx + 1]
            check[2] = True
        i += 1
        idx += 2
    i = 1
    while (i < 3):
        if (check[i] == False):
            error("usage : ./zappy_ai -n team_name -p port [-h hostname]", 1)
        i += 1
    try:
        args[1] = int(args[1])
    except:
        error("port must be a number", 1)
    return args

pathBuf = []
noAnsList = []
waitingList = []
isElev = False
launchInc = False
curAct = "first\n"

def nb_min(row):
    return (row ** 2)

def nb_middle(row):
    return (row ** 2 + row)

def nb_max(row):
    return (row ** 2 + 2 * row)

def go_forward(nb, sock):
    while (nb > 0):
        add_buffer("avance\n")
        nb -= 1

def path_finding(goal, sock):
    row = 0
    if (goal != 0):
        while (goal > nb_max(row)):
            row += 1
        go_forward(row, sock)
    if (goal != nb_middle(row)):
        if (goal < nb_middle(row)):
            add_buffer("gauche\n")
        else:
            add_buffer("droite\n")
        go_forward(abs(nb_middle(row) - goal), sock)

def add_buffer(elem):
    global pathBuf

    pathBuf.append(elem)

def find_broadcast(direction):
        if (direction == 0):
            return
        if (direction == 1 or direction == 2 or direction == 8):
            add_buffer("avance\n")
            add_buffer("voir\n")
        elif (direction == 6 or direction == 7):
            add_buffer("droite\n")
            add_buffer("avance\n")
            add_buffer("voir\n")
        elif (direction == 4 or direction == 3):
            add_buffer("gauche\n")
            add_buffer("avance\n")
            add_buffer("voir\n")
        elif (direction == 5):
            add_buffer("droite\n")
            add_buffer("droite\n")
            add_buffer("avance\n")
            add_buffer("voir\n")

def what_to_put(player):
    lvl = player.level
    needed = player.level_up[lvl]
    for stone in needed:
        quantity = needed[stone]
        while (quantity > 0):
            add_buffer("pose " + stone + "\n")
            quantity -= 1

def send_data(sock, elem):
    global curAct

    print("[ACTION] " + elem, end="")
    curAct = elem
    elem = elem.encode()
    sock.send(elem)

def random_move(sock):
    praise = random.randint(0, 2)
    if (praise == 0):
        send_data(sock, "avance\n")
    elif (praise == 1):
        send_data(sock, "gauche\n")
    elif (praise == 2):
        send_data(sock, "droite\n")

def pick_everything(sock, play):
    if (play.get_pos("nourriture") == 0):
        send_data(sock, "prend nourriture\n")
        return 0
    if (play.get_pos("linemate") == 0):
        send_data(sock, "prend linemate\n")
        return 0
    if (play.get_pos("deraumere") == 0):
        send_data(sock, "prend deraumere\n")
        return 0
    if (play.get_pos("sibur") == 0):
        send_data(sock, "prend sibur\n")
        return 0
    if (play.get_pos("mendiane") == 0):
        send_data(sock, "prend mendiane\n")
        return 0
    if (play.get_pos("phiras") == 0):
        send_data(sock, "prend phiras\n")
        return 0
    if (play.get_pos("thystame") == 0):
        send_data(sock, "prend thystame\n")
        return 0
    return 1

def algo_lvl1(msg, sock, play):
    global curAct
    global pathBuf
    global pos
    global launchInc
    global isElev

    if (msg == "mort\n"):
        print("[JOUEUR] I am dead :(")
        sys.exit(1)
    if (msg.startswith("message")):
        return 0
    if ((not msg and curAct == "first\n") or (pos == -1 and curAct == "avance\n") or (curAct.startswith("prend") and msg == "ko\n")):
        send_data(sock, "voir\n")
        return 0
    if (msg and curAct == "voir\n"):
        play.set_vision(msg)
        pos = play.get_pos("nourriture")
        if (pos == -1):
            random_move(sock)
            return 0
    if (play.get_pos("linemate") == 0 and isElev == False):
        isElev = True
    if (isElev == False and launchInc == True):
        send_data(sock, "incantation\n")
        launchInc = False
        return 0
    if (isElev == True):
        if (pick_everything(sock, play) == 1):
            send_data(sock, "pose linemate\n")
            isElev = False
            launchInc = True
        return 0
    if (msg == "elevation en cours\n"):
        return 0
    if (msg.startswith("niveau")):
        play.level += 1
        print ("[JOUEUR] vient de monter niveau " + str(play.level) + " !")
        send_data(sock, "voir\n")
        return 0
    if (pos > 0 and not pathBuf):
        path_finding(pos, sock)
    if (msg == "ko\n"):
        random_move(sock)
        pos = -1
        return 0
    if (pathBuf):
        send_data(sock, pathBuf[0])
        pathBuf.pop(0)
        if (not pathBuf):
            pos = 0
    elif (pos == 0):
        send_data(sock, "prend nourriture\n")
    else:
        send_data(sock, "avance\n")

upOk = False
foodRefill = False
doInv = True
goToInc = -1
ressource = "deraumere"
checkInv = 0
missingPpl = 1
sendOkMsg = False

incBegin = False
msgSent = False
needVision = False

def message_analysis(msg, play):
    global goToInc
    global sendOkMsg
    global launchInc
    global incBegin
    global missingPpl
    global needVision

    print ("[MESSAGE] " + (msg[len("message "):]), end="")
    msg = msg.replace(',', ' ')
    msg = msg.replace('\n', ' ')
    words = msg.split(' ')
    if (words[2] == play.team_name):
        if (words[4] == str(play.level)):
            if (words[3] == "incantation"):
                goToInc = int(words[1])
            elif (words[3] == "join"):
                if (words[1] == "0"):
                    missingPpl -= 1
                    sendOkMsg = True
                    if (missingPpl == 0):
                        incBegin = True
                        needVision = True
                else:
                    sendOkMsg = False
            elif (words[3] == "accepted"):
                launchInc = True
                msgSent = False

pplNeeded = [0, 0, 1, 1, 3, 3, 5, 5]

def algo_smart(msg, sock, play):
    global pos
    global curAct
    global upOk
    global foodRefill
    global doInv
    global ressource
    global goToInc
    global checkInv
    global sendOkMsg
    global launchInc
    global incBegin
    global missingPpl
    global msgSent
    global needVision

    checkInv += 1
    if (msg == "mort\n"):
        print("[JOUEUR] I am dead :(")
        sys.exit(1)
    if (msg.startswith("message")):
        message_analysis(msg, play)
        return 0
    if (msg == "elevation en cours\n"):
        return 0
    if (msg.startswith("niveau")):
        play.level += 1
        print ("[JOUEUR] vient de monter niveau " + str(play.level) + " !")
        missingPpl = pplNeeded[play.level]
        if (needVision):
            send_data(sock, "voir\n")
        needVision = False
        incBegin = False
        launchInc = False
        msgSent = False
        upOk = False
        goToInc = -1
        return 0
    if ((play.inventory == {} and curAct != "inventaire\n") or doInv == True or checkInv >= 50):
        checkInv = 0
        send_data(sock, "inventaire\n")
        doInv = False
        return 0
    if (msg and curAct == "inventaire\n"):
        play.set_inventory(msg)
        send_data(sock, "voir\n")
        return 0
    if (msg and curAct == "voir\n"):
        play.set_vision(msg)
        if (incBegin or launchInc):
            ressource = "joueur"
        elif (foodRefill):
            ressource = "nourriture"
        else:
            if (not launchInc):
                ressource = play.have_enough()
            if (ressource == "ok"):
                ressource = "nourriture"
        pos = play.get_pos(ressource)
        if (pos == -1):
            random_move(sock)
            return 0
    if (msgSent or launchInc):
        send_data(sock, "inventaire\n")
        return 0
    if (needVision):
        send_data(sock, "voir\n")
        needVision = False
        return 0
    if (incBegin and not needVision):
        if (pick_everything(sock, play) == 0):
            return 0
        pathBuf.clear()
        what_to_put(play)
        incBegin = False
    if (sendOkMsg):
        send_data(sock, "broadcast " + play.team_name + " accepted " + str(play.level) + "\n")
        sendOkMsg = False
        return 0
    if (goToInc == 0 and not msgSent):
        send_data(sock, "broadcast " + play.team_name + " join " + str(play.level) + "\n")
        msgSent = True
        return 0
    if (missingPpl == 0 and pathBuf):
        send_data(sock, pathBuf[0])
        pathBuf.pop(0)
        return (0)
    if (missingPpl == 0 and not pathBuf):
        send_data(sock, "incantation\n")
        needVision = True
        return 0
    if (launchInc):
        send_data(sock, "inventaire\n")
        return 0
    if ((not msg and curAct == "first\n") or (pos == -1 and curAct == "avance\n") or (curAct.startswith("prend") and msg == "ko\n")):
        send_data(sock, "voir\n")
        return 0
    if (goToInc > 0 and not pathBuf):
        find_broadcast(goToInc)
    if (pos > 0 and not pathBuf):
        path_finding(pos, sock)
    if (play.check_inventory(6, 0, 0, 0, 0, 0, 0) == False):
        foodRefill = True
    if (play.check_inventory(20, 0, 0, 0, 0, 0, 0) and foodRefill):
        foodRefill = False
    if (foodRefill and pathBuf):
        send_data(sock, pathBuf[0])
        pathBuf.pop(0)
        if (not pathBuf):
            pos = 0
        return 0
    if (foodRefill and pos == 0):
        send_data(sock, "prend nourriture\n")
        return 0
    if (play.can_i_up() and not upOk):
        upOk = True
    if (upOk):
        send_data(sock, "broadcast " + play.team_name + " incantation " + str(play.level) + "\n")
        return 0
    if (msg == "ko\n"):
        random_move(sock)
        pos = -1
        return 0
    if (pathBuf):
        send_data(sock, pathBuf[0])
        pathBuf.pop(0)
        if (not pathBuf):
            pos = 0
        return 0
    elif (pos == 0):
        send_data(sock, "prend " + ressource + "\n")
    else:
        send_data(sock, "broadcast cc cherche grp pr lvl 3 pls mp\n")
        doInv = True

def do_action(msg, sock, play):
    if (msg == "\n"):
        return 0
    if (play.level == 1):
        algo_lvl1(msg, sock, play)
    else:
        algo_smart(msg, sock, play)

def init():
    global actSent
    global pos

    random.seed()
    args = parse_arguments()
    poller = select.poll()
    serv_sock = socket.create_connection((args[0], int(args[1])))
    pos = -1
    welcome = serv_sock.recv(1024)
    team_name = args[2] + "\n"
    serv_sock.send(team_name.encode())
    init_data = serv_sock.recv(1024).decode()
    dataTab = init_data.split('\n')
    if (dataTab[1] == "" and not dataTab[0].startswith("ko")):
        dataTab[1] = serv_sock.recv(1024).decode()
    if (dataTab[0].startswith("ko")):
        print("Server refused connection, please try again")
        sys.exit(1)
    play1 = player.Player(args[2], int(dataTab[0]))
    poller.register(serv_sock.fileno())
    do_action("", serv_sock, play1)

    while True:
        pollFd = poller.poll(1)
        for fd, event in pollFd:
            serv_info = ""
            doneCmd = ""
            if (event & select.POLLIN):
                buf = serv_sock.recv(1024)
                serv_info += buf.decode()
                while (len(buf) == 1024):
                    buf = serv_sock.recv(1024)
                    serv_info += buf.decode()
                serv_info = serv_info.split("\n")
                do_action(serv_info[0] + "\n", serv_sock, play1)
                do_action(serv_info[1] + "\n", serv_sock, play1)
        time.sleep(0.001)
