import fileinput
import pygame
import time

pygame.init()

screen = pygame.display.set_mode((1000, 700))
pygame.display.set_caption("Graphics Example")
done = False
index = 0
physics_input = fileinput.input()
while not done:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True
    screen.fill((255, 255, 255)) # White background
    text = physics_input.readline()
    coors = text.split("|")
    x1 = float(coors[0].split(",")[0])
    y1 = float(coors[0].split(",")[1])
    x2 = float(coors[1].split(",")[0])
    y2 = float(coors[1].split(",")[1])
    print(coors);
    x1,y1,x2,y2 = x1*0.1, y1*0.1, x2*0.1, y2*0.1
    x1,y1,x2,y2 = x1+450, y1+325, x2+450, y2+325
    pygame.draw.circle(screen, (0, 0, 255), (x1, y1), 5) # Blue circle
    print(x1, y1, x2, y2);
    pygame.draw.circle(screen, (255, 0, 0), (x2, y2), 5) # Red circle
    pygame.display.flip()
    #time.sleep(0.01)
    screen.fill((255, 255, 255))
    index += 1
pygame.quit()