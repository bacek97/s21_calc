//
// Created by Gladis Ariane on 4/3/22.
//

#ifndef SRC_VISUAL_H_
#define SRC_VISUAL_H_

// Заполняем 80х25 точками
void fillDots();

// Используем ESC-символытерминала чтобы перейти в нужный Х и Y
void Goto(int x, int y);

void Clear();

// Подаем Х и функцию func чтобы высчитать y и нарисовать '*' в этой координате
void print();

#endif  // SRC_VISUAL_H_
