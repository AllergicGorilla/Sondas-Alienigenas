import random
random.seed()
class board:

	def __init__(self):
		self._matrix = [["-","-","-"],
					   ["-","-","-"],
			 		   ["-","-","-"]]
		self._isPlayerTurn = bool(random.getrandbits(1))
		self._playAgain = True

	def isPlayerX(self, boolean):
		self.playerIsX = boolean

	def mark(self, x, y, Boolean):
		if Boolean:
			self._matrix[y][x] = "X"
		else:
			self._matrix[y][x] = "O"

	def askPlayer(self):
		while True:
			playerX = getPos("x position[1-3]: ")
			playerY = getPos("y position[1-3]: ")
			x = playerX - 1
			y = playerY - 1
			if self._matrix[y][x] == "-":
				break
			print("This place is already occupied.\n")
		print("PLAYER")
		self.mark(x, y, self.playerIsX)
		self._isPlayerTurn = False


	def draw(self):
		for y in self._matrix:
			for x in y:
				print(x, end="")
			print()

	def update(self):
		if self._isPlayerTurn:
			self.askPlayer()
		else:
			#TODO: implement AI
			print("AI")
			#self.mark(random.randint(0,2), random.randint(0,2), not player)
			self._isPlayerTurn = True
		#Checks horizontally
		for row in self._matrix:
			self.__check(row)

		#Checks vertically
		for n in range(0, 2):
			column = [row[n] for row in self._matrix]
			self.__check(column)

		#Checks diagonally
		diagonal_1 = [self._matrix[k][k] for k in range(0, 3)]
		self.__check(diagonal_1)
		diagonal_2 = [self._matrix[j][2 - j] for j in range(0, 3)]
		self.__check(diagonal_2)

	def __check(self, list):
		if list == ["X"] * 3:
			self.__finish(True)
		elif list == ["O"] * 3:
			self.__finish(False)

	def clear(self):
		for y in range(0, 3):
			for x in range(0, 3):
				self._matrix[y][x] = "-"

	def __finish(self, X_won):
		print("Player has won!") if (self.playerIsX == X_won) else print("AI has won!")
		self.clear()
		self._playAgain = False

	@property
	def playAgain(self):
		return self._playAgain


#Helper functions
def getInt(prompt):
	result = 0
	while True:
		try:
			result = int(input(prompt))
			break
		except ValueError:
			print("That's not a valid number!")
	return result

def getPos(prompt):
	n = 0
	while n not in range(1, 4):
		n = getInt(prompt)
	return n