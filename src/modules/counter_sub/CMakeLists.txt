px4_add_module(
    MODULE modules__counter_sub
    MAIN counter_sub
    STACK_MAIN 2000
    SRCS
        counter_sub.cpp
    DEPENDS
    )