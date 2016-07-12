#!/usr/bin/python
from board import board

def getInputIf_X():
    result = ""
    while True:
        result = input("Choose \'X\' or \'O\': ")
        if result.upper() == "X":
            return True
        elif result.upper() == "O":
            return False

B = board()
player = getInputIf_X()
B.isPlayerX(player)

while B.playAgain:
    B.update()
    print()


print("END")


