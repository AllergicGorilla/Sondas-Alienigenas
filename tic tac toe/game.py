#!/usr/bin/python
from board import board

B = board()
player = (input("Choose \'X\' or \'O\':\n") == "X")
B.isPlayerX(player)

while B.playAgain:
    B.update()
    B.draw()
    print()


print("END")