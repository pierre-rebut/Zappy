#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import pathfinding
from enum import Enum

class State(Enum):
    RESEARCH = 0
    GROUPCHIEF = 1
    GROUPPEON = 2

class Player(object):
    vision = []
    level = 1
    inventory = {}
    level_up = {1:{"linemate":1, "deraumere":0, "sibur":0, "mendiane":0, "phiras":0, "thystame":0},
                2:{"linemate":1, "deraumere":1, "sibur":1, "mendiane":0, "phiras":0, "thystame":0},
                3:{"linemate":2, "deraumere":0, "sibur":1, "mendiane":0, "phiras":2, "thystame":0},
                4:{"linemate":1, "deraumere":1, "sibur":2, "mendiane":0, "phiras":1, "thystame":0},
                5:{"linemate":1, "deraumere":2, "sibur":1, "mendiane":3, "phiras":0, "thystame":0},
                6:{"linemate":1, "deraumere":2, "sibur":3, "mendiane":0, "phiras":1, "thystame":0},
                7:{"linemate":2, "deraumere":2, "sibur":2, "mendiane":2, "phiras":2, "thystame":1}}
    state = State.RESEARCH
    hungry = False
    needVision = False
    group = []

    def __init__(self, team_name, id_):
        self.team_name = team_name
        self.id_ = id_

    def set_vision(self, seen):
        if (seen[0] == '{'):
            self.vision = str.split(str.strip(seen.rstrip(), '{}'), ',')

    def set_inventory(self, inventory):
        tmp_inventory = []
        tmp_inventory = str.split(str.strip(inventory.rstrip(), '{}'), ',')
        i = 0
        if (len(tmp_inventory) < 7):
            return
        while (i < len(tmp_inventory)):
            tmp_inventory[i] = str.split(str.lstrip(tmp_inventory[i]), ' ')
            i += 1
        self.inventory[tmp_inventory[0][0]] = int(tmp_inventory[0][1])
        self.inventory[tmp_inventory[1][0]] = int(tmp_inventory[1][1])
        self.inventory[tmp_inventory[2][0]] = int(tmp_inventory[2][1])
        self.inventory[tmp_inventory[3][0]] = int(tmp_inventory[3][1])
        self.inventory[tmp_inventory[4][0]] = int(tmp_inventory[4][1])
        self.inventory[tmp_inventory[5][0]] = int(tmp_inventory[5][1])
        self.inventory[tmp_inventory[6][0]] = int(tmp_inventory[6][1])

    def add_in_inventory(self, nourriture, linemate, deraumere, sibur, mendiane, phiras, thystame):
        self.inventory["nourriture"] += nourriture
        self.inventory["linemate"] += linemate
        self.inventory["deraumere"] += deraumere
        self.inventory["sibur"] += sibur
        self.inventory["mendiane"] += mendiane
        self.inventory["phiras"] += phiras
        self.inventory["thystame"] += thystame

    def check_inventory(self, nourriture, linemate, deraumere, sibur, mendiane, phiras, thystame):
        if (self.inventory["nourriture"] < nourriture or self.inventory["linemate"] < linemate or
            self.inventory["sibur"] < sibur or self.inventory["mendiane"] < mendiane or
            self.inventory["phiras"] < phiras or self.inventory["thystame"] < thystame):
            return (False)
        return (True)

    def can_i_up(self):
        grid = self.level_up[self.level]
        if (grid["linemate"] > self.inventory["linemate"] or
            grid["deraumere"] > self.inventory["deraumere"] or
            grid["sibur"] > self.inventory["sibur"] or
            grid["mendiane"] > self.inventory["mendiane"] or
            grid["phiras"] > self.inventory["phiras"] or
            grid["thystame"] > self.inventory["thystame"]):
            return (False)
        return (True)

    def have_enough(self):
        grid = self.level_up[self.level]
        for stone in grid:
            if (grid[stone] > self.inventory[stone]):
                return stone
        return ("ok")

    def get_pos(self, obj):
        if (self.vision == [] or len(self.vision) < pathfinding.nb_max(self.level)):
            return (-1)
        row = self.level
        nb_coups = 0
        while ((nb_coups - 1) / 2 <= row):
            if (nb_coups <= row and obj in self.vision[pathfinding.nb_middle(nb_coups)]):
                return (pathfinding.nb_middle(nb_coups))
            if (nb_coups > 2):
                toto = 0
                val_min = pathfinding.nb_middle(nb_coups - 2) - 1
                val_max = pathfinding.nb_middle(nb_coups - 2) + 1
                if (val_min <= pathfinding.nb_max(row) or val_max <= pathfinding.nb_max(row)):
                    if (obj in self.vision[val_min]):
                        return (val_min)
                    if (obj in self.vision[val_max]):
                        return (val_max)
                toto += 1
                while (toto <= nb_coups - 4):
                    if (toto + 1 <= nb_coups - 2 - toto):
                        val_min = pathfinding.nb_middle(nb_coups - 2 - toto) - 1 - toto
                        val_max = pathfinding.nb_middle(nb_coups - 2 - toto) + 1 + toto
                        if (val_min <= pathfinding.nb_max(row) or val_max <= pathfinding.nb_max(row)):
                            if (obj in self.vision[val_min]):
                                return (val_min)
                            if (obj in self.vision[val_max]):
                                return (val_max)
                    toto += 1
            nb_coups += 1
        return (-1)
