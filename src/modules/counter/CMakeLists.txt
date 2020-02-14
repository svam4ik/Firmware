px4_add_module(
    MODULE modules__counter
    MAIN counter
    STACK_MAIN 2000
    SRCS
        counter.cpp
    DEPENDS
    )