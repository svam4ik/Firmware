px4_add_module(
    MODULE modules__simple_app
    MAIN simple_app
    STACK_MAIN 2000
    SRCS
        simple_app.c
    DEPENDS
    )