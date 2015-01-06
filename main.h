#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <iostream>
#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class setup {
    std::string testing;
public:
    void set_string(std::string);
    void print_testing();
};

#endif // MAIN_H_INCLUDED
