#!/usr/bin/env python 3
# -*- coding: utf-8 -*-

import socket
import algo

def nb_min(row):
    return (row ** 2)

def nb_middle(row):
    return (row ** 2 + row)

def nb_max(row):
    return (row ** 2 + 2 * row)

def go_forward(nb, sock):
    while (nb > 0):
        algo.send_data(sock, "avance\n")
        nb -= 1

def path_finding(goal, sock):
    row = 0
    print(goal)
    if (goal != 0):
        while (goal > nb_max(row)):
            row += 1
        go_forward(row, sock)
    if (goal != nb_middle(row)):
        if (goal < nb_middle(row)):
            algo.send_data(sock, "gauche\n")
            pass
        else:
            algo.send_data(sock, "droite\n")
            pass
        go_forward(abs(nb_middle(row) - goal), sock)
