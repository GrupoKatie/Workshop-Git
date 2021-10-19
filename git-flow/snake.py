import turtle, os, random, sys

WIDTH = 600
HEIGHT = 600

def add_sqr(x, y):
	sqr = turtle.Turtle()
	sqr.speed(0)
	sqr.shape('square')
	sqr.color('blue')
	sqr.penup()
	sqr.goto(x, y)
	sqr.dx = 20
	sqr.dy = 0
	return sqr


def move_up():
	head.dx = 0
	head.dy = 20


def move_down():
	head.dx = 0
	head.dy = -20


def move_right():
	head.dx = 20
	head.dy = 0


def move_left():
	head.dx = -20
	head.dy = 0


def is_empty(x, y):
	for sqr in snake:
		if x == sqr.xcor() and y == sqr.ycor():
			return False
		else:
			return True


def add_food():
	temp = possible_pos.copy()
	food_pos = random.choice(temp)
	while food_pos in snake_pos:
		temp.remove(food_pos)
		food_pos = random.choice(temp)

	food = add_sqr(food_pos[0], food_pos[1])
	food.color('purple')
	return food


def snake_exit():
	sys.stderr = open('snake_exit', 'w')
	wn.bye()
	os.remove('snake_exit')


wn = turtle.Screen()
wn.title('Snake by FernandoLins8')
wn.bgcolor('black')
wn.setup(WIDTH, HEIGHT)
wn.tracer(1, 30)

wn.listen()
wn.onkeypress(move_up, 'Up')
wn.onkeypress(move_down, 'Down')
wn.onkeypress(move_right, 'Right')
wn.onkeypress(move_left, 'Left')
wn.onkeypress(snake_exit, 'Escape')

possible_pos = []
a = [x for x in range(-280, 290, 20)]
b = [y for y in range(-280, 290, 20)]
for x in a:
	for y in b:
		possible_pos.append((x, y))

snake = []
snake.append(add_sqr(20, 0))
snake.append(add_sqr(-20, 0))
head = snake[0]

snake_pos = []
snake_pos.append((snake[0].xcor(), snake[0].ycor()))
snake_pos.append((snake[1].xcor(), snake[1].ycor()))
has_food = 0


while True:
	if not has_food:
		food = add_food()
		snake_pos.append((food.xcor(), food.ycor()))
		has_food = 1

	if head.xcor() == food.xcor() and head.ycor() == food.ycor():
		has_food = 0
		food.color('blue')
		snake.append(food)

	last = snake.pop()
	snake_pos.pop()

	last.goto(head.xcor(), head.ycor())
	last.dx, last.dy = head.dx, head.dy

	snake.insert(0, last)
	head = snake[0]

	head.goto(head.xcor() + head.dx, head.ycor() + head.dy)

	# Colisions
	if (head.xcor(), head.ycor()) in snake_pos:
		snake_exit()
	
	if head.xcor() in (-300, 300) or head.ycor() in (-300, 300):
		snake_exit()

	snake_pos.insert(0, (head.xcor(), head.ycor()))
	
	wn.update()
