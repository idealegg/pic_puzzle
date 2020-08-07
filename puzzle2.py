#*--coding: utf8--*
import random
import pprint
import pygame
import os


# 初始化
pygame.init()
# 窗口标题
pygame.display.set_caption(u'拼图游戏')
# 窗口大小
s = pygame.display.set_mode((1200, 600))
 
#绘图地图
imgMap = [
    [0, 1, 2],
    [3, 4, 5],
    [6, 7, 8]
]
 
#判断胜利的地图
winMap = [
    [0, 1, 2],
    [3, 4, 5],
    [6, 7, 8]
]
 
pic_size = 498
line_width = 2

#游戏的单击事件
def click(x, y, map):
    print "x: %d, y: %d, map: %s" % (x, y, map)
    if y - 1 >= 0 and map[y - 1][x] == 8:
        map[y][x], map[y - 1][x] = map[y - 1][x], map[y][x]
    elif y + 1 <= 2 and map[y + 1][x] == 8:
        map[y][x], map[y + 1][x] = map[y + 1][x], map[y][x]
    elif x - 1 >= 0 and map[y][x - 1] == 8:
        map[y][x], map[y][x - 1] = map[y][x - 1], map[y][x]
    elif x + 1 <= 2 and map[y][x + 1] == 8:
        map[y][x], map[y][x + 1] = map[y][x + 1], map[y][x]
 
#打乱地图
def randMap(map):
    for i in range(1000):
        x = random.randint(0, 2)
        y = random.randint(0, 2)
        click(x, y, map)
 
# 加载图片
img = pygame.image.load('./girl.jpg')
s_img = pygame.image.load('./start.png')
e_img = pygame.image.load('./end.png')
img = pygame.transform.scale(img, (pic_size, pic_size))
s_img = pygame.transform.scale(s_img, (150, 25))
e_img = pygame.transform.scale(e_img, (150, 25))
#随机地图
#randMap(imgMap)

imgMap = [
    [6, 4, 3],
    [1, 2, 8],
    [7, 5, 0]
]

s_e_img = [s_img, e_img]
c_img = 0
steps = []

#游戏主循环
while True:
    #延时32毫秒,相当于FPS=30
    pygame.time.delay(32)
    for event in pygame.event.get():
        # 窗口的关闭事件
        if event.type == pygame.QUIT:
            exit()
        elif event.type == pygame.MOUSEBUTTONDOWN:      #鼠标单击事件
            if pygame.mouse.get_pressed() == (1, 0, 0):     #鼠标左键按下
                mx, my = pygame.mouse.get_pos()     #获得当前鼠标坐标
                if (c_img == 0) and (mx<pic_size + line_width *2 and my <pic_size + line_width *2):      #判断鼠标是否在操作范围内
                    x=int(mx/((pic_size+line_width)/3))     #计算鼠标点到了哪个图块
                    y=int(my/((pic_size+line_width)/3))
                    #print event
                    #print x
                    #print y
                    pprint.pprint(imgMap)
                    click(x,y,imgMap)   #调用单击事件
                    if imgMap==winMap:  #如果当前地图情况和胜利情况相同,就print胜利
                        print(u"胜利了！")
                elif mx > 10 and mx < 10 + 150 and my > 550 and my < 550 + 25:
                    c_img = (c_img + 1) % 2
                    if c_img == 1:
                        cmd = " ".join(["pic_puzzle5.exe 3 3", " ".join(map(str, imgMap[0])), " ".join(map(str, imgMap[1])), " ".join(map(str, imgMap[2]))])
                        print "cmd: %s" % cmd
                        os.system(cmd)
                        with open("compute_result", "r") as fd:
                            steps = fd.read().split()
                            steps.reverse()
                    else:
                        steps = []

                    
                                
    
    if (c_img == 1) and steps:
        step = steps.pop()
        step = step.strip()
        print "step: %s" % step
        click(int(step)%3,int(step)/3,imgMap)
    if imgMap==winMap:  #如果当前地图情况和胜利情况相同,就print胜利
        print(u"胜利了！")
    #背景色填充成绿色
    s.fill((0,255,0))
    #绘图
    
    #pprint.pprint(imgMap)
    for y in range(3):
        for x in range(3):
            i = imgMap[y][x]
            if i == 8:      #8号图块不用绘制
                continue
            dx = (i % 3) * pic_size/3      #计算绘图偏移量
            dy = (int(i / 3)) * pic_size/3
            #print "x: %s, y: %s, dx: %s, dy: %s\n" % (x, y, dx, dy)
            s.blit(img, (x * (line_width + pic_size/3), y * (line_width + pic_size/3)), (dx, dy, pic_size/3, pic_size/3))
    # 画参考图片
    s.blit(img, (600, 0))
    s.blit(s_e_img[c_img], (10, 550))
    # 刷新界面
    pygame.display.flip()