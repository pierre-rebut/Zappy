#!/bin/sh
## test.sh for ds in /home/rebut_p/Programmation/PSU/PSU_2015_zappy/server_dir
## 
## Made by Pierre Rebut
## Login   <rebut_p@epitech.net>
## 
## Started on  Wed Jun 22 16:45:12 2016 Pierre Rebut
## Last update Thu Jun 23 17:24:13 2016 Simon Desplat
##

for i in $(seq 1 $1)
do
    ./connect.py -n toto -h 127.0.0.1 -p 6667 &
done
